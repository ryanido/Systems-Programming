
#include "stack.h"



struct double_stack * double_stack_new(int max_size) {
 struct double_stack * temp;
 temp = malloc(sizeof(struct double_stack));
 temp -> top = 0;
 temp -> max_size = max_size;
 temp -> items = malloc(sizeof(double) *  max_size);
 return temp;
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
 assert(this -> top < this -> max_size);
 this -> items[this -> top] = value;
 this -> top++;
}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
 assert(this -> top > 0);
 double result = this -> items[this->top - 1];
 this -> top--;
 return result;
}
//peek a value on the stack
double double_stack_peek(struct double_stack * this) 
{
  double result = double_stack_pop(this);
  double_stack_push(this, result);
  return result;
}
//check if stack is empty
int double_stack_empty(struct double_stack * this)
{
  return (this -> top <= 0);
}
//free/empty a double stack
void double_stack_free (struct double_stack * this){
	free(this -> items);
	free(this);
 }


