/*
 * =====================================================================================
 *
 *       Filename:  sop-mpi.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/11/2012 10:46:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

void * pack_winner( winner_set * winner );
winner_set * unpack_winner( void * buffer );
void provide_stack( stack_struct * stack );
inline void send_finish( );
inline void send_ask( int proc );
int regular_listener( void );
void send_max( void );
void recieve_max( void );
int ask_for_stack( stack_struct * stack );
winner_set * get_winner( int source, int flag );
