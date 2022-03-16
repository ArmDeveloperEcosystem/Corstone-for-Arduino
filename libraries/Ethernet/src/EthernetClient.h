/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#ifndef _ETHERNET_CLIENT_H_
#define _ETHERNET_CLIENT_H_

extern "C" {
  #include <lwip/sockets.h>

  #undef write
  #undef read
  #undef connect
  #undef close
  #undef poll
}

#include <Arduino.h>
#include <Client.h>

class EthernetClient : public Client {
public:
  EthernetClient();
  virtual ~EthernetClient();

  virtual int connect(IPAddress ip, uint16_t port);
  virtual int connect(const char *host, uint16_t port);

  virtual int availableForWrite(void);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);

  virtual int available();
  virtual int read();
  virtual int read(uint8_t *buf, size_t size);
  virtual int peek();

  virtual void flush();
  virtual void stop();

  virtual uint8_t connected();

  virtual operator bool();

  virtual IPAddress remoteIP();
  virtual uint16_t remotePort();

  using Print::write;

private:
  int _socket;

  IPAddress _remoteIp;
  uint16_t _remotePort;
};

#endif
