/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Arduino.h"

__attribute__((weak)) void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t val)
{
  (void)dataPin;
  (void)clockPin;
  (void)bitOrder;
  (void)val;
}

__attribute__((weak)) uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder)
{
  (void)dataPin;
  (void)clockPin;
  (void)bitOrder;

  return 0;
}
