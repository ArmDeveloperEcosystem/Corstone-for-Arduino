/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Arduino.h"

__attribute__((weak)) void analogReference(uint8_t mode)
{
  (void)mode;
}

__attribute__((weak)) int analogRead(pin_size_t pin)
{
  (void)pin;

  return 0;
}

__attribute__((weak)) void analogWrite(pin_size_t pin, int value)
{
  (void)pin;
  (void)value;
}
