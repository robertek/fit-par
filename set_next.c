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

winner_set * construct_last_set( int sum, int num, int set, winner_set * previous, winner_set * last_set )
{
	/* All numbers done, do next set*/
	if( num == last_set->set[set].num )
	{
		previous->result += sum;
		previous->exists = 1;
		return previous;
	}

	/* Dont include current number in set */
	winner_set * winner1 = copy_winner( previous );
	winner1 = construct_last_set( sum, num+1, set, winner1, last_set );

	/* Include current number, but check if sum is <c */
	if( sum + last_set->set[set].member[num] < input_c )
	{
		winner_set * winner2 = copy_winner( previous );
		add_to_winner( winner2, set, last_set->set[set].member[num] );
		winner2 = construct_last_set( sum + last_set->set[set].member[num], num+1, set, winner2, last_set );

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

winner_set * construct_next_set( int sum, int num, int set, winner_set * previous, winner_set * last_set )
{
	/* All numbers done, do next set*/
	if( num == last_set->set[set].num )
	{
		previous->result += sum;
		winner_set * help = copy_winner(previous);
		help->set[set+1].num = 0;
		if( set == input_a-2 )
		{
			help = construct_last_set( 0, 0, set+1, help, previous );
		}
		else
		{
			help = construct_next_set( 0, 0, set+1, help, previous );
		}
		clean_winner( previous );
		return help;
	}

	/* Dont include current number in set */
	winner_set * winner1 = copy_winner( previous );
	/* Add number to second set */
	add_to_winner( winner1, set+1, last_set->set[set].member[num] );
	winner1 = construct_next_set( sum, num+1, set, winner1, last_set );

	/* Include current number, but check if sum is <c */
	if( sum + last_set->set[set].member[num] < input_c )
	{
		winner_set * winner2 = copy_winner( previous );
		add_to_winner( winner2, set, last_set->set[set].member[num] );
		winner2 = construct_next_set( sum + last_set->set[set].member[num], num+1, set, winner2, last_set );

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
