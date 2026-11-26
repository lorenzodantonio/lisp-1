#include "parser.h"
#include "obj.h"

#include <ctype.h>
#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parser_init(struct parser *p, char *program) {
  p->program = program;
  p->cursor = program;
}

void parser_deinit(struct parser *p) {
  free(p->program);
  p->program = NULL;
}

char *loadfile(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "can't read file\n");
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  const size_t fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "failed allocating memory for source code\n");
    return NULL;
  }

  fread(buffer, fsize, 1, fp);
  buffer[fsize] = '\0';

  fclose(fp);

  return buffer;
}

void skip_spaces(struct parser *p) {
  while (isspace(*p->cursor)) {
    p->cursor++;
  }
}

struct obj *parse_string(struct parser *p) {
  char *start = p->cursor;

  while (*p->cursor != '\0') {
    if (*p->cursor == '"') {
      return create_string(start, p->cursor++ - start);
    }

    p->cursor++;
  }
  return NULL;
}

int is_symbol_char(int c) {
  char symchars[] = "+-*/$!";
  if (isalpha(c)) {
    return 1;
  }

  if (strchr(symchars, c) != NULL) {
    return 1;
  }

  return 0;
}

struct obj *parse_symbol(struct parser *p) {
  char *start = p->cursor;

  while (*p->cursor && is_symbol_char(*p->cursor)) {
    p->cursor++;
  }

  return create_symbol(start, p->cursor - start);
}

struct obj *parse_number(struct parser *p) {
  const char *start = p->cursor;

  if (*p->cursor == '-') {
    p->cursor++;
  }

  while (isdigit(*p->cursor)) {
    p->cursor++;
  }

  const size_t len = p->cursor - start;
  char *str = malloc(len + 1);
  str[len] = '\0';
  memcpy(str, start, len);

  return create_number(atoi(str));
}

struct obj *parse_list(struct parser *p) {
  skip_spaces(p);

  if (*p->cursor == '\0') {
    return NULL;
  }

  if (*p->cursor == ')') {
    p->cursor++;
    return create_nil();
  }

  struct obj *car = parse(p);
  if (car == NULL) {
    return NULL;
  }

  return create_cons_cell(car, parse_list(p));
}

struct obj *parse(struct parser *p) {
  skip_spaces(p);
  if (*p->cursor == '\0') {
    return NULL;
  }

  if (*p->cursor == '(') {
    p->cursor++;
    return parse_list(p);
  }

  if (*p->cursor == '"') {
    p->cursor++;
    return parse_string(p);
  }

  if (is_symbol_char(*p->cursor)) {
    return parse_symbol(p);
  }

  if (isdigit(*p->cursor)) {
    return parse_number(p);
  }

  return NULL; // error
}
