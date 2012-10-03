/*
 * =====================================================================================
 *
 *       Filename:  set_next.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29.9.2012 18:12:39
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
		
#include "sop.h"
#include "set.h"
#include "misc.h"

int construct_last_set( int sum, int num, int set, winner_set * previous, winner_set * last_set )
{
	/* All numbers done */
	if( num == last_set->set[set].num )
	{
		previous->result = sum + last_set->result;

		if( previous->result > max_winner->result )
		{
			clean_winner( max_winner );
			max_winner = copy_winner( previous );
		}
		return 0;
	}

	if( max_winner->result == input_max ) return 0;

	/* Include current number, but check if sum is <c */
	if( sum + last_set->set[set].member[num] < input_c && previous->set[set].num < last_set->set[0].num )
	{
		add_to_winner( previous, set, last_set->set[set].member[num] );
		construct_last_set( sum + last_set->set[set].member[num], num+1, set, previous, last_set );
		del_from_winner( previous, set );
	}

	/* Dont include current number in set */
	construct_last_set( sum, num+1, set, previous, last_set );

	return 0;
}

int construct_next_set( int sum, int num, int set, winner_set * previous, winner_set * last_set )
{
	/* All numbers done, do next set*/
	if( num == last_set->set[set].num )
	{
		if( sum == 0 ) return 0;

		previous->result = sum + last_set->result;
		winner_set * help = copy_winner(previous);
		help->set[set+1].num = 0;
		if( set == input_a-2 )
		{
			construct_last_set( 0, 0, set+1, help, previous );
		}
		else
		{
			construct_next_set( 0, 0, set+1, help, previous );
		}
		clean_winner( help );
		return 0;
	}

	if( max_winner->result == input_max ) return 0;

	/* Include current number, but check if sum is <c */
	if( sum + last_set->set[set].member[num] < input_c && previous->set[set].num < last_set->set[0].num )
	{
		add_to_winner( previous, set, last_set->set[set].member[num] );
		construct_next_set( sum + last_set->set[set].member[num], num+1, set, previous, last_set );
		del_from_winner( previous, set );
	}

	/* Dont include current number in set */
	/* Add number to second set */
	add_to_winner( previous, set+1, last_set->set[set].member[num] );
	construct_next_set( sum, num+1, set, previous, last_set );
	del_from_winner( previous, set+1 );

	return 0;
}
