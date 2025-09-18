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

#ifndef ERRORES_H
#define ERRORES_H

/** \brief Brief description of the file
 **
 ** Full file description
 **
 ** \addtogroup Errores module Management of errors
 ** \brief Header file for errores module
 ** @{ */

/* === Headers files inclusions ================================================================ */

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#define Alerta(mensaje)      RegistrarMensaje(ALERTA, __func__, __LINE__, mensaje)
#define Error(mensaje)       RegistrarMensaje(ERROR, __func__, __LINE__, mensaje)
#define Informacion(mensaje) RegistrarMensaje(INFORMACION, __func__, __LINE__, mensaje)
#define Depuracion(mensaje)  RegistrarMensaje(DEPURACION, __func__, __LINE__, mensaje)

/* === Public data type declarations =========================================================== */

typedef enum gravedad_e { ERROR, ALERTA, INFORMACION, DEPURACION } gravedad_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * \brief Funcion para registrar un mensaje en la biblioteca de errores del sistema
 *
 * \param gravedad Nivel de gravedad del mensaje
 * \param funcion Nombre de la funcion desde donde se registra el mensaje
 * \param linea Linea de codigo desde donde se registra el mensaje
 * \param mensaje Mensaje a registrar
 */
void RegistrarMensaje(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* ERRORES_H */
