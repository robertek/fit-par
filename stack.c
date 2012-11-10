/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  easy stack implemenatation
 *
 *        Version:  1.0
 *        Created:  25.10.2012 21:37:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "sop.h"
#include "misc.h"
#include "stack.h"


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
	stack->top = (stack->top-1)%STACK_SIZE;
}

winner_set * stack_top( stack_struct * stack )
{
	return stack->array[stack->top];
}

int stack_size( stack_struct * stack )
{
	return (stack->top - stack->bottom + 1)%STACK_SIZE;
}

winner_set * stack_bottom( stack_struct * stack )
{
	int help = stack->bottom;
	stack->bottom = (stack->bottom+1)%STACK_SIZE;
	return stack->array[help];
}
