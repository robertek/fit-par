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
int input_S[MAX_N];
int input_c;
int input_a;

struct set_member_struct
{
	int * value;
	struct set_member_struct * next;
};

typedef struct set_member_struct set_member;

typedef struct
{
	int num;
	set_member * member;
} set_struct;

typedef struct
{
	int exists;
	long result;
	set_struct * set;
} winner_set;

#endif 

/* vim: set ts=2 sw=2 :*/
