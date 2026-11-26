#ifndef LANG_EVAL_H
#define LANG_EVAL_H

#include "obj.h"

struct obj *eval(struct obj *prg, struct env *e);

#endif
