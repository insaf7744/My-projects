#ifndef STACK_H_
#define STACK_H_

struct st {
  char c;
  struct st *next;
};
struct st *push(struct st *, char);
char delete (struct st **);
int priority(char);
void parsing_in_polish_notation(struct st *operations, char *input_str,
                                char *output_str);

#endif