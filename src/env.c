#include "env.h"
#include <string.h>

int env_init(struct env *e) {
  e->bindings = create_nil();
  return 0;
}

int env_register(struct env *e, struct obj *sym, struct obj *value) {
  e->bindings = create_cons_cell(create_cons_cell(sym, value), e->bindings);
  return 0;
}

struct obj *env_lookup(struct env *e, struct obj *key) {
  for (struct obj *o = e->bindings; o->type != OBJ_TYPE_NIL;
       o = o->cons_cell.cdr) {
    struct obj *slot = o->cons_cell.car;

    struct obj *k = slot->cons_cell.car;
    if (strcmp(k->str.value, key->str.value) == 0) {
      return slot->cons_cell.cdr;
    }
  }

  return create_nil();
}
