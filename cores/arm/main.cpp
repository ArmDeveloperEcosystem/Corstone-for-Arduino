/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include <stdarg.h>

#include <FreeRTOS.h>
#include <task.h>

#define ARDUINO_MAIN
#include "Arduino.h"

void arduino_task(void*)
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

extern "C" {
  void error(const char *format, ...) {
    va_list args;
    char buffer[1024];

    va_start(args, format);
    vsnprintf(buffer, 1023, format, args);
    va_end(args);

    Serial.print("*** ERROR: ");
    Serial.print(buffer);
    Serial.println(" ***");

    exit(1);
  }

  int _write(int file, char *data, int len) {
    return Serial.write((uint8_t*)data, len);
  }

  void _exit(int code) {
    Serial.write((uint8_t)0x04);
    Serial.write((uint8_t)code);

    while (1);
  }

  void __wrap_us_ticker_init(void)
  {
    printf("__wrap_us_ticker_init\n");
  }

  void __wrap_us_ticker_util_wait(uint32_t us)
  {
    printf("__wrap_us_ticker_util_wait: %u\n", us);
    vTaskDelay(us / 1000);
  }
}
