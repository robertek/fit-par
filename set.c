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

inline winner_set * initial_winner( void )
{
	winner_set * help = (winner_set*) malloc( sizeof(winner_set) );

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

inline winner_set * copy_winner( winner_set * previous )
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

inline void add_to_winner( winner_set * winner, int set, int number )
{
	winner->set[set].member[winner->set[set].num++] = number;
}

inline void del_from_winner( winner_set * winner, int set  )
{
	winner->set[set].num--;
}

int construct_set( long sum, int num, winner_set * previous )
{
	/* All numbers done, do next set*/
	if( num == input_n )
	{
		if( sum == 0 ) return 0;

		previous->result = sum;
		winner_set * help = copy_winner( previous );
		help->set[1].num = 0;
		if( input_a == 2 )
		{
			construct_last_set( 0, 0, 1, help, previous );
		}
		else
		{
			construct_next_set( 0, 0, 1, help, previous );
		}
		clean_winner(help);
		return 0;
	}

	if( max_winner->result == input_max ) return 0;

	/* Include current number, but check if sum is <c */
	if( sum + input_S[num] < input_c )
	{
		add_to_winner( previous, 0, input_S[num] );
		construct_set( sum + input_S[num], num+1, previous );
		del_from_winner( previous, 0 );
	}

	/* Dont include current number in set */
	/* Add number to second set */
	add_to_winner( previous, 1, input_S[num] );
	construct_set( sum, num+1, previous );
	del_from_winner( previous, 1 );

	return 0;
}

/* vim: set ts=2 sw=2 :*/
