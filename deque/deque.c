//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "deque.h"

// create a new empty deque
struct deque * new_deque() {
	struct deque * this = malloc(sizeof(struct deque));
	this -> elements = malloc(sizeof(char*))
	this -> size = 0;
	this -> nelements = 0; 
	return this
}

// push a string to the front of the deque
void push_front_deque(struct deque * this, char * str) {

}

// pop a string from the front of the deque
char * pop_front_deque(struct deque * this) {

}

// push a string to the back of the deque
void push_back_deque(struct deque * this, char * str) {

}

// pop a value from the back of the deque
char * pop_back_deque(struct deque * this) {

}

// free the memory used by the deque
void free_deque(struct deque * this) {

}

// return a string from the deque at position "index", where the
// item at the front of the deque has index 0, and subsequent
// items are numbered successively. If there are fewer than index+1
// items in the deque, return a string containing the value "ERROR"
char * item_at_deque(struct deque * this, int index) {

}



