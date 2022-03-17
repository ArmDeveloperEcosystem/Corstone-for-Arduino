/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

extern "C" {
  #include <hal/serial_api.h>
}

#include "Uart.h"

Uart::Uart(void* serial, int tx, int rx) :
  _serial(serial),
  _txPin(tx),
  _rxPin(rx)
{
}

void Uart::begin(unsigned long baudRate)
{
  begin(baudRate, SERIAL_8N1);
}

void Uart::begin(unsigned long baudrate, uint16_t config)
{
  // TODO: use config
  serial_init((serial_t*)_serial, (PinName)_txPin, (PinName)_rxPin);
  serial_baud((serial_t*)_serial, baudrate);
}

void Uart::end()
{
}

int Uart::available()
{
  return 0;
}

int Uart::availableForWrite()
{
  return 1;
}

int Uart::peek()
{
  return -1;
}

int Uart::read()
{
  return -1;
}

void Uart::flush()
{
}

size_t Uart::write(const uint8_t data)
{
  serial_putc((serial_t*)_serial, (int)data);

  return 1;
}

static serial_t serial;
Uart Serial(&serial, CONSOLE_TX, CONSOLE_RX);

static serial_t serial1;
Uart Serial1(&serial1, U1_TX, U1_RX);
