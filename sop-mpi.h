/*
 * =====================================================================================
 *
 *       Filename:  sop-mpi.h
 *
 *    Description:  mpi implementation helpers header
 *
 *        Version:  1.0
 *        Created:  11/11/2012 10:46:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */

#ifndef __sop_mpi_h__
#define __sop_mpi_h__

void * pack_winner( winner_set * winner );
winner_set * unpack_winner( void * buffer );
void provide_stack( stack_struct * stack );
void send_finish( );
inline void send_ask( int proc );
int regular_listener( void );
inline void send_max( void );
void recieve_max( void );
int ask_for_stack( stack_struct * stack );
winner_set * get_winner( int source, int flag );

#endif

/* vim: set ts=2 sw=2 :*/
