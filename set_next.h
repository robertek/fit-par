/*
 * =====================================================================================
 *
 *       Filename:  set_next.h
 *
 *    Description:  set_next header
 *
 *        Version:  1.0
 *        Created:  29.9.2012 18:17:36
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */

#ifndef __set_next_h__
#define __set_next_h__

int construct_last_set( int sum, int num, int set, winner_set * previous, winner_set * last_set );
int construct_next_set( int sum, int num, int set, winner_set * previous, winner_set * last_set );

#endif
