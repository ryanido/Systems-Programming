// code for a huffman coder


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"

// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
	struct huffcoder * this = malloc(sizeof(struct huffcoder));
	this -> tree = malloc(sizeof(struct huffchar));
	this -> freqs = {0}
	return this;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
	char * temp = filename;
	int freqs[MAX_CHARS] = 0;
	for(int i = 0; filename[i] != '\0'; i++)
	{	
		for(int o = 0; temp[o] != '\0'; o++)
		{
			if (strcmp(temp[o],filename[i]) == 0)
			{
				freqs[i]++;
				temp[o] = '00';
			} 
		}
	}
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
}


// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder * this)
{
  for ( int i = 0; i < NUM_CHARS; i++ ) {
    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], this->codes[i]);;
  }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{
}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{
}
