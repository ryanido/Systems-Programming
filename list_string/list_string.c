//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list_string.h"

// add node to list_string
void list_string_add(struct list_string * ls, char letter)
{
	//case 1: list_string is not empty, add letter to next node of the last node 
	if(ls -> head != NULL)
	{
		struct ls_node * tmp = ls -> head;
		while(tmp -> next != NULL)
		{
			tmp = tmp -> next;
		}
		struct ls_node * new = malloc(sizeof(struct ls_node));
		new -> c = letter;
		new -> next = NULL;
		tmp -> next = new;
	}
	//case 2: list_string is empty, create head node and add letter to it;
	else
	{
		ls -> head = malloc(sizeof(struct ls_node));
		ls -> head -> c = letter;
		ls -> head -> next = NULL;
	}
}

// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string * new_list_string(char * text) {
	struct list_string * ls = malloc(sizeof(struct list_string));
	int i = 1;
	char l = text[0];
	//add all letters to list string until the string null terminates
	while (l != '\0')
	{
		list_string_add(ls,l);
		l = text[i++];
	}
	return ls;
}

// find the length of the list string
int list_string_length(struct list_string * this) {
	int i = 0;
	//case 1: list is not empty, count how many nodes are not null
	if(this -> head != NULL)
	{
		i = 1;
   		struct ls_node * tmp = (this -> head);
		while((tmp -> next) != NULL)
		{
			i++;
			tmp = (tmp -> next);
		}		
	}
	//case 2: list is empty return 0
	return i;
}


// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd". 
int list_string_compare(struct list_string * s1, struct list_string * s2) {
	struct ls_node * n1 = (s1 -> head);
	struct ls_node * n2 = (s2 -> head);
	char c1 = n1 -> c;
	char c2 = n2 -> c;
	int diff = 0;
	//while loop that doesnt end until the strings are proven to be different in contents or length
	while(diff == 0)
	{
		char c1 = n1 -> c;
		char c2 = n2 -> c;
		// letter(ascii) is greater than corresponding letter on other string: exit loop with return value
		if(c1 > c2)
		{
			diff = 1;
		}
		else if (c1 < c2)
		{
			diff = -1;
		}
		else // if c1 == c2
		{
			//next node is null 
			if(n1 -> next == NULL)
			{
				//case 1: strings are not of equal length, return that the shorter string is less lexicographically 
				if(list_string_length(s1) != list_string_length(s2))
				{
					diff = -1;
				}
				//case 2: strings are equal return 0
				else return 0;
			}
			else if (n2 -> next == NULL)
			{
				if(list_string_length(s1) != list_string_length(s2))
				{
					diff = 1;
				}
				else return 0;
			}
			//check next nodes
			n1 = n1 -> next;
			n2 = n2 -> next;
		}
	}
	return diff;
		
	
}


// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string * text, struct list_string * str) {
	for (int i = 0; i < (list_string_length(text)-list_string_length(str)); i++)
	{
		struct ls_node * tmpStr = str -> head;
		struct ls_node * tmpTxt = text -> head;
		for (int o = 0; o < i; o++)
		{
			tmpTxt = tmpTxt -> next;
		}
		int count = 0;
		while((tmpTxt -> c) == (tmpStr -> c))
		{
			count++;
			if(count >= list_string_length(str))
			{
				return 1;
			}
			if((tmpTxt -> next) == NULL || (tmpStr -> next) == NULL)
			{
				return 0;
			}
			else {
				tmpTxt = tmpTxt -> next;
				tmpStr = tmpStr -> next;
			}
	
		}
	}
	return 0;
}




