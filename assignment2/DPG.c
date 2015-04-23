#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct builtin {
  const char* ident;
  int (*main)(int argc, char** argv);
};

static int builtin_abs(int argc, char** argv)
{
  /* ignore error checking, gotta go fast */
  int n = atoi(argv[0]);
  return (n < 0) ? -n : n;
}

static int builtin_sum(int argc, char** argv)
{
  int sum = 0;

  for (int i = 0; i < argc; i++)
  sum += atoi(argv[i]);

  return sum;
}

/* this array should be sorted, if not qsort() it */
const struct builtin funcs[] = {
  { "abs", builtin_abs },
  { "sum", builtin_sum }
};
const size_t funcs_len = sizeof(funcs) / sizeof(funcs[0]);

static int builtin_cmp(const void* a, const void* b)
{
  const struct builtin* pa = (const struct builtin*)a;
  const struct builtin* pb = (const struct builtin*)b;

  return strcmp(pa->ident, pb->ident);
}

int main(int argc, char** argv)
{
  struct builtin tmp;
  tmp.ident = argv[1];

  /* assume input valid */
  struct builtin* b = bsearch(&tmp, funcs, funcs_len, sizeof(funcs[0]), builtin_cmp);

  if (b == NULL) {
    fprintf(stderr, "no such command: %s\n", argv[1]);
    return 1;
  }

  printf("command returned: %d\n", b->main(argc-2, &argv[2]));
  return 0;
}
