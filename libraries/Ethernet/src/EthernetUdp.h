/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#ifndef _ETHERNET_UDP_H_
#define _ETHERNET_UDP_H_

extern "C" {
  #include <lwip/sockets.h>

  #undef read
  #undef write
  #undef close
  #undef poll
}

#include <Arduino.h>
#include <Udp.h>

class EthernetUDP : public UDP {
public:
  EthernetUDP();
    virtual ~EthernetUDP();

  virtual uint8_t begin(uint16_t);
  virtual void stop();

  virtual int beginPacket(IPAddress ip, uint16_t port);
  virtual int beginPacket(const char *host, uint16_t port);
  virtual int endPacket();
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buffer, size_t size);

  using Print::write;

  virtual int parsePacket();
  virtual int available();
  virtual int read();
  virtual int read(unsigned char* buffer, size_t len);
  virtual int read(char* buffer, size_t len);
  virtual int peek();
  virtual void flush();

  virtual IPAddress remoteIP();
  virtual uint16_t remotePort();

private:
  int _socket;
  struct sockaddr_in _remoteAddr;

  uint8_t _txBuffer[1500];
  size_t _txBufferIndex;

  uint8_t _rxBuffer[1500];
  ssize_t _rxBufferIndex;
  ssize_t _rxBufferLength;
};

#endif
