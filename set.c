/*
 * =====================================================================================
 *
 *       Filename:  set.c
 *
 *    Description:  functions to walk first set and helpers
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

#include "sop.h"
#include "set_next.h"
#include "stack.h"
#include "sop-mpi.h"

/*
 * winner_set allocator
 */
winner_set * initial_winner( void )
{
	winner_set * help = (winner_set*) malloc( sizeof(winner_set) );

	help->result = 0;
	help->num = 0;
	help->set = (set_struct*) malloc( input_a * sizeof(set_struct) );

	int i;
	for( i=0 ; i<input_a ; i++ )
	{
		help->set[i].num = 0; 
		help->set[i].member = (int*) calloc( input_n,  sizeof(int) );
	}
	return help;
}

/*
 * winner_set deallocator
 */
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

/*
 * winner_set deep copy
 */
winner_set * copy_winner( winner_set * previous )
{
	winner_set * help = initial_winner(); 

	help->result = previous->result;
	help->num = previous->num;

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
	winner->num++;
}

inline void del_from_winner( winner_set * winner, int set  )
{
	winner->set[set].num--;
	winner->num--;
}

/*
 * complete worker of first set, stack based, paraleled
 */
int construct_set_helper( stack_struct * stack ) 
{
	winner_set * help;

	while(stack_size( stack ))
	{
		help = stack_top( stack );

		/* All numbers done, do next set*/
		if( help->num == input_n )
		{
			stack_pop( stack );

			/* do not continue in corner case when no item in set */
			if( help->result == 0 || help->set[1].num == 0 )
			{
				clean_winner(help);
				if( stack_size(stack)>1 ) provide_stack( stack );
				if( regular_listener() ) break;
				if( ! stack_size(stack) && ask_for_stack( stack ) ) break ;
				continue;
			}

			/* continue working on next set (set_next.c) 
			 * provide one struct as reference and one as working  */
			winner_set * help2 = copy_winner( help );
			help2->set[1].num = 0;
			if( input_a == 2 )
			{
				construct_last_set( 0, 0, 1, help2, help );
			}
			else
			{
				construct_next_set( 0, 0, 1, help2, help );
			}
			clean_winner(help);
			clean_winner(help2);

			/* some paralelization helpers */
			if( stack_size(stack)>1 ) provide_stack( stack );
			if( regular_listener() ) break;
			if( ! stack_size(stack) && ask_for_stack( stack ) ) break ;
			continue;
		}

		/* Finish when max result found */
		if( max_winner->result == input_max )
		{
			send_finish();
			break;
		}
		
		/* add item to set only if sum < input_c */
		if( help->result + input_S[help->num] < input_c )
		{
			stack_push( stack, copy_winner(help) );
			add_to_winner( stack_top(stack), 0, input_S[help->num]);
			stack_top(stack)->result += input_S[help->num];
		}

		/* use existing stack content to add item to second set */
		add_to_winner( help, 1, input_S[help->num]);

		/* some paralelization helpers */
		if( stack_size(stack)>1 ) provide_stack( stack );
		if( regular_listener() ) break;
		if( ! stack_size(stack) && ask_for_stack( stack ) ) break ;
	}

	stack_destroy( stack );
	return 0;
}

/**
 * set constructor for rank 0
 */
int construct_set()
{
	stack_struct * stack = stack_init();

	/* create initail jobs */
	stack_push( stack, initial_winner() );
	add_to_winner( stack_top(stack), 1, input_S[0]);
	stack_push( stack, initial_winner() );
	add_to_winner( stack_top(stack), 0, input_S[0]);
	stack_top(stack)->result = input_S[0];

	/* continue working */
	construct_set_helper( stack );

	/* collect all max values and set the best */
	recieve_max();

	return 0;
}

/**
 * set constructor for other ranks
 */
int construct_set_others()
{
	stack_struct * stack = stack_init();

	/* ask for job and start working */
	if( ! ask_for_stack( stack ) ) 
		construct_set_helper( stack );
	else
		stack_destroy( stack );

	/* send my max value */
	send_max();

	return 0;
}

/* vim: set ts=2 sw=2 :*/
