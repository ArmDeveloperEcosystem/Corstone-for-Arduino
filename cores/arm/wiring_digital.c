/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#define PinMode PinModeMdh
#include <hal/gpio_api.h>
#undef PinMode

#include "Arduino.h"

static gpio_t gpio[PINS_NUMBER];

void pinMode(pin_size_t ulPin, PinMode ulMode)
{
  if (ulPin < PINS_NUMBER) {
    gpio_init(&gpio[ulPin], ulPin);

    switch (ulMode) {
      case INPUT:
      case INPUT_PULLUP:
      case INPUT_PULLDOWN:
        gpio_mode(&gpio[ulPin], PIN_INPUT);
        break;

      case OUTPUT:
      case OUTPUT_OPENDRAIN:
        gpio_mode(&gpio[ulPin], PIN_OUTPUT);
        break;

      default:
        break;
    }
  } else if (ulPin >= SW1 && ulPin <= SW8) {
    // nothing to do
  } else if (ulPin >= LED1 && ulPin <= USERLED2) {
    // nothing to do
  } else if (ulPin >= USERPB1 && ulPin <= USERPB2) {
    // nothing to do
  }
}

void digitalWrite(pin_size_t ulPin, PinStatus ulVal)
{
  if (ulPin < PINS_NUMBER) {
    gpio_write(&gpio[ulPin], ulVal);
  } else if (ulPin >= SW1 && ulPin <= SW8) {
    // nothing to do
  } else if (ulPin >= LED1 && ulPin <= USERLED2) {
    arm_mps3_io_write_leds(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PIN, ulPin - LED1, ulVal);
  } else if (ulPin >= USERPB1 && ulPin <= USERPB2) {
    // nothing to do
  }
}

PinStatus digitalRead(pin_size_t ulPin)
{
  if (ulPin < PINS_NUMBER) {
    return (gpio_read(&gpio[ulPin]) ? HIGH : LOW);
  } else if (ulPin >= SW1 && ulPin <= SW8) {
    return arm_mps3_io_read_switches(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PIN, ulPin - SW1);
  } else if (ulPin >= LED1 && ulPin <= USERLED2) {
    return arm_mps3_io_read_leds(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PIN, ulPin - LED1);
  } else if (ulPin >= USERPB1 && ulPin <= USERPB2) {
    return arm_mps3_io_read_buttons(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PORT, ulPin - USERPB1);
  }
  
  return LOW;
}
