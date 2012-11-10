/*
 * =====================================================================================
 *
 *       Filename:  sop.h
 *
 *    Description:  global SOP definitions 
 *
 *        Version:  1.0
 *        Created:  19.9.2012 22:00:12
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */

#ifndef __sop_h__
#define __sop_h__

#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

#define MAX_N 100

#define WINNER_ASK 1
#define WINNER_SEND 2
#define WINNER_FINISH 3
#define WINNER_MAX 4

int input_n;
int input_max;
int input_S[MAX_N];
int input_c;
int input_a;
int winner_size;

typedef struct
{
	int num;
	int * member;
} set_struct;

typedef struct
{
	int result;
	int num;
	set_struct * set;
} winner_set;

winner_set * max_winner;

#endif 

/* vim: set ts=2 sw=2 :*/
