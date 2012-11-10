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
#include "sop.h"
#include "misc.h"
#include "set.h"

int parse_input( char * file )
{
	int i;
	int help;
	FILE * fd = fopen( file, "r");

	help = fscanf( fd, "%d", &input_n );
	//if( input_n < 20 ) return 1;

	for( i=0 ; i<input_n ; i++ ) help = fscanf( fd, "%d", &input_S[i] );

	help = fscanf( fd, "%d", &input_c );
	help = fscanf( fd, "%d", &input_a );
	//if( input_a > 1 && input_a <= input_n/10 ) return 1;
	input_max=input_a*(input_c-1);

	fclose(fd);
	return 0;
}

void print_winner( winner_set * winner )
{
	int i,j;
	if( winner->result > 0 )
	{
		printf("Result = %ld\n", winner->result );

		for( i=0 ; i<input_a ; i++ )
		{
			printf("Set %d:", i);

			for( j=0 ; j<winner->set[i].num ; j++ )
				printf(" %d", winner->set[i].member[j] );

			printf("\n");
		}
	}
	else
		printf("No sets found.\n");
}

int main( int argc, char ** argv )
{
	if( parse_input(argv[1]) ) return 1;

	max_winner = initial_winner();

	construct_set();

	print_winner( max_winner );
	clean_winner( max_winner );

	return 0;
}

/* vim: set ts=2 sw=2 :*/
