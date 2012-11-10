/*
 * =====================================================================================
 *
 *       Filename:  misc.c
 *
 *    Description:  some helper functions 
 *
 *        Version:  1.0
 *        Created:  28.9.2012 14:50:05
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */
#include "sop.h"

void clean_winner( winner_set * winner )
{
	int i;
	for( i=0 ; i<input_a ; i++ )
	{
		free( winner->set[i].member );
	}
	free( winner->set );
	free( winner );
	return;
}

/* vim: set ts=2 sw=2 :*/
