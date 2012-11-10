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
#include "sop.h"
#include "misc.h"
#include "set_next.h"
#include "stack.h"

inline winner_set * initial_winner( void )
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

void add_to_winner( winner_set * winner, int set, int number )
{
	winner->set[set].member[winner->set[set].num++] = number;
	winner->num++;
}

void del_from_winner( winner_set * winner, int set  )
{
	winner->set[set].num--;
	winner->num--;
}

void * pack_winner( winner_set * winner )
{
	void * help = malloc( winner_size * sizeof(int) );
	int i;
	int pos=0;

	MPI_Pack( &winner->result, 1, MPI_INT, help, winner_size*sizeof(int), &pos, MPI_COMM_WORLD );
	MPI_Pack( &winner->num, 1, MPI_INT, help, winner_size*sizeof(int), &pos, MPI_COMM_WORLD );
	for( i=0 ; i<input_a ; i++ )
	{
		MPI_Pack( &winner->set[i].num, 1, MPI_INT, help, winner_size*sizeof(int), &pos, MPI_COMM_WORLD );
		MPI_Pack( winner->set[i].member, input_n, MPI_INT, help, winner_size*sizeof(int), &pos, MPI_COMM_WORLD );
	}
	return help;
}

winner_set * unpack_winner( void * buffer )
{
	winner_set * help = initial_winner();
	int i;
	int pos=0;

	MPI_Unpack( buffer, winner_size*sizeof(int), &pos, &help->result, 1, MPI_INT , MPI_COMM_WORLD );
	MPI_Unpack( buffer, winner_size*sizeof(int), &pos, &help->num, 1, MPI_INT , MPI_COMM_WORLD );
	for( i=0 ; i<input_a ; i++ )
	{
		MPI_Unpack( buffer, winner_size*sizeof(int), &pos, &help->set[i].num, 1, MPI_INT , MPI_COMM_WORLD );
		MPI_Unpack( buffer, winner_size*sizeof(int), &pos, help->set[i].member, input_n, MPI_INT , MPI_COMM_WORLD );
	}
	free(buffer);
	return help;
}

void provide_stack( stack_struct * stack )
{
	MPI_Status status;
	int flag,tmp;
	void * packed;

	while( stack_size(stack)>1 )
	{
		MPI_Iprobe( MPI_ANY_SOURCE, WINNER_ASK, MPI_COMM_WORLD, &flag, &status );
		if(flag)
		{
			MPI_Recv( &tmp, 1, MPI_CHAR, MPI_ANY_SOURCE, WINNER_ASK, MPI_COMM_WORLD, &status);

			packed = pack_winner(stack_bottom(stack));
			MPI_Send( packed, winner_size, MPI_INT, status.MPI_SOURCE, WINNER_SEND, MPI_COMM_WORLD );
			free(packed);
		}
		else return;
	}
}

inline void send_finish( )
{
	char msg=WINNER_FINISH;
	int rank,nr;
	int i;

	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &nr );

	for( i=0 ; i<nr ; i++ )
	{
		if( i!=rank ) MPI_Send( &msg, 1, MPI_CHAR, i, WINNER_FINISH, MPI_COMM_WORLD );
	}
}

inline void send_ask( int proc )
{
	char msg=WINNER_ASK;
	MPI_Send( &msg, 1, MPI_CHAR, proc, WINNER_ASK, MPI_COMM_WORLD );
}

winner_set * get_winner( int source, int flag )
{
	MPI_Status status;
	void * buffer = malloc( winner_size * sizeof(int) );
	
	MPI_Recv( buffer, winner_size, MPI_INT, source, flag, MPI_COMM_WORLD, &status );

	return unpack_winner( buffer );
}
		
int regular_listener( void )
{
	MPI_Status status;
	int flag;

	MPI_Iprobe( MPI_ANY_SOURCE, WINNER_FINISH, MPI_COMM_WORLD, &flag, &status );
	if(flag)
	{
		return 1;
	}
	return 0;
}

void send_max( void )
{
	void * packed; 

	packed = pack_winner( max_winner );
	MPI_Send( packed, winner_size, MPI_INT, 0, WINNER_MAX, MPI_COMM_WORLD );
	free(packed);
}

void recieve_max( void )
{
	int nr;
	winner_set * help;

	MPI_Comm_size( MPI_COMM_WORLD, &nr );
	
	while(--nr)
	{
		help = get_winner( nr, WINNER_MAX );
		if( help->result > max_winner->result )
		{
			clean_winner( max_winner );
			max_winner = help;
		}
		else
		{
			clean_winner( help );
		}
	}
}

int construct_set_helper( stack_struct * stack ) 
{
	winner_set * help;

	while(stack_size( stack ))
	{
		help = stack_top( stack );

		/* All numbers done, do next set*/
		if( help->num == input_n - 1 )
		{
			stack_pop( stack );

			if( help->result == 0 )
			{
				clean_winner(help);
				continue;
			}

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
			continue;
		}

		/* Finish when max result found */
		if( max_winner->result == input_max )
		{
			send_finish();
			stack_destroy( stack );
			return 0;
		}
		
		if( help->result + input_S[help->num] < input_c )
		{
			stack_push( stack, copy_winner(help) );
			add_to_winner( stack_top(stack), 0, input_S[help->num]);
			stack_top(stack)->result += input_S[help->num];
		}

		add_to_winner( help, 1, input_S[help->num]);

		if(stack_size(stack)>1) provide_stack( stack );
		if( regular_listener() )
		{
			stack_destroy( stack );
			return 0;
		}
	}

	stack_destroy( stack );
	return 0;
}

int construct_set()
{
	stack_struct * stack = stack_init();

	stack_push( stack, initial_winner() );
	add_to_winner( stack_top(stack), 1, input_S[0]);
	stack_push( stack, initial_winner() );
	add_to_winner( stack_top(stack), 0, input_S[0]);
	stack_top(stack)->result = input_S[0];

	construct_set_helper( stack );

	recieve_max();

	return 0;
}


int construct_set_others()
{
	send_ask(0);
	winner_set * recived = get_winner( MPI_ANY_SOURCE, WINNER_SEND);
	
	stack_struct * stack = stack_init();
	stack_push( stack, recived );

	construct_set_helper( stack );

	send_max();

	return 0;
}

/* vim: set ts=2 sw=2 :*/
