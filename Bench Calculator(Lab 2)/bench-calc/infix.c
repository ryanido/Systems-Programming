#include "infix.h"





// convert a string of a symbol to a predetermined int to use to compare precedence 
int precedence(char* symbol)
{
  if(strcmp(symbol,"+") == 0)
  { 
    return 1;
  }
  else if(strcmp(symbol,"-") == 0)
  {
    return 1;
  }
  else if(strcmp(symbol,"X") == 0)
  {
    return 2;
  }
  else if (strcmp(symbol,"/") == 0)
  {
    return 2;
  }
  else if (strcmp(symbol,"^") == 0)
  {
    return 3;
  }
  else if(strcmp(symbol,"(") == 0)
  {
  }
  
}
//convert infix notation to postfix notation
char**infix_to_postfix(char** infix, int size)
{
  char**postfix = malloc(sizeof(char**) * size);
  struct double_stack*stack = double_stack_new(size);
  int postfix_index = 0;
  int temp;
  for(int i = 0;i < size; i++)
  {
    if(is_operand(infix[i]))
    {
      postfix[postfix_index++] = infix[i];
    }
    else if(strcmp(infix[i],"(") == 0)
    {
      double_stack_push(stack,i);
    }
    else if(is_operator(infix[i]))
    {
      if(!double_stack_empty(stack))
      {
        temp = (int) double_stack_pop(stack);
        double_stack_push(stack,temp);
      
        while(!double_stack_empty(stack) && is_operator(infix[temp]) && 
        (precedence(infix[i]) <= precedence(infix[temp])))
        {
               postfix[postfix_index++] = infix[temp];
               double_stack_pop(stack);
               if(!double_stack_empty(stack))
               {
                 temp = (int) double_stack_pop(stack);
                 double_stack_push(stack,temp);
               }
        }
      }
      double_stack_push(stack,i);
    }
    else if(strcmp(infix[i],")") == 0)
    {
      temp = (int) double_stack_pop(stack);
      while(strcmp(infix[temp],"(") != 0)
      {
        postfix[postfix_index++] = infix[temp];
        temp = (int) double_stack_pop(stack);
      }
    }
  }
  while(!double_stack_empty(stack))
  {
    temp = (int) double_stack_pop(stack);
    postfix[postfix_index++] = infix[temp];
  }
  return postfix;
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  char**postfix_expression = infix_to_postfix(args,nargs); 
  int size = nargs;
  for(int i = 0; i < nargs; i++)
  {
    if (strcmp(args[i],"(") == 0 || strcmp(args[i], ")") == 0)
    {
      size--;
    }
  }
  double result = evaluate_postfix_expression(postfix_expression,size);
  return result;
}

