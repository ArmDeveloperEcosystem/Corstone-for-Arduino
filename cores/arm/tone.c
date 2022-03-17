/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Arduino.h"

__attribute__((weak)) void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  (void)_pin;
  (void)frequency;
  (void)duration;
}

__attribute__((weak)) void noTone(uint8_t _pin)
{
  (void)_pin;
}
