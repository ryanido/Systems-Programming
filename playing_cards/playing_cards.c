//   playing_cards.c
//   David Gregg
//   December 2020

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "playing_cards.h"



// pack the playing card structures into bytes of memory
unsigned char * pack_playing_cards(struct playing_card * cards,
				   int number_of_cards) {
    int number_of_bits = number_of_cards * 8;
    unsigned char * packed = malloc(number_of_cards * sizeof(unsigned char));
    unsigned char pack = 0;
    for(int i = 0; i < number_of_bits; i++)
    {
        int bit_i = i % 8;
        int card_bit_i = i % 6;
        int card_i = i/6;
		int pack_i = i/8;
        unsigned char temp_bit;
        unsigned char mask;
        if(card_bit_i < 2)
        {
            mask = 1 << (1 - card_bit_i);
            temp_bit = cards[card_i].suit & mask;
			temp_bit = temp_bit >> (1 -card_bit_i);
	   
        }
        else //if(card_bit_i >= 2)
        {
            mask = 1 << (5 - card_bit_i);
            temp_bit = cards[card_i].value & mask;
			temp_bit = temp_bit >> (5 - card_bit_i);
        }
        if(bit_i == 0 && i != 0)
        {
            pack = 0;
            pack_i++;
        }
		temp_bit = temp_bit << (7 - bit_i);
        pack = pack | temp_bit;
        packed[pack_i] = pack;
    }
	return packed;
}




// unpack bytes of memory containing card data into playing card structures
struct playing_card * unpack_playing_cards(unsigned char * packed_cards,
					   int number_of_cards) {
	struct playing_card * cards = malloc(sizeof(struct playing_card) * number_of_cards);
	unsigned char suit = 0;
	unsigned char card = 0;
	for(int i = 0; i < number_of_cards*6; i++)
	{
		int bit_i = i % 8;
        int card_bit_i = i % 6;
        int card_i = i/6;
		int pack_i = i/8;
        unsigned char temp_bit;
        unsigned char mask;
		mask = 1 << (7 - bit_i);
        temp_bit = packed_cards[pack_i] & mask;
		temp_bit = temp_bit >> (7 - bit_i);
		if(card_bit_i == 0)
		{
			suit = 0;
			card = 0;
		}
        if(card_bit_i < 2)
        {
           temp_bit = temp_bit << (1 - card_bit_i);
		   suit = suit | temp_bit;
		   cards[card_i].suit = suit;
		   
        }
        else //if(card_bit_i >= 2)
        {
           temp_bit = temp_bit << (5 - card_bit_i);
		   card = card | temp_bit;
		   cards[card_i].value = card;
        }
		
	}
	return cards;

}


