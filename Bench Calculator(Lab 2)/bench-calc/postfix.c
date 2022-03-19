#include "postfix.h"
#include <math.h>

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  struct double_stack * stack = double_stack_new(nargs);
  for(int i = 0;i < nargs; i++)
  {
    if(is_operator(args[i]))
    {
      double operand2 = double_stack_pop(stack);
      double operand1 = double_stack_pop(stack);
      if(strcmp(args[i],"+") == 0)
      { 
        double_stack_push(stack, (operand2 + operand1));
      }
      else if(strcmp(args[i],"-") == 0)
      {
        double_stack_push(stack, (operand1-operand2));
      }
      else if(strcmp(args[i],"X") == 0)
      {
        double_stack_push(stack, (operand2*operand1));
      }
      else if (strcmp(args[i],"/") == 0)
      {
        double_stack_push(stack, (operand1/operand2));
      }
      else
      {
       double_stack_push(stack,(pow(operand1,operand2)));
      }
    }
    else
    {
      double_stack_push(stack,atof(args[i]));
    }
  }
  double result = double_stack_pop(stack);
  double_stack_free(stack);
  return result;
}

int is_operator(char*token)
{
  if(token[1] != '\0')
  {
    return 0;
  }
  else if((strcmp(token,"+") == 0||  strcmp(token,"-") == 0|| 
     strcmp(token,"X") == 0|| strcmp(token,"/") == 0|| strcmp(token,"^") == 0))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int is_operand(char*token)
{
  int i = 0;
  if(token[1] != '\0')
  {
    if(token[0] == '-')
    {
      i++;  
    }
    while(token[i] != '\0')
    {
      if(!(token[i] <='9'|| token[i] == '.'))
      {
        return 0;
      }
      i++;
    }
    return 1;
  }
  else if(token[0] <= '9' && token[0] >= '0')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


