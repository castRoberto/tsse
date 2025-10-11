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


/** \brief Implementation file for priority queue module
 **
 ** This module implements a priority queue using a heap data structure.
 ** The implementation is based on the book "Introduction to Algorithms", 3rd Edition,
 ** by Cormen, Leiserson, Rivest, and Stein, specifically from Chapter 6, Section 5.
 **
 ** \addtogroup priority_queue module
 ** \author Roberto Castro Beltran <
 ** @{ */

/********************** inclusions *******************************************/

#include "priority_queue.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/********************** macros and definitions *******************************/
#define ROOT_INDEX                0
#define NO_ELEMENTS_IN_QUEUE      0
#define NULL_VALUE                0
#define INITIAL_INSERTION_INDEX   0

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

static size_t _get_parent (size_t index);

static size_t _get_left (size_t index);

static size_t _get_right (size_t index);

static void _swap (priority_queue_t* pq, size_t i, size_t j);

static void _heapify (priority_queue_t* pq, size_t index);

static void _bubble_up (priority_queue_t* pq, size_t index);

/********************** internal data definition *****************************/


/********************** external data definition *****************************/


/********************** internal functions definition ************************/

static size_t _get_parent (size_t index) {

	return (index - 1) / 2;

}

static size_t _get_left (size_t index) {

	return 2 * index + 1;

}

static size_t _get_right (size_t index) {

	return 2 * index + 2;

}

#ifdef PQ_DEBUG

static int _power_of_two (int exp) {

  return 1 << exp; // 2^exp

}

static uint16_t _calculate_level (size_t size) {

  // Implement log2(size) using bitwise operations
  unsigned level = 0;
  while (size >>= 1) level++;
  return level;

}

#endif


// Function to swap two elements in an array
static void _swap (priority_queue_t* pq, size_t i, size_t j) {

  pq_node_t temp_node = pq->nodes[i];
  pq->nodes[i] = pq->nodes[j];
  pq->nodes[j] = temp_node;

}


static bool _should_update_by_order (const pq_node_t* candidate,
                                     const pq_node_t* parent) {

  return (candidate->priority == parent->priority &&
          candidate->insertion_index < parent->insertion_index);

}


static bool _child_better_than_parent (const priority_queue_t* pq,
                                        size_t parent,
                                        size_t candidate) {

  bool is_better = false;

  if (parent != candidate) {

    const pq_node_t* c = &pq->nodes[candidate]; // Candidate node
    const pq_node_t* p = &pq->nodes[parent]; // Parent node

    if (PQ_MAX_PRIORITY_QUEUE == pq->type) {

      is_better =
        (c->priority > p->priority || _should_update_by_order (c, p));

    } else { // MIN_PRIORITY_QUEUE

      is_better =
        (c->priority < p->priority || _should_update_by_order (c, p));

    }

  }

	return is_better;

}


static void _heapify (priority_queue_t* pq, size_t index) {

	size_t child_left = _get_left (index);
	size_t child_right = _get_right (index);
	size_t best = index;

	if (child_left < pq->size && _child_better_than_parent (pq, best, child_left)) {

		best = child_left;

	}

	if (child_right < pq->size && _child_better_than_parent (pq, best, child_right)) {

		best = child_right;

	}

	if (best != index) {

		_swap (pq, index, best);
		_heapify (pq, best);

	}

}


static void _bubble_up (priority_queue_t* pq, size_t index) {

  while (index > 0 && _child_better_than_parent(pq, _get_parent(index), index)) {

    size_t parent = _get_parent(index);

    _swap(pq, index, parent);

    index = parent;

  }

}

/********************** external functions definition ************************/

priority_queue_t* pq_create (void* memory_pool, size_t capacity, pq_type_t type) {

	priority_queue_t* pq = NULL;

	if (NULL != memory_pool && capacity > NO_ELEMENTS_IN_QUEUE) {

		pq = (priority_queue_t*)memory_pool;

		// Initialize the queue
		pq->nodes = (pq_node_t*)((char*)memory_pool + sizeof(priority_queue_t));
		pq->size = NO_ELEMENTS_IN_QUEUE;
    pq->type = type;
		pq->capacity = capacity;
    pq->next_insertion_index = INITIAL_INSERTION_INDEX;

    memset (pq->nodes, NULL_VALUE, capacity * sizeof(pq_node_t));

	}

	return pq;

}


bool pq_insert (priority_queue_t* pq, void* data, uint16_t priority) {

	bool successful = false;

	if (NULL != pq && pq->size < pq->capacity && NULL != data) {

    pq->nodes[pq->size].data = data;
    pq->nodes[pq->size].priority = priority;
    pq->nodes[pq->size].insertion_index = pq->next_insertion_index++;

    _bubble_up (pq, pq->size);

    pq->size++;

    successful = true;

	}

	return successful;

}


void* pq_peek (priority_queue_t* pq) {

  void* data = NULL;

  if (NULL != pq && pq->size > NO_ELEMENTS_IN_QUEUE) {

    data = pq->nodes[ROOT_INDEX].data;

  }

  return data;

}


void* pq_extract (priority_queue_t* pq) {

	void* data = NULL;

	if (NULL != pq && pq->size > NO_ELEMENTS_IN_QUEUE) {

    data = pq->nodes[ROOT_INDEX].data;

    pq->nodes[ROOT_INDEX] = pq->nodes[pq->size - 1];
    pq->size--;

    if (pq->size > NO_ELEMENTS_IN_QUEUE) {

      _heapify (pq, ROOT_INDEX);

    }

	}

	return data;

}


bool pq_is_empty (priority_queue_t* pq) {

	bool is_empty = true;

	if (NULL != pq) {

		is_empty = pq->size == NO_ELEMENTS_IN_QUEUE;

	}

	return is_empty;

}


size_t pq_size (priority_queue_t* pq) {

	size_t size = 0;

	if (NULL != pq) {

		size = pq->size;

	}

	return size;

}


void pq_print_priority_queue (priority_queue_t* pq) {

#ifdef PQ_DEBUG

	if (NULL != pq) {

		uint16_t levels = _calculate_level (pq->size);

		uint16_t current_level = 0;
		size_t first_node_in_level = 0;
		size_t last_node_in_level = 0;
		uint16_t space_between_nodes = 0;
		uint16_t offset_spaces = 0;


		printf("Priority Queue as Tree:\n\n");

		for (size_t i = 1; i <= pq->size; i++) {

			current_level = _calculate_level (i);

			first_node_in_level = _power_of_two (current_level);

			last_node_in_level = 2 * first_node_in_level - 1;

			if (i == first_node_in_level) {

				offset_spaces = _power_of_two (levels - current_level); // 2^(l - n)

				printf ("%*s%d", offset_spaces, " ", pq->nodes[i-1].priority);

				fflush (stdout);

			} else {

				space_between_nodes = (2 * offset_spaces) - 1;

				printf ("%*s%d", space_between_nodes, " ", pq->nodes[i-1].priority);

				fflush (stdout);

			}


			if (i == last_node_in_level || i == pq->size) {

				printf("\n");

			}

		}

		printf("\n");

	} else {

		printf("Queue empty or NULL");

	}

#else

  // Debug functionality is disabled
  (void)pq; // Suppress unused parameter warning

#endif

}

/********************** end of file ******************************************/
