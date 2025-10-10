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
#define MAX_ELEMENT_INDEX 0
#define NO_ELEMENTS_IN_QUEUE 0
#define NULL_VALUE 0

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

static size_t _get_parent (size_t index);

static size_t _get_left (size_t index);

static size_t _get_right (size_t index);

static void _swap (priority_queue_t* pq, size_t i, size_t j);

static void _max_heapify (priority_queue_t* pq, size_t index);

static void _increase_priority (priority_queue_t* pq, size_t index, int16_t priority);

static int _power_of_two (int exp);

static uint16_t _calculate_level (size_t size);

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

static int _power_of_two (int exp) {

  return 1 << exp; // 2^exp

}

static uint16_t _calculate_level (size_t size) {

  return (uint16_t) log2 (size);

}


// Function to swap two elements in an array
static void _swap (priority_queue_t* pq, size_t i, size_t j) {

  pq_node_t temp_node = pq->nodes[i];
  pq->nodes[i] = pq->nodes[j];
  pq->nodes[j] = temp_node;

}


static bool _should_update_by_order (priority_queue_t* pq,
                                     size_t current_largest,
                                     size_t candidate) {

  return (pq->nodes[candidate].priority ==
            pq->nodes[current_largest].priority
          &&
          pq->nodes[candidate].insertion_index <
            pq->nodes[current_largest].insertion_index);

}


static bool _check_update_largest_node (priority_queue_t* pq,
                                        size_t current_largest,
                                        size_t candidate) {

	return (pq->nodes[candidate].priority > pq->nodes[current_largest].priority ||
			    _should_update_by_order (pq, current_largest, candidate));

}


static void _max_heapify (priority_queue_t* pq, size_t index) {

	size_t child_left = _get_left (index);
	size_t child_right = _get_right (index);
	size_t largest;

	if (child_left < pq->size && _check_update_largest_node (pq, index, child_left)) {

		largest = child_left;

	} else {

		largest = index;

	}

	if (child_right < pq->size && _check_update_largest_node (pq, largest, child_right)) {

		largest = child_right;

	}

	if (largest != index) {

		_swap (pq, index, largest);
		_max_heapify (pq, largest);

	}

}


static void _increase_priority (priority_queue_t* pq, size_t index, int16_t priority) {

	if (priority > pq->nodes[index].priority) {

		pq->nodes[index].priority = priority;

		while (index > 0 && _check_update_largest_node (pq, _get_parent(index), index)) {

			size_t parent = _get_parent(index);

			_swap(pq, index, parent);

			index = parent;

		}

	}

}

/********************** external functions definition ************************/

priority_queue_t* pq_create (void* memory_pool, size_t capacity, pq_type_t type) {

	priority_queue_t* pq = NULL;

	// Suppress unused parameter warning
	(void)type;

	if (NULL != memory_pool && capacity > NO_ELEMENTS_IN_QUEUE) {

		pq = (priority_queue_t*)memory_pool;

		// Initialize the queue
		pq->nodes = (pq_node_t*)((char*)memory_pool + sizeof(priority_queue_t));
		pq->size = NO_ELEMENTS_IN_QUEUE;
    pq->type = MAX_QUEUE;
		pq->capacity = capacity;
    pq->next_insertion_index = 0;

    memset (pq->nodes, NULL_VALUE, capacity * sizeof(pq_node_t));

	}

	return pq;

}


bool pq_insert (priority_queue_t* pq, void* data, uint16_t priority) {

	bool successful = false;

	if (NULL != pq && pq->size < pq->capacity && NULL != data) {

    pq->nodes[pq->size].data = data;
    pq->nodes[pq->size].priority = 0; // - inf
    pq->nodes[pq->size].insertion_index = pq->next_insertion_index++;

    _increase_priority (pq, pq->size, priority);

    pq->size++;

    successful = true;

	}

	return successful;

}


void* pq_peek (priority_queue_t* pq) {

  void* data = NULL;

  if (NULL != pq && pq->size > 0) {

    data = pq->nodes[0].data;

  }

  return data;

}


void* pq_extract (priority_queue_t* pq) {

	void* data = NULL;

	if (NULL != pq && pq->size > 0) {

    data = pq->nodes[MAX_ELEMENT_INDEX].data;

    pq->nodes[MAX_ELEMENT_INDEX] = pq->nodes[pq->size - 1];
    pq->size--;

    if (pq->size > 0) {

      _max_heapify (pq, 0);

    }

	}

	return data;

}


bool pq_is_empty (priority_queue_t* pq) {

	bool is_empty = true;

	if (NULL != pq) {

		is_empty = pq->size == 0;

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

}

/********************** end of file ******************************************/
