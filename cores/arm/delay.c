/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include <FreeRTOS.h>
#include <task.h>

unsigned long millis(void)
{
  return xTaskGetTickCount() / pdMS_TO_TICKS(1);
}

unsigned long micros(void)
{
  return (xTaskGetTickCount() * 1000) / pdMS_TO_TICKS(1);
}

void delay(unsigned long ms)
{
  if (ms == 0) {
    return;
  }

  vTaskDelay(pdMS_TO_TICKS(ms));
}

void delayMicroseconds(unsigned int usec)
{
  if (usec == 0) {
    return;
  }

  vTaskDelay(pdMS_TO_TICKS(usec * 1000));
}
