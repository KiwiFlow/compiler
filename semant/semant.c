#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

#define TODO()\
  do{\
  printf ("TODO: add your code at file: \"%s\", line: %d\n", __FILE__, __LINE__);\
}while(0)

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    //R2
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  switch(exp->kind)
  {
  case EXP_INT:
  {
    return TYPE_INT;
  }
  case EXP_TRUE:
  {
    return TYPE_BOOL;
  }
  case EXP_FALSE:
  {
    return TYPE_BOOL;
  }
  case EXP_ID:
  {
    Type_t id_type =Table_lookup(((Exp_Id)exp)->id);
    if(id_type==-1)
    {
      //R1
      fprintf (stderr, "Error: the variable "
      "\"%s\" has not been declared!\n", ((Exp_Id)exp)->id);
      exit(0);
    }
    return id_type;
  }
  case  EXP_ADD:
  {
    Exp_Add p = (Exp_Add)exp;
    if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
    {
      //R6
      printf("add exp type error!\n");
      exit(0);
    }
    return TYPE_INT;
  }
  case  EXP_SUB:
  {
    Exp_Sub p = (Exp_Sub)exp;
    if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
    {
      //R6
      printf("sub exp type error!\n");
      exit(0);
    }
    return TYPE_INT;
  }
  case  EXP_TIMES:
  {
    Exp_Times p = (Exp_Times)exp;
    if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
    {
      //R6
      printf("times exp type error!\n");
      exit(0);
    }
    return TYPE_INT;
  }
  case  EXP_DIVIDE:
  {
    Exp_Divide p = (Exp_Divide)exp;
    if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
    {
      //R6
      printf("divide exp type error!\n");
      exit(0);
    }
    return TYPE_INT;
  }
  case  EXP_AND:
  {
    Exp_And p = (Exp_And)exp;
    if(check_exp(p->left) != TYPE_BOOL || check_exp(p->right) != TYPE_BOOL)
    {
      //R7
      printf("and exp type error!\n");
      exit(0);
    }
    return TYPE_BOOL;
  }
  case  EXP_OR:
  {
    Exp_Or p = (Exp_Or)exp;
    if(check_exp(p->left) != TYPE_BOOL || check_exp(p->right) != TYPE_BOOL)
    {
      //R7
      printf("or exp type error!\n");
      exit(0);
    }
    return TYPE_BOOL;
  }
  default :
  {
    printf("compiler error\n");
    exit(0);
  }
  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  switch(stm->kind)
  {
    case STM_ASSIGN:
    {
      Stm_Assign stm_as = (Stm_Assign)stm;
      Type_t id_type =Table_lookup(stm_as->id);
      if(id_type==-1)
      {
        //R1
        fprintf (stderr, "Error: the variable "
        "\"%s\" has not been declared!\n", stm_as->id);
        exit(0);
      }
      Type_t exp_type = check_exp(stm_as->exp);
      if(id_type != exp_type)
      {//R3
        printf("assign statement left type not equal to right type\n");
        exit(0);
      }
      
      break;
    }
    case STM_PRINTI:
    {
      Stm_Printi p = (Stm_Printi)stm;
      Exp_t exp = p->exp;
      if(check_exp(exp) != TYPE_INT)
      {
        //R4
        fprintf (stderr, "Error: printi type error ");
      }
      break;
    }
    case STM_PRINTB:
    {
      Exp_t exp = ((Stm_Printb)stm)->exp;
      if(check_exp(exp) != TYPE_BOOL)
      {
        //R5
        fprintf (stderr, "Error: printb type error ");
      }
      break;
    }
    default:
    {
    }
  }
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
