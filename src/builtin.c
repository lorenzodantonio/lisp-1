#include "builtin.h"

struct obj *sum(struct obj *args) {
  int r = 0;
  const struct obj *current = args;

  while (current->type != OBJ_TYPE_NIL) {
    const struct obj *car = current->cons_cell.car;
    if (car->type != OBJ_TYPE_NUMBER) {
      return create_error("+: contract violation");
    }

    r += car->num;
    current = current->cons_cell.cdr;
  }

  return create_number(r);
}
