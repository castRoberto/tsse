/************************************************************************************************
Copyright (c) <2024>, <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

/** \brief Header file for priority queue module
 **
 ** This module implements a priority queue using a heap data structure.
 ** The implementation is based on the book "Introduction to Algorithms", 3rd Edition,
 ** by Cormen, Leiserson, Rivest, and Stein, specifically from Chapter 6, Section 5.
 **
 ** \addtogroup priority_queue module
 ** \author Roberto Castro Beltran <
 ** @{ */

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/********************** typedef **********************************************/

typedef enum {

  PQ_UNKNOWN_PRIORITY_QUEUE = 0,

  PQ_MIN_PRIORITY_QUEUE,
  PQ_MAX_PRIORITY_QUEUE,

} pq_type_t;

// Structure for priority queue elements
typedef struct {

  uint16_t priority;
  size_t insertion_index;
  void* data;

} pq_node_t;


// Structure for priority queue
typedef struct {

  pq_node_t* nodes;
  size_t size;
  size_t capacity;
  pq_type_t type;
  size_t next_insertion_index;

} priority_queue_t;

/********************** macros ***********************************************/
#define PQ_MEMORY_SIZE(capacity) (sizeof(priority_queue_t) + capacity * sizeof(pq_node_t))

/********************** external data declaration ****************************/


/********************** external functions declaration ***********************/

priority_queue_t* pq_create (void* memory_pool, size_t capacity, pq_type_t type); // O(1)

bool pq_insert (priority_queue_t* pq, void* data, uint16_t priority); // O(log_2(n))

void* pq_peek (priority_queue_t* pq); // O(1)

void* pq_extract (priority_queue_t* pq); // O(log_2(n))

bool pq_is_empty (priority_queue_t* pq);

size_t pq_size (priority_queue_t* pq);

void pq_print_priority_queue (priority_queue_t* pq);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* __PRIORITY_QUEUE_H__ */

/********************** end of file ******************************************/
