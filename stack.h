/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.10.2012 22:25:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

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
int stack_notempty( stack_struct * stack );
winner_set * stack_bottom( stack_struct * stack );
