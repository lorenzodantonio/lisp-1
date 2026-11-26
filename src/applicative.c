#include "applicative.h"
#include "obj.h"

struct obj *display(struct obj *args) {
  if (args->type != OBJ_TYPE_CONS_CELL || args->cons_cell.cdr->type != OBJ_TYPE_NIL) {
    return create_error("display: expected 1 argument");
  }

  print_obj(args->cons_cell.car);
  return create_nil();
}
