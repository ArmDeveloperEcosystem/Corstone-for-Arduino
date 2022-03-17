/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Arduino.h"

__attribute__((weak)) unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout)
{
  (void)pin;
  (void)state;
  (void)timeout;

  return 0;
}

__attribute__((weak)) unsigned long pulseInLong(pin_size_t pin, uint8_t state, unsigned long timeout)
{
  (void)pin;
  (void)state;
  (void)timeout;

  return 0;
}
