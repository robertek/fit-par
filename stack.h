/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  Basic stack implementation header file
 *
 *        Version:  1.0
 *        Created:  25.10.2012 22:25:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */

#ifndef __stack_h__
#define __stack_h__

#define STACK_SIZE (input_n+2)

typedef struct
{
  int top;
	int bottom;
	winner_set ** array;
} stack_struct;

stack_struct * stack_init();
void stack_destroy( stack_struct * help );
void stack_push( stack_struct * stack, winner_set * help );
void stack_pop( stack_struct * stack );
winner_set * stack_top( stack_struct * stack );
int stack_size( stack_struct * stack );
winner_set * stack_bottom( stack_struct * stack );

#endif

/* vim: set ts=2 sw=2 :*/
