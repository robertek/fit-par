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


winner_set * copy_winner( winner_set * previous )
{

}

winner_set * construct_set( long sum, int num, winner_set * previous )
{

	if( num == input_n )
	{
		return previous;
	}

	winner_set * winner1 = previous;
	winner1 = construct_set( 0, 1);

	if( sum + input_S[num] < input_c )
	{
		winner_set * winner2 = copy_winner( previous );
		add_to_winner( &input_S[num] );
		winner2 = construct_set( sum + input_S[num], 1, winner2 );

		if( winner1->exists && winner2->exists )
			if( winner1->result > winner2->result )
			{
				clean_winner( winner2 );
				return winner1;
			}
			else 
			{
				clean_winner( winner1 );
				return winner2;
			}
		else if( winner1->exists )
		{
			clean_winner( winner2 );
			return winner1;
		}
		else if( winner2->exists )
		{
			clean_winner( winner1 );
			return winner2;
		}
		else
		{
			clean_winner( winner1 );
			clean_winner( winner2 );
			return 0;
		}
	}
	else
	{
		return winner1;
	}
}

/* vim: set ts=2 sw=2 :*/
