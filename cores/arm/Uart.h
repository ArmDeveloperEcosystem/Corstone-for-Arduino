/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#pragma once

#include "api/HardwareSerial.h"

class Uart : public arduino::HardwareSerial
{
public:
  Uart(void*, int tx, int rx);
  void begin(unsigned long baudRate);
  void begin(unsigned long baudrate, uint16_t config);
  void end();
  int available();
  int availableForWrite();
  int peek();
  int read();
  void flush();
  size_t write(const uint8_t data);

  using Print::write;

  operator bool() { return true; }

private:
  int _txPin;
  int _rxPin;
  void* _serial;
};

extern Uart Serial;
extern Uart Serial1;
