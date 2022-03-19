#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
  struct listset * header;
	header = malloc(sizeof(struct listset));
	header -> head = NULL;
	return header;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
  for(struct listnode * p = this -> head; p != NULL; p = p->next)
	{
		if(strcmp(item, p -> str) == 0)
		{
			return 1;
		}
	}
	return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
  if(!listset_lookup(this,item))
  {
    struct listnode * tmp = malloc(sizeof(struct listnode));
	  tmp -> str = item;
	  tmp -> next = this -> head;
	  this -> head = tmp;
  }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
  //is list empty?
	if(this -> head == NULL)
	{
		return;
	}	
	if(listset_lookup(this,item))
	{
		//if wanted item is at the head of the list
		if(strcmp((this -> head) -> str, item) == 0)
		{
			struct listnode * tmp = this -> head;
			this -> head = tmp -> next;
			free(tmp);
			return;
		}
		//search remainder of list for item
		for(struct listnode * p = this -> head; p != NULL; p = p->next)
		{
			if(strcmp(item, (p -> next) -> str) == 0)
			{
				struct listnode * tmp = p -> next;
				p -> next = tmp -> next;
				free(tmp);
				return;
			}
		}
		
	}
}
  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
  struct listnode * tmp = src1 -> head;
  for(int i = 1; i < listset_cardinality(src1); i++)
  {
    listset_add(dest,tmp -> str);
    tmp = tmp -> next;
  }
  tmp = src2 -> head;
  for(int i = 1; i < listset_cardinality(src2); i++)
  {
    listset_add(dest,tmp -> str);
    tmp = tmp -> next;
  }

}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
  struct listnode * tmp = src1 -> head;
  char* tmpI = tmp -> str;
  for(int i = 1; i < listset_cardinality(src1); i++)
  {
    if(listset_lookup(src2,tmpI))
    {
      listset_add(dest,tmpI);
    }
    tmp = tmp -> next;
    tmpI = tmp -> str;
  }              

}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
    int count = 1;
    if (this -> head == NULL)
    {
      return 0;
    }
    for(struct listnode * tmp = this -> head;tmp -> next != NULL; tmp = tmp -> next)
    {
      count++;
    }
    return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
