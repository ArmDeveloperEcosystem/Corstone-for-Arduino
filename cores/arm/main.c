/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include <FreeRTOS.h>
#include <task.h>

#define ARDUINO_MAIN
#include "Arduino.h"

void arduino_task()
{
  setup();

  while (1) {
    loop();
  }
}

int main()
{
  xTaskCreate(arduino_task, "Arduino task", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();

  while (1);

  return 0;
}
