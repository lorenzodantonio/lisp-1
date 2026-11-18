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

struct obj *create_string(char *s) {
  struct obj *o = create_obj(OBJ_TYPE_STRING);
  o->str.value = strdup(s);
  o->str.len = strlen(s);
  return o;
}

struct obj *create_symbol(char *s) {
  struct obj *o = create_string(s);
  o->type = OBJ_TYPE_SYMBOL;
  return o;
}

struct obj *create_function(struct obj *(*fn)(struct obj *args)) {
  struct obj *o = create_obj(OBJ_TYPE_FUNCTION);
  o->fn = fn;
  return o;
}

struct obj *create_error(char *msg) {
  struct obj *o = create_string(msg);
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
  case OBJ_TYPE_FUNCTION:
    printf("struct obj *(*fn)(struct obj *args)");
    break;
  case OBJ_TYPE_NIL:
    printf("()");
    break;
  default:
    printf("unknown type");
  }
}
