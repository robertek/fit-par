/*
 * =====================================================================================
 *
 *       Filename:  set.h
 *
 *    Description:  header for set
 *
 *        Version:  1.0
 *        Created:  28.9.2012 14:55:58
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Robert David (davidrob@fit.cvut.cz), Vaclav Sajdl (sajdlvac@fit.cvut.cz) 
 *   Organization:  FIT
 *
 * =====================================================================================
 */

#ifndef __set_h__
#define __set_h__

winner_set * initial_winner( void );
void clean_winner( winner_set * winner );

winner_set * copy_winner( winner_set* );

inline void add_to_winner( winner_set*, int set, int number );
inline void del_from_winner( winner_set*, int set );

int construct_set( void );
int construct_set_others( void );

#endif
