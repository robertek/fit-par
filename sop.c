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

#include "sop.h"

int parse_input( void )
{
	int i;

	scanf( "%d", input_n );
	if( input_n < 20 ) return 1;

	for( i=0 ; i<input_n ; i++ )
	{
		scanf( "%d", input_S[i] );
	}

	scanf( "%d", input_c );
	scanf( "%d", input_a );
	if( input_a > 1 && input_a <= input_n/10 ) return 1;
}


int main( void )
{
	if( parse_input() ) return 1;


}

/* vim: set ts=2 sw=2 :*/
