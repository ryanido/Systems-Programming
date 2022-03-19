#include "bitset.h"
#include <stdlib.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
  struct bitset * set = malloc(sizeof(struct bitset));
	int bits_per_word = sizeof(uint64_t);
	set -> universe_size = size;
	set -> size_in_words = ((size + bits_per_word - 1)/bits_per_word);
  set -> bits = malloc(sizeof(uint64_t) * (set -> size_in_words));
	for(int i = 0; i < set -> size_in_words; i++)
	{
		set -> bits[i] = 0;
	}
	return set;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
  return (this -> universe_size);
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this)
{
  int count = 0;
  for(int i = 0; i < this -> universe_size;i++)
  { 
    if(bitset_lookup(this,i))
    { 
      count++;
    }
  }
  return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
  uint64_t temp = item;
  int word_pos = temp/(this -> size_in_words);
  int item_pos = temp%(this -> size_in_words);
  uint64_t set = this -> bits[word_pos];
  uint64_t mask = 1 << item_pos;
	uint64_t result = mask & set;
	result = result >> item_pos;
	return result;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
  uint64_t temp = item;
  int word_pos = temp/(this -> size_in_words);
  int item_pos = temp%(this -> size_in_words);
  uint64_t set = this -> bits[word_pos];
  uint64_t mask = 1 << item_pos;
	(this -> bits)[word_pos] = (mask | set);
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
  uint64_t temp = item;
  int word_pos = temp/(this -> size_in_words);
  int item_pos = temp%(this -> size_in_words);
  uint64_t set = this -> bits[word_pos];
  uint64_t mask = ~(1 << item_pos);
	(this -> bits)[word_pos] = (mask & set);
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
    if(bitset_size(src1) == bitset_size(src2) && bitset_size(src1) == bitset_size(dest))
    {
      for (int i = 0; i < bitset_size(src1); i++)
      {
        if(bitset_lookup(src1,i) || bitset_lookup(src2,i))
        {
          bitset_add(dest,i);
        }
      }
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
     if(bitset_size(src1) == bitset_size(src2) && bitset_size(src1) == bitset_size(dest))
    {
      for (int i = 0; i < bitset_size(src1); i++)
      {
        if(bitset_lookup(src1,i) && bitset_lookup(src2,i))
        {
          bitset_add(dest,i);
        }
      }
    }
}
