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

/** \brief Fichero de pruebas unitarias del modulo de leds
 **
 ** Pruebas a realizar:
 ** - Iniciar el driver y revisar que todos los leds esten apagados
 ** - Prender un led y verificar que no cambian los otros
 ** - Prender un led cualquiera y apagarlo
 ** - Prender mas de un led, apagar uno y verificar que el resto siguen sin cambios
 ** - Encender un led fuera de rango y comprobar que se genera un error
 ** - Apagar un led fuera de rango y comprobar que se genera un error
 ** - Prender todos los leds
 ** - Apagar todos los leds
 ** - Prender algunos leds mas de una vez y verificar que sigue prendido
 ** - Consultar el estado de un led prendido
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "leds.h"
#include "errores.h"
#include "mock_errores.h"

#include <stdbool.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

static uint16_t port;

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void setUp (void) {

  LedsInitDriver (&port);

}


void tearDown (void) {

}


void test_al_iniciar_todos_los_leds_deben_apagarse (void) {

  uint16_t port = 0xFFFF;
  LedsInitDriver (&port);
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

}


void test_prender_un_led_y_verificar_que_no_cambian_los_otros (void) {

  LedsTurnOn (3);
  TEST_ASSERT_EQUAL_HEX16 (1 << 2, port);

}


void test_prender_un_led_cualquiera_y_apagarlo (void) {

  LedsTurnOn (5);
  LedsTurnOff (5);
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

}


void test_prender_mas_de_un_led_apagar_uno_y_verificar_que_el_resto_siguen_sin_cambios (void) {

  LedsTurnOn (3);
  LedsTurnOn (5);
  LedsTurnOff (3);
  TEST_ASSERT_EQUAL_HEX16 (1 << 4, port);

}


void test_encender_un_led_fuera_de_rango_y_comprobar_que_se_genera_un_error (void) {

  //RegistrarMensaje_Expect (ALERTA, "LedsTurnOn", 0, "El led no es valido");
  //RegistrarMensaje_IgnoreArg_linea ();

  RegistrarMensaje_ExpectAnyArgs ();
  LedsTurnOn (0);
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

  RegistrarMensaje_ExpectAnyArgs ();
  LedsTurnOn (17);
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

}


void test_apagar_un_led_fuera_de_rango_y_comprobar_que_se_genera_un_error (void) {

  RegistrarMensaje_ExpectAnyArgs ();
  LedsTurnOff (0);
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

  RegistrarMensaje_ExpectAnyArgs ();
  LedsTurnOff (17);
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

}


void test_prender_todos_los_leds () {

  LedsTurnOnAll ();
  TEST_ASSERT_EQUAL_HEX16 (0xFFFF, port);

}


void test_apagar_todos_los_leds () {

  LedsTurnOnAll ();
  LedsTurnOffAll ();
  TEST_ASSERT_EQUAL_HEX16 (0x0000, port);

}


void test_prender_algunos_leds_mas_de_una_vez_y_verificar_que_sigue_prendido (void) {

  LedsTurnOn (10);
  LedsTurnOn (7);
  LedsTurnOn (10);
  LedsTurnOn (7);
  TEST_ASSERT_EQUAL_HEX16 ((1 << 9) | (1 << 6), port);

}


void test_consultar_el_estado_de_un_led_prendido (void) {

  LedsTurnOn (8);
  bool state = LedsIsOn (8);
  TEST_ASSERT_EQUAL (true, state);

}


void test_consultar_el_estado_de_un_led_prendido_fuera_de_rango (void) {

  RegistrarMensaje_ExpectAnyArgs ();
  RegistrarMensaje_ExpectAnyArgs ();
  LedsTurnOn (17);
  bool state = LedsIsOn (17);
  TEST_ASSERT_EQUAL (false, state);

}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */