#include "builtin.h"
#include "env.h"
#include "eval.h"
#include "obj.h"

#include <stdio.h>

int main(void) {
  struct env dict;
  env_init(&dict);

  env_register(&dict, create_symbol("+"), create_function(sum));

  struct obj *prg = create_cons_cell(
      create_symbol("+"),
      create_cons_cell(
          create_number(1),
          create_cons_cell(create_number(2),
                           create_cons_cell(create_number(3),
                                            create_cons_cell(create_number(4),
                                                             create_nil())))));

  struct obj *result = eval(prg, &dict);
  print_obj(result);
  printf("\n");

  return 0;
}
