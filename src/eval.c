#include "eval.h"

struct obj *eval(struct obj *prg, struct env *e) {
  switch (prg->type) {
  case OBJ_TYPE_CONS_CELL: {
    struct obj *car = prg->cons_cell.car;
    struct obj *cdr = prg->cons_cell.cdr;

    struct obj *op = eval(car, e);
    if (op->type == OBJ_TYPE_ERROR) {
      return op;
    }

    if (op->type != OBJ_TYPE_FUNCTION) {
      return create_error("operator expected");
    }

    struct obj *args = NULL;
    struct obj *tail = create_nil();

    for (struct obj *cur = cdr; cur->type != OBJ_TYPE_NIL;
         ) {
      struct obj *val = eval(cur->cons_cell.car, e);
      if (val->type == OBJ_TYPE_ERROR) {
        return val;
      }

      if (args == NULL) {
        args = create_cons_cell(val, create_nil());
        cur = cur->cons_cell.cdr;
        tail = args;
      } else {
        args->cons_cell.cdr = create_cons_cell(val, args->cons_cell.cdr);
        args = args->cons_cell.cdr;
        cur = cur->cons_cell.cdr;
      }
    }

    return op->fn(tail);
  }
  case OBJ_TYPE_SYMBOL: {
    struct obj *value = env_lookup(e, prg);
    if (value->type == OBJ_TYPE_NIL) {
      return create_error("symbol not found");
    }
    return value;
  }
  case OBJ_TYPE_NUMBER:
  case OBJ_TYPE_STRING:
  case OBJ_TYPE_ERROR:
    return prg;
  default:
    return create_error("attempted to evaluate an unknown type");
  }
}
