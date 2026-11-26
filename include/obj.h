#ifndef LANG_OBJ_H
#define LANG_OBJ_H

#include <stddef.h>

struct env;
struct obj;

enum obj_type {
  OBJ_TYPE_NUMBER,
  OBJ_TYPE_CONS_CELL,
  OBJ_TYPE_STRING,
  OBJ_TYPE_SYMBOL,
  OBJ_TYPE_ERROR,
  OBJ_TYPE_OPERATIVE,
  OBJ_TYPE_APPLICATIVE,
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

union operative {
  struct obj *(*native)(struct obj *args, struct env *env);
  struct obj *expr;
};

struct obj {
  enum obj_type type;
  union {
    struct cons_cell cons_cell;
    struct string str;
    int num;
    union operative operative;
    struct obj *(*applicative)(struct obj *args);
  };
};

struct obj *create_number(int n);
struct obj *create_string(char *s, size_t len);
struct obj *create_symbol(char *s, size_t len);

struct obj *create_cons_cell(struct obj *car, struct obj *cdr);

struct obj *create_operative(struct obj *(*native)(struct obj *args, struct env *env));
struct obj *create_applicative(struct obj *(*native)(struct obj *args));

struct obj *create_error(char *msg);
struct obj *create_nil(void);

void print_obj(struct obj *o);

#endif
