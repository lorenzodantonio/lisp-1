#ifndef LANG_PARSER_H
#define LANG_PARSER_H

struct parser {
  char *program;
  char *cursor;
};

void parser_init(struct parser *p, char *program);
void parser_deinit(struct parser *p);

struct obj *parse_string(struct parser *p);
struct obj *parse_symbol(struct parser *p);
struct obj *parse_number(struct parser *p);

// struct obj *parse_list(struct parser *p);

struct obj *parse(struct parser *p);

char *loadfile(char *filename);

#endif
