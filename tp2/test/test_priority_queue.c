/************************************************************************************************
Copyright (c) <2025>, <copyright holders>

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

/** \brief Fichero de pruebas unitarias del modulo de cola de prioridad
 **
 ** Pruebas a realizar:
 ** - Crear una cola de prioridad y verificar que inicia vacia
 ** - Insertar elementos en una cola de prioridad maxima y ver que se extraen en orden de mayor a menor prioridad
 ** - Insertar elementos en una cola de prioridad minima y ver que se extraen en orden de menor a mayor prioridad
 ** - Intentar insertar elementos en una cola llena y verificar que no se insertan
 ** - Insertar varios elementos con la misma prioridad y verificar que se extraen en orden de inserción
 ** - Comprobar que peek devuelve el elemento con mayor prioridad sin extraerlo de la cola
 ** - Validar comportamiento ante nulos
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "priority_queue.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
typedef struct {
  uint8_t value;
  uint16_t priority;
} data_t;
/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

#define ELEMENTS_NUMBER 10
static uint8_t _pq_memory_pool [PQ_MEMORY_SIZE(ELEMENTS_NUMBER)];
priority_queue_t* pq = NULL;

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/**
 *Helper to create queue each test
 */
static void _create_queue(pq_type_t type) {

  pq = pq_create(_pq_memory_pool, ELEMENTS_NUMBER, type);
  TEST_ASSERT_NOT_NULL(pq);

}

/* === Public function implementation ========================================================== */

void setUp(void) {

}

void tearDown(void) {

}


void test_crear_una_cola_de_prioridad_y_verificar_que_inicia_vacia (void) {

  _create_queue(PQ_MAX_PRIORITY_QUEUE);
  TEST_ASSERT_TRUE (pq_is_empty (pq));
  TEST_ASSERT_EQUAL (0U, pq_size (pq));

}

void test_insertar_elementos_en_una_cola_de_prioridad_maxima_y_verificar_que_se_extraen_en_orden_de_mayor_a_menor_prioridad (void) {

  data_t data1 = { .value = 1, .priority = 50 };
  data_t data2 = { .value = 2, .priority = 30 };
  data_t data3 = { .value = 3, .priority = 65 };
  data_t data4 = { .value = 4, .priority = 10 };

  _create_queue(PQ_MAX_PRIORITY_QUEUE);
  TEST_ASSERT_TRUE(pq_insert(pq, &data1.value, data1.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data2.value, data2.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data3.value, data3.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data4.value, data4.priority));

  TEST_ASSERT_FALSE(pq_is_empty(pq));
  TEST_ASSERT_EQUAL(4U, pq_size(pq));

  TEST_ASSERT_EQUAL(3, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(3U, pq_size(pq));

  TEST_ASSERT_EQUAL(1, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(2U, pq_size(pq));

  TEST_ASSERT_EQUAL(2, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(1U, pq_size(pq));

  TEST_ASSERT_EQUAL(4, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(0U, pq_size(pq));

}


void test_insertar_elementos_en_una_cola_de_prioridad_minima_y_verificar_que_se_extraen_en_orden_de_menor_a_mayor_prioridad (void) {

  data_t data1 = { .value = 1, .priority = 50 };
  data_t data2 = { .value = 2, .priority = 30 };
  data_t data3 = { .value = 3, .priority = 65 };
  data_t data4 = { .value = 4, .priority = 10 };

  _create_queue(PQ_MIN_PRIORITY_QUEUE);
  TEST_ASSERT_TRUE(pq_insert(pq, &data1.value, data1.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data2.value, data2.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data3.value, data3.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data4.value, data4.priority));

  TEST_ASSERT_FALSE(pq_is_empty(pq));
  TEST_ASSERT_EQUAL(4U, pq_size(pq));

  TEST_ASSERT_EQUAL(4, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(3U, pq_size(pq));

  TEST_ASSERT_EQUAL(2, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(2U, pq_size(pq));

  TEST_ASSERT_EQUAL(1, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(1U, pq_size(pq));

  TEST_ASSERT_EQUAL(3, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(0U, pq_size(pq));

}


void test_intentar_insertar_elementos_en_una_cola_llena_y_verificar_que_no_se_insertan (void) {

  data_t data[ELEMENTS_NUMBER + 2] = {
    { .value = 1, .priority = 10 },
    { .value = 2, .priority = 20 },
    { .value = 3, .priority = 30 },
    { .value = 4, .priority = 40 },
    { .value = 5, .priority = 50 },
    { .value = 6, .priority = 60 },
    { .value = 7, .priority = 70 },
    { .value = 8, .priority = 80 },
    { .value = 9, .priority = 90 },
    { .value = 10, .priority = 100 },
    { .value = 11, .priority = 110 }, // Extra element
    { .value = 12, .priority = 120 }  // Extra element
  };

  _create_queue(PQ_MAX_PRIORITY_QUEUE);
  for (uint8_t i = 0; i < ELEMENTS_NUMBER; i++) {

    TEST_ASSERT_TRUE(pq_insert(pq, &data[i].value, data[i].priority));

  }

  TEST_ASSERT_FALSE(pq_is_empty(pq));
  TEST_ASSERT_EQUAL(ELEMENTS_NUMBER, pq_size(pq));

  // Intentar insertar dos elementos mas
  TEST_ASSERT_FALSE(pq_insert(pq, &data[ELEMENTS_NUMBER].value, data[ELEMENTS_NUMBER].priority));
  TEST_ASSERT_FALSE(pq_insert(pq, &data[ELEMENTS_NUMBER + 1].value, data[ELEMENTS_NUMBER + 1].priority));

  TEST_ASSERT_EQUAL(ELEMENTS_NUMBER, pq_size(pq));

}


void test_insertar_varios_elementos_con_la_misma_prioridad_y_verificar_que_se_extraen_en_orden_de_insercion (void) {

  data_t data1 = { .value = 1, .priority = 50 };
  data_t data2 = { .value = 2, .priority = 50 };
  data_t data3 = { .value = 3, .priority = 50 };
  data_t data4 = { .value = 4, .priority = 50 };

  _create_queue(PQ_MAX_PRIORITY_QUEUE);
  TEST_ASSERT_TRUE(pq_insert(pq, &data1.value, data1.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data2.value, data2.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data3.value, data3.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data4.value, data4.priority));

  TEST_ASSERT_FALSE(pq_is_empty(pq));
  TEST_ASSERT_EQUAL(4U, pq_size(pq));

  TEST_ASSERT_EQUAL(1, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(3U, pq_size(pq));

  TEST_ASSERT_EQUAL(2, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(2U, pq_size(pq));

  TEST_ASSERT_EQUAL(3, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(1U, pq_size(pq));

  TEST_ASSERT_EQUAL(4, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(0U, pq_size(pq));

}


void test_comprobar_que_peek_devuelve_el_elemento_con_mayor_prioridad_sin_extraerlo_de_la_cola (void) {

  data_t data1 = { .value = 1, .priority = 50 };
  data_t data2 = { .value = 2, .priority = 30 };
  data_t data3 = { .value = 3, .priority = 65 };
  data_t data4 = { .value = 4, .priority = 10 };

  _create_queue(PQ_MAX_PRIORITY_QUEUE);
  TEST_ASSERT_TRUE(pq_insert(pq, &data1.value, data1.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data2.value, data2.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data3.value, data3.priority));
  TEST_ASSERT_TRUE(pq_insert(pq, &data4.value, data4.priority));

  TEST_ASSERT_FALSE(pq_is_empty(pq));
  TEST_ASSERT_EQUAL(4U, pq_size(pq));

  // Peek should return the highest priority element without removing it
  TEST_ASSERT_EQUAL(3, *(uint8_t*)pq_peek(pq));
  TEST_ASSERT_EQUAL(4U, pq_size(pq)); // Size should remain the same

  // Extract to verify it's the same element
  TEST_ASSERT_EQUAL(3, *(uint8_t*)pq_extract(pq));
  TEST_ASSERT_EQUAL(3U, pq_size(pq));

}


void test_validar_comportamiento_ante_nulos (void) {

  // Test pq_create with NULL memory pool
  priority_queue_t* null_pq = pq_create(NULL, ELEMENTS_NUMBER, PQ_MAX_PRIORITY_QUEUE);
  TEST_ASSERT_NULL(null_pq);

  // Test pq_insert with NULL queue
  data_t data = { .value = 1, .priority = 50 };
  TEST_ASSERT_FALSE(pq_insert(NULL, &data.value, data.priority));

  // Test pq_peek with NULL queue
  TEST_ASSERT_NULL(pq_peek(NULL));

  // Test pq_extract with NULL queue
  TEST_ASSERT_NULL(pq_extract(NULL));

  // Test pq_is_empty with NULL queue
  TEST_ASSERT_TRUE(pq_is_empty(NULL));

  // Test pq_size with NULL queue
  TEST_ASSERT_EQUAL(0U, pq_size(NULL));

  // Create a valid queue for further tests
  _create_queue(PQ_MAX_PRIORITY_QUEUE);

  // Test pq_insert with NULL data
  TEST_ASSERT_FALSE(pq_insert(pq, NULL, data.priority));

  // Test pq_peek on empty queue
  TEST_ASSERT_NULL(pq_peek(pq));

  // Test pq_extract on empty queue
  TEST_ASSERT_NULL(pq_extract(pq));

}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
