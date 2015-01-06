#include "ast.h"
// Data structures for the Stack language.
enum Stack_Kind_t {STACK_ADD,STACK_MINUS,STACK_TIMES,STACK_DIVIDE, STACK_PUSH};
struct Stack_t
{
  enum Stack_Kind_t kind;
};

struct Stack_Add
{
  enum Stack_Kind_t kind;
};
struct Stack_Minus
{
  enum Stack_Kind_t kind;
};
struct Stack_Times
{
  enum Stack_Kind_t kind;
};
struct Stack_Divide
{
  enum Stack_Kind_t kind;
};

struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

struct Stack_t *Stack_Add_new ()
{
  struct Stack_Add *p = (struct Stack_Add *)malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Minus_new ()
{
  struct Stack_Add *p = (struct Stack_Minus *)malloc (sizeof(*p));
  p->kind = STACK_MINUS;
  return (struct Stack_t *)p;
}
struct Stack_t *Stack_Times_new ()
{
  struct Stack_Add *p = (struct Stack_Times *)malloc (sizeof(*p));
  p->kind = STACK_TIMES;
  return (struct Stack_t *)p;
}
struct Stack_t *Stack_Divide_new ()
{
  struct Stack_Add *p = (struct Stack_Divide *)malloc (sizeof(*p));
  p->kind = STACK_DIVIDE;
  return (struct Stack_t *)p;
}
struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = (struct Stack_Push *)malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}
/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = (struct List_t *)malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}

// a compiler from arithmetic-exp to Stack
struct List_t *all = 0;

void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}

void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    emit (Stack_Push_new (((Exp_Int)exp)->n));
    break;
  }
  case EXP_ADD:{
	compile(((Exp_Add)exp)->left);
	compile(((Exp_Add)exp)->right);
	emit(Stack_Add_new());
    break;
  }
  case EXP_MINUS:{
	compile(((Exp_Minus)exp)->left);
	compile(((Exp_Minus)exp)->right);
	emit(Stack_Minus_new());
    break;
  }
  case EXP_TIMES:{
	compile(((Exp_Times)exp)->left);
	compile(((Exp_Times)exp)->right);
	emit(Stack_Times_new());
    break;
  }
  case EXP_DIVIDE:{
	compile(((Exp_Divide)exp)->left);
	compile(((Exp_Divide)exp)->right);
	emit(Stack_Divide_new());
    break;
  }
  default:
    break;
  }
}

void print_instrs(struct List_t *list)
{
//assume len >=2
    struct List_t * cur = list, * next = list->next;
    cur->next = 0;
    while(next != 0)
    {
        struct List_t * temp = next->next;
        next->next = cur;
        cur = next;
        next = temp;
    }
    while(cur != 0)
    {
        switch(cur->instr->kind)
        {
          case STACK_ADD:
          {
            printf("add\n");
            break;
          }
          case STACK_MINUS:
          {
            printf("minus\n");
            break;
          }
          case STACK_TIMES:
          {
            printf("times\n");
            break;
          }
          case STACK_DIVIDE:
          {
            printf("divide\n");
            break;
          }
          case STACK_PUSH:
          {
            printf("push %d\n",((struct Stack_Push *)(cur->instr))->i);
            break;
          }
          default:
          {
            printf("compiler wrong");
          }
        }
        cur = cur->next;
    }
    

}

extern Exp_t tree;
void yyparse ();

int main (int argc, char **argv)
{
  yyparse();
  Exp_print (tree);
  compile(tree);
  printf("\n-------------compile result-----------------\n");
  print_instrs(all);
  
  return 0;
}
