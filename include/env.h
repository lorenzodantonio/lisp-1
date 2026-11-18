#ifndef LANG_ENV_H
#define LANG_ENV_H

#include "obj.h"

struct env {
  struct obj *bindings;
};

int env_init(struct env *e);
int env_register(struct env *e, struct obj *sym, struct obj *value);
struct obj *env_lookup(struct env *e, struct obj *key);

#endif
