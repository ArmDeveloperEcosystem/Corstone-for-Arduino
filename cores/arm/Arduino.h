/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2014 Arduino LLC.  All right reserved.
  Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef Arduino_h
#define Arduino_h

#include "api/ArduinoAPI.h"

#ifdef __cplusplus

using namespace arduino;

extern "C"{
#endif // __cplusplus

#ifdef __cplusplus
} // extern "C"
#endif

// Include board variant
#include "variant.h"

#define interrupts()    __enable_irq()
#define noInterrupts()  __disable_irq()

#define digitalPinToInterrupt(P)   ( P )

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#define abs(x) ((x)>0?(x):-(x))

#ifdef __cplusplus
#include "Uart.h"
#endif

// ARM toolchain doesn't provide itoa etc, provide them
#include "api/itoa.h"

#endif // Arduino_h
