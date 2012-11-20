/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  Basic stack implementation
 *
 *        Version:  1.0
 *        Created:  25.10.2012 21:37:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */
#include "sop.h"
#include "stack.h"
#include "set.h"

/*
 * all functions are self explained by its name
 */
stack_struct * stack_init()
{
	stack_struct * help = (stack_struct*) malloc( sizeof(stack_struct) );
	help->top= STACK_SIZE-1;
	help->bottom=0;
	help->array = (winner_set**) malloc( STACK_SIZE * sizeof(winner_set) );
	return help;
}

void stack_destroy( stack_struct * help )
{
	if(help)
	{
		while(stack_size(help))
		{
			clean_winner(stack_top(help));
			stack_pop(help);
		}
		free(help->array);
		free(help);
	}
}

void stack_push( stack_struct * stack, winner_set * help )
{
	stack->top = (stack->top+1)%STACK_SIZE;
	stack->array[stack->top] = help;
}

void stack_pop( stack_struct * stack )
{
	stack->top = stack->top>0 ? stack->top-1: STACK_SIZE-1;
}

winner_set * stack_top( stack_struct * stack )
{
	return stack->array[stack->top];
}

int stack_size( stack_struct * stack )
{
	return (stack->top - stack->bottom + 1)%STACK_SIZE;
}

/*
 * only one nonstandard stack function that return last stack item and delete it
 * this is how stack division work for our sw
 */
winner_set * stack_bottom( stack_struct * stack )
{
	int help = stack->bottom;
	stack->bottom = (stack->bottom+1)%STACK_SIZE;
	return stack->array[help];
}

/* vim: set ts=2 sw=2 :*/
