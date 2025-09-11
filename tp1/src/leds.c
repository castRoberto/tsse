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

/** \brief Fichero que representa el driver de leds
 **
 ** \addtogroup Leds module
 ** \brief Driver de leds
 ** @{ */

/* === Headers files inclusions =============================================================== */
#include "leds.h"
#include "errores.h"

#include <stdbool.h>
#include <stdio.h>

/* === Macros definitions ====================================================================== */

#define LEDS_ALL_OFF 0x0000
#define FIRST_BIT 1
#define LED_TO_BIT_OFFSET 1

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

static uint16_t* _port; // Direccion del puerto virtual

/* === Private function declarations =========================================================== */

static uint16_t LedsToMask (int led) {
  return FIRST_BIT << (led - LED_TO_BIT_OFFSET);
}


static bool ISLedValid (int led) {
  bool result = led >= 1 && led <= 16;
  if (!result) {
    Alerta ("El led no es valido");
  }
  return result;
}

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void LedsInitDriver (uint16_t* port) {

  _port = port;
  LedsTurnOffAll ();

}


void LedsTurnOn (int led) {

  if (!ISLedValid (led)) return; // Evito que se apague un led invalido

  *_port |= LedsToMask (led);

}


void LedsTurnOff (int led) {

  if (!ISLedValid (led)) return; // Evito que se apague un led invalido

  *_port &= ~LedsToMask (led);

}


void LedsTurnOnAll (void) {

  *_port = ~LEDS_ALL_OFF;

}


void LedsTurnOffAll (void) {

  *_port = LEDS_ALL_OFF;

}


bool LedsIsOn (int led) {

  if (!ISLedValid (led)) return false; // Evito que se consulte un led invalido

  return (*_port & LedsToMask (led)) != 0;

}


bool LedsIsOff (int led) {

  if (!ISLedValid (led)) return false; // Evito que se consulte un led invalido

  return (*_port & LedsToMask (led)) == 0;

}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */