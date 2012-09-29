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

#define MAX_N 100

int input_n;
int input_max;
int input_S[MAX_N];
int input_c;
int input_a;

typedef struct
{
	int num;
	int * member;
} set_struct;

typedef struct
{
	long result;
	set_struct * set;
} winner_set;

#endif 

/* vim: set ts=2 sw=2 :*/
