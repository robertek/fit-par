/*
 * =====================================================================================
 *
 *       Filename:  sop-mpi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/11/2012 10:46:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "sop.h"
#include "set.h"
#include "stack.h"

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
		/* handle realy slow procs*/
		MPI_Send( &nr, 1, MPI_INT, nr, WINNER_MAX, MPI_COMM_WORLD );

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

int ask_for_stack( stack_struct * stack )
{
	int rank,nr;

	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &nr );

	/* TODO */

	return 1;
}
