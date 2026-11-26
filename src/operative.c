#include "obj.h"
#include "env.h"
#include "eval.h"


struct obj *define(struct obj *param, struct env *env) {
  if (param->type != OBJ_TYPE_CONS_CELL) {
    return create_error("define: missing key");
  }

  struct obj *key = param->cons_cell.car;
  if (key->type != OBJ_TYPE_SYMBOL) {
    return create_error("define: wrong key type (must be a symbol)");
  }

  struct obj *cdr = param->cons_cell.cdr;
  if (cdr->type != OBJ_TYPE_CONS_CELL) {
    return create_error("define: missing value");
  }

  struct obj *value = eval(cdr->cons_cell.car, env);
  if (value->type == OBJ_TYPE_ERROR) {
    return value;
  }

  env_register(env, key, value);
  return value;
}
