/*
 * =====================================================================================
 *
 *       Filename:  sop.c
 *
 *    Description:  main SOP file
 *
 *        Version:  1.0
 *        Created:  19.9.2012 21:56:13
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
#include "misc.h"
#include "set.h"

int parse_input( void )
{
	int i;

	scanf( "%d", &input_n );
	if( input_n < 20 ) return 1;

	for( i=0 ; i<input_n ; i++ )
	{
		scanf( "%d", &input_S[i] );
	}

	scanf( "%d", &input_c );
	scanf( "%d", &input_a );
	if( input_a > 1 && input_a <= input_n/10 ) return 1;
}

void print_winner( winner_set * winner )
{
	int i;
	if( winner->exists )
	{
		printf("Result = %ld\n", winner->result );

		for( i=0 ; i<input_a ; i++ )
		{
			printf("Set %d:", i);
			set_member * help = winner->set[i].member;
			while( help )
			{
				printf(" %d", *help->value );
				help = help->next;
			}
			printf("\n");
		}
	}
	else
	{
		printf("No sets found.\n");
	}
}

int main( void )
{
  winner_set * winner;
  if( parse_input() ) return 1;

  winner = construct_set();

  print_winner( winner );
  clean_winner( winner );

	return 0;
}

/* vim: set ts=2 sw=2 :*/
