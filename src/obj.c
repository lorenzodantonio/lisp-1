#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct obj *create_obj(enum obj_type type) {
  struct obj *o = malloc(sizeof(*o));
  if (!o) {
    return NULL;
  }
  o->type = type;
  return o;
}

struct obj *create_number(int n) {
  struct obj *o = create_obj(OBJ_TYPE_NUMBER);
  o->num = n;
  return o;
}

struct obj *create_string(char *s, size_t len) {
  struct obj *o = create_obj(OBJ_TYPE_STRING);
  o->str.value = malloc(len + 1);
  memcpy(o->str.value, s, len);
  o->str.value[len] = '\0';
  return o;
}

struct obj *create_symbol(char *s, size_t len) {
  struct obj *o = create_string(s, len);
  o->type = OBJ_TYPE_SYMBOL;
  return o;
}

struct obj *create_operative(struct obj *(*native)(struct obj *args, struct env *env)) {
  struct obj *o = create_obj(OBJ_TYPE_OPERATIVE);
  o->operative.native = native;
  return o;
}

struct obj *create_applicative(struct obj *(*native)(struct obj *args)) {
  struct obj *o = create_obj(OBJ_TYPE_APPLICATIVE);
  o->applicative = native;
  return o;
}

struct obj *create_error(char *msg) {
  struct obj *o = create_string(msg, strlen(msg));
  o->type = OBJ_TYPE_ERROR;
  return o;
}

struct obj *create_cons_cell(struct obj *car, struct obj *cdr) {
  struct obj *o = create_obj(OBJ_TYPE_CONS_CELL);

  o->cons_cell.car = car;
  o->cons_cell.cdr = cdr;

  return o;
}

struct obj *create_nil(void) {
  return create_obj(OBJ_TYPE_NIL);
}

void print_obj(struct obj *o) {
  if (o == NULL) {
    return;
  }

  switch (o->type) {
  case OBJ_TYPE_NUMBER:
    printf("%d", o->num);
    break;
  case OBJ_TYPE_SYMBOL:
  case OBJ_TYPE_STRING:
    printf("%s", o->str.value);
    break;
  case OBJ_TYPE_ERROR:
    printf("error: %s", o->str.value);
    break;
  case OBJ_TYPE_CONS_CELL: {
    printf("(");
    print_obj(o->cons_cell.car);
    printf(" . ");
    print_obj(o->cons_cell.cdr);
    printf(")");
    break;
  }
  case OBJ_TYPE_OPERATIVE:
    printf("struct obj *(*fn)(struct obj *args, struct env *env);)");
    break;
  case OBJ_TYPE_APPLICATIVE:
    printf("struct obj *(*fn)(struct obj *args)");
    break;
  case OBJ_TYPE_NIL:
    printf("()");
    break;
  default:
    printf("unknown type");
  }
  printf("\n");
}
