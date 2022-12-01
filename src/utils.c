/* utils.c - Some handy tools.

   Copyright (c) 2021 - Monaco F. J. <monaco@usp.br> 

   This file is part of Snaskii

   Snaskii is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sys/time.h>
#include "utils.h"

/* Subtract the ‘struct timeval’ values X and Y, storing the result in RESULT.
   Return 1 if the difference is negative, otherwise 0. 

   Attribution: this function is reproduced from GNU Libc Manual:
   https://www.gnu.org/software/libc/manual/html_node/Calculating-Elapsed-Time.html
*/

int
timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

/**
 * The functions below allows to create simples, double linked
 * lists, which can be used as queues.
 * tail: begin of the list, tail of the snake
 * head: end of the list, head of the snake
 * format: tail -> ... -> head
*/
list_t *newlist(){
    list_t *l;
    l = (list_t*) malloc(sizeof(list_t));
    l->head = NULL;
    l->tail = NULL;
    point_t snakehead;
    snakehead.type = 'O';
    snakehead.x = 0;
    snakehead.y = 0;
    insert(l, snakehead);
    return l;
}

void insert(list_t* l, point_t p) {

    node_t *new = (node_t *)malloc(sizeof(node_t)); 
    new->next = NULL;
    new->p = p;

    /* first node of the list */
    if(l->tail == NULL){
        new->prev = NULL;
        l->tail = new;
    }else{
        new->prev = l->head;
        l->head->next = new;
    }

    l->head = new;
}

void pop(list_t *l){
    node_t *node = l->tail;
    l->tail = l->tail->next;
    free(node);
}

void freeList(list_t *l) {
	if(l != NULL) {
		node_t *aux = l->tail;
		while(aux != NULL) {
			l->tail = aux->next;
			free(aux);
			aux = l->tail;
		}
		free(l);
	}
}


