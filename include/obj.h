#ifndef LANG_OBJ_H
#define LANG_OBJ_H

#include <stddef.h>

struct obj;

enum obj_type {
  OBJ_TYPE_NUMBER,
  OBJ_TYPE_CONS_CELL,
  OBJ_TYPE_STRING,
  OBJ_TYPE_SYMBOL,
  OBJ_TYPE_FUNCTION,
  OBJ_TYPE_ERROR,
  OBJ_TYPE_NIL,
};

struct cons_cell {
  struct obj *car;
  struct obj *cdr;
};

struct string {
  char *value;
  size_t len;
};

struct obj {
  enum obj_type type;
  union {
    struct cons_cell cons_cell;
    struct string str;
    int num;
    struct obj *(*fn)(struct obj *args);
  };
};

struct obj *create_number(int n);
struct obj *create_string(char *s);
struct obj *create_symbol(char *s);
struct obj *create_cons_cell(struct obj *car, struct obj *cdr);
struct obj *create_function(struct obj *(*fn)(struct obj *args));
struct obj *create_error(char *msg);
struct obj *create_nil(void);

void print_obj(struct obj *o);

#endif
