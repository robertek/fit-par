/*
 * =====================================================================================
 *
 *       Filename:  sop-mpi.c
 *
 *    Description:  mpi implementation helpers
 *
 *        Version:  1.0
 *        Created:  11/11/2012 10:46:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */
#include "sop.h"
#include "set.h"
#include "stack.h"

/*
 * flaten the data struct
 */
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

/*
 * parse data struct from flaten data
 */
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

/*
 * call finish to all other proceses
 */
void send_finish( )
{
	char msg=0;
	int rank,nr;
	int i;

	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &nr );

	for( i=0 ; i<nr ; i++ )
	{
		if( i!=rank ) MPI_Send( &msg, 1, MPI_CHAR, i, WINNER_FINISH, MPI_COMM_WORLD );
	}
}

/*
 * send work asking message
 */
inline void send_ask( int proc )
{
	char msg=color;
	MPI_Send( &msg, 1, MPI_CHAR, proc, WINNER_ASK, MPI_COMM_WORLD );
}

/*
 * recieve computation data
 */
winner_set * get_winner( int source, int flag )
{
	MPI_Status status;
	void * buffer = malloc( winner_size * sizeof(int) );
	
	MPI_Recv( buffer, winner_size, MPI_INT, source, flag, MPI_COMM_WORLD, &status );

	return unpack_winner( buffer );
}
		
/*
 * send computation data with max sum, only caled at the end
 */
inline void send_max( void )
{
	void * packed; 

	packed = pack_winner( max_winner );
	MPI_Send( packed, winner_size, MPI_INT, 0, WINNER_MAX, MPI_COMM_WORLD );
	free(packed);
}

/*
 * collect all max data and set the maximal one
 */
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

/*
 * provide our stack when whe have spare
 */
void provide_stack( stack_struct * stack )
{
	MPI_Status status;
	int flag,tmp;
	void * packed;

	/* only provide spare stack items */
	while( stack_size(stack)>1 )
	{
		MPI_Iprobe( MPI_ANY_SOURCE, WINNER_ASK, MPI_COMM_WORLD, &flag, &status );
		if(flag)
		{
			MPI_Recv( &tmp, 1, MPI_CHAR, MPI_ANY_SOURCE, WINNER_ASK, MPI_COMM_WORLD, &status);

			packed = pack_winner(stack_bottom(stack));
			MPI_Send( packed, winner_size, MPI_INT, status.MPI_SOURCE, WINNER_SEND, MPI_COMM_WORLD );
			free(packed);

			color = BLACK;
		}
		else return;
	}
}

/*
 * handler for special messages, this is done in evry cycle
 */
int regular_listener( void )
{
	MPI_Status status;
	int flag,tmp;

	MPI_Iprobe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status );
	if(flag)
		switch(status.MPI_TAG)
		{
			case WINNER_FINISH :
				return 1;
			case PESEK :
				MPI_Recv( &tmp, 1, MPI_INT, MPI_ANY_SOURCE, PESEK, MPI_COMM_WORLD, &status);
				have_pesek = 1;
				return 0;
		}
	return 0;
}

/*
 * self explanatory
 */
inline void send_pesek( int proc )
{
	char msg=color;
	MPI_Send( &msg, 1, MPI_CHAR, proc, PESEK, MPI_COMM_WORLD );
}

/*
 * ugly but functional dynamic work handler
 */
int ask_for_stack( stack_struct * stack )
{
	int rank,nr,flag,tmp;
	winner_set * recived;
	MPI_Status status;

	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &nr );

	/* do nothing if there is only one proc */
	if( nr == 1 ) return 1;  


	/* dijkstras pesek implemented exactly from the lectures */
	if( rank == 0 )
	{
		color = WHITE;
		send_pesek( 1 );
		have_pesek = 0;
	}
	else
	{
		if( have_pesek )
		{
			send_pesek( (rank+1)%nr );
			color=WHITE;
			have_pesek = 0;
		}
	}

	/* ask for work */
	send_ask( (rank+1)%nr );

	/* ugly,ugly active waiting for job */
	while(1)
	{
		MPI_Iprobe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status );
		if(flag)
			/* check for all possible tags */
			switch(status.MPI_TAG)
			{
				case WINNER_FINISH :
					return 1;
				case WINNER_SEND :
					recived = get_winner( MPI_ANY_SOURCE, WINNER_SEND );
					stack_push( stack, recived );
					return 0;
				case WINNER_DONOTHAVE :
					MPI_Recv( &tmp, 1, MPI_INT, status.MPI_SOURCE, WINNER_DONOTHAVE, MPI_COMM_WORLD, &status);
					send_ask( (rank+1)%nr );
					break;
				case WINNER_ASK :
					MPI_Recv( &tmp, 1, MPI_INT, status.MPI_SOURCE, WINNER_ASK, MPI_COMM_WORLD, &status);
					MPI_Send( &flag, 1, MPI_INT, status.MPI_SOURCE, WINNER_DONOTHAVE, MPI_COMM_WORLD );
					break;
				case PESEK :
					MPI_Recv( &tmp, 1, MPI_INT, MPI_ANY_SOURCE, PESEK, MPI_COMM_WORLD, &status);
					have_pesek = 1;
					break;
			}

		/* another peseks handler */
		if( have_pesek )
		{
			if( rank == 0 )
			{
				if( tmp == WHITE )
				{
					send_finish();
					return 1;
				}
				else
				{
					color = WHITE;
					send_pesek( 1 );
					have_pesek = 0;
				}
			}
			else
			{
				send_pesek( (rank+1)%nr );
				color=WHITE;
				have_pesek = 0;
			}
		}
	}

	return 1;
}

/* vim: set ts=2 sw=2 :*/
