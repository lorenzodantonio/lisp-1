#include "builtin.h"
#include "env.h"
#include "eval.h"
#include "obj.h"
#include "parser.h"
#include "operative.h"
#include "applicative.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "missing filename\n");
    return -1;
  }

  struct env dict;
  env_init(&dict);

  env_register(&dict, create_symbol("$define!", 8), create_operative(define));
  env_register(&dict, create_symbol("display", 7), create_applicative(display));
  env_register(&dict, create_symbol("+", 1), create_applicative(sum));

  char *src = loadfile(argv[1]);
  if (src == NULL) {
    return -1;
  }

  struct parser p;
  parser_init(&p, src);

  struct obj *parsed;
  while ((parsed = parse(&p)) != NULL) {
    struct obj *value = eval(parsed, &dict);
    if (value->type == OBJ_TYPE_ERROR) {
      print_obj(value);
    }
  }

  parser_deinit(&p);

  return 0;
}
