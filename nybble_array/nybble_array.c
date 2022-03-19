//   nybble_array.c
//   David Gregg
//   December 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "nybble_array.h"


// create a new array of nybbles with space for "size"
// nybbles and initialize the values of the array to zero
struct nybble_array * nybble_array_new(int size) {
	//allocate memory for nybble array
	struct nybble_array * this = malloc(sizeof(struct nybble_array));
	this -> size_in_nybbles = size;
	//check if number of nybbles is even or odd to see if extra byte is needed
	if ( size % 2 == 1)
	{
		this -> size_in_bytes = size/2 + 1;
	}
	else
	{
		this -> size_in_bytes = size/2;
	}
	this -> data_bytes = malloc(sizeof(char) * (this -> size_in_bytes));
	//intialize each value in the array to 0
	for(int i = 0;i < (this -> size_in_bytes);i++)
	{
		(this -> data_bytes)[i] = 0;
	}
	return this;
}

// return the nybble value at position index
unsigned get_nybble_value(struct nybble_array * this, int index) {
	// get the byte in which the nybble relates to in the array and its position in that byte(1st or 2nd)
	int byte_index = index /2;
	int nybble_pos = index % 2;
	unsigned char temp_byte = (this -> data_bytes)[byte_index];
	unsigned char mask = 0xF;
	unsigned result;
	// retrieve nybble by firstly clearing the bits in the byte it doesnt relate to, 
	// then pushing the remaining bits to their original position in their unpacked representation
	if (nybble_pos == 0)
	{
		result = (temp_byte >> 4) & mask;	
	}
	else // if (nybble_pos == 1)
	{
		result = temp_byte & mask;
	} 
	return result;
}

// set the nybble at position index to value
void set_nybble_value(struct nybble_array * this, int index, unsigned value) {
	//get the byte in which the nybble relates to in the array and its position in that byte(1st or 2nd)
	int byte_index = index /2;
	int nybble_pos = index % 2;
	unsigned char temp_byte = (this -> data_bytes)[byte_index];
	unsigned char mask;
	unsigned char new_byte;
	// insert nybble by firstly clearing the bits it relates, 
	// then setting those bits to the nybbles binary code 
	if (nybble_pos == 0)
	{
		mask = 0xF;
		new_byte = (temp_byte & mask) | (value << 4);
	}
	else // if (nybble_pos == 1)
	{
		mask = 0xF0;
		new_byte = (temp_byte & mask) | value;
	} 
	(this -> data_bytes)[byte_index] = new_byte;
}

// free the memory used by a nybble array
void nybble_array_free(struct nybble_array * this) {
	free(this -> data_bytes);
	free(this);
}

// given an array of unsigned integers with values 0 to 15 create
// a new nybble_array with the same values
struct nybble_array * unsigned_to_nybble_array(unsigned * array, int size)
{
	struct nybble_array * result = nybble_array_new(size);
	for(int i = 0; i < size; i++)
	{
		set_nybble_value(result,i,array[i]);
	}
	return result;
}

// given an array of nybbles, create a new array of unsigned integers
// with the same values
unsigned * nybble_array_to_unsigned(struct nybble_array * this) {
	unsigned * result = malloc(sizeof(unsigned) * (this -> size_in_nybbles));
	for(int i = 0; i < (this -> size_in_nybbles); i++)
	{
		result[i] = get_nybble_value(this,i);
	}
	return result;
}

// print the raw byte content of the nybble array
void print_raw_bytes_nybble_array(struct nybble_array * this) {
  for ( int i = 0; i < this->size_in_bytes; i++ ) {
    printf("%x ", this->data_bytes[i]);
  }
  printf("\n");
}

