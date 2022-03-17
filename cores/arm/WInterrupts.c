/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Arduino.h"

__attribute__((weak)) void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode)
{
  (void)interruptNumber;
  (void)callback;
  (void)mode;
}

__attribute__((weak)) void attachInterruptParam(pin_size_t interruptNumber, voidFuncPtrParam callback, PinStatus mode, void* param)
{
  (void)interruptNumber;
  (void)callback;
  (void)mode;
  (void)param;
}

__attribute__((weak)) void detachInterrupt(pin_size_t interruptNumber)
{
  (void)interruptNumber;
}
