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

/* maximum input size */
#define MAX_N 100

/* mpi tag defines */
#define WINNER_ASK 1
#define WINNER_SEND 2
#define WINNER_FINISH 3
#define WINNER_MAX 4
#define WINNER_DONOTHAVE 5
#define PESEK 6

/* colors for dijkstra peseks algorithm */
#define WHITE 0
#define BLACK 1

/* global input variables */
int input_n;
int input_max;
int input_S[MAX_N];
int input_c;
int input_a;
int winner_size;

/* Dijkstra pesek color */
int color;
int have_pesek;

/* set structs  */
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

/* global set with max sum */
winner_set * max_winner;

#endif 

/* vim: set ts=2 sw=2 :*/
