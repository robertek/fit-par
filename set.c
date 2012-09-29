/*
 * =====================================================================================
 *
 *       Filename:  set.c
 *
 *    Description:  functions to walk all sets
 *
 *        Version:  1.0
 *        Created:  28.9.2012 14:18:27
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "sop.h"
#include "misc.h"
#include "set_next.h"

winner_set * initial_winner( void )
{
	winner_set * help = (winner_set*) malloc( sizeof(winner_set) );

	help->exists = 0;
	help->result = 0;
	help->set = (set_struct*) malloc( input_a * sizeof(set_struct) );

	int i;
	for( i=0 ; i<input_a ; i++ )
	{
		help->set[i].num = 0; 
		help->set[i].member = (int*) malloc( input_n * sizeof(int) );
	}
	return help;
}

winner_set * copy_winner( winner_set * previous )
{
	winner_set * help = initial_winner(); 

	help->result = previous->result;

	int i,j;
	for( i=0 ; i<input_a ; i++ )
	{
		help->set[i].num = previous->set[i].num;
    for( j=0 ; j<help->set[i].num ; j++ )
		{
			help->set[i].member[j] = previous->set[i].member[j];
		}
	}
	return help;
}

void add_to_winner( winner_set * winner, int set, int number )
{
	winner->set[set].member[winner->set[set].num++] = number;
}

winner_set * construct_set( long sum, int num, winner_set * previous )
{
	/* All numbers done, do next set*/
	if( num == input_n )
	{
		previous->result = sum;
		winner_set * help = copy_winner( previous );
		help->set[1].num = 0;
		if( input_a == 2 )
		{
			help = construct_last_set( 0, 0, 1, help, previous );
		}
		else
		{
			help = construct_next_set( 0, 0, 1, help, previous );
		}
		clean_winner( previous );
		return help;
	}

	/* Dont include current number in set */
	winner_set * winner1 = copy_winner( previous );
	/* Add number to second set */
	add_to_winner( winner1, 1, input_S[num] );
	winner1 = construct_set( sum, num+1, winner1 );

	/* Include current number, but check if sum is <c */
	if( sum + input_S[num] < input_c )
	{
		winner_set * winner2 = copy_winner( previous );
		add_to_winner( winner2, 0, input_S[num] );
		winner2 = construct_set( sum + input_S[num], num+1, winner2 );

		if( winner1->exists && winner2->exists )
			if( winner1->result > winner2->result )
			{
				clean_winner( previous );
				clean_winner( winner2 );
				return winner1;
			}
			else 
			{
				clean_winner( previous );
				clean_winner( winner1 );
				return winner2;
			}
		else if( winner1->exists )
		{
			clean_winner( previous );
			clean_winner( winner2 );
			return winner1;
		}
		else if( winner2->exists )
		{
			clean_winner( previous );
			clean_winner( winner1 );
			return winner2;
		}
		else
		{
			clean_winner( previous );
			clean_winner( winner2 );
			return winner1;
		}
	}
	else
	{
		clean_winner( previous );
		return winner1;
	}
}

/* vim: set ts=2 sw=2 :*/
