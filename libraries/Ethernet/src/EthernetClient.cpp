/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Ethernet.h"
#include "EthernetClient.h"

EthernetClient::EthernetClient() :
  _socket(-1),
  _remoteIp((uint32_t)0),
  _remotePort(0)
{
}

EthernetClient::~EthernetClient()
{
}

int EthernetClient::connect(IPAddress ip, uint16_t port)
{
  stop();

  _socket = lwip_socket(PF_INET, SOCK_STREAM, 0);
  if (_socket < 0) {
    stop();

    return 0;
  }

  struct sockaddr_in remoteAddr;

  memset(&remoteAddr, 0x00, sizeof(remoteAddr));
  remoteAddr.sin_family = AF_INET;
  remoteAddr.sin_addr.s_addr = ip;
  remoteAddr.sin_port = htons(port);

  if (lwip_connect(_socket, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) < 0) {
    stop();
    return 0;
  }

  _remoteIp = ip;
  _remotePort = port;

  return 1;
}

int EthernetClient::connect(const char *host, uint16_t port)
{
  IPAddress ip;

  if (!Ethernet.hostByName(host, ip)) {
    return 0;
  }

  return connect(ip, port);
}

int EthernetClient::availableForWrite(void)
{
  return 1;
}

size_t EthernetClient::write(uint8_t b)
{
  return write(&b, sizeof(b));
}

size_t EthernetClient::write(const uint8_t *buf, size_t size)
{
  int result = lwip_write(_socket, buf, size);

  if (result < 0) {
    setWriteError();

    stop();

    return 0;
  }

  return result;
}

int EthernetClient::available()
{
  int result = 0;

  peek();

  int r = lwip_ioctl(_socket, FIONREAD, &result);

  if (lwip_ioctl(_socket, FIONREAD, &result) < 0) {

    stop();

    return 0;
  }

  return result;
}

int EthernetClient::read()
{
  if (available() < 1) {
    return -1;
  }

  uint8_t b;

  read(&b, sizeof(b));

  return b;
}

int EthernetClient::read(uint8_t *buf, size_t size)
{
  int result = lwip_recv(_socket, buf, size, MSG_DONTWAIT);

  if (result < 0 && errno != EWOULDBLOCK) {
    stop();

    return 0;
  }

  if (result == -1) {
    result = 0;
  }

  return result;
}

int EthernetClient::peek()
{
  uint8_t b;

  if (lwip_recv(_socket, &b, sizeof(b), MSG_PEEK | MSG_DONTWAIT) <= 0) {
    if (errno != EWOULDBLOCK) {
      stop();
    }

    return -1;
  }

  return b;
}

void EthernetClient::flush()
{
}

void EthernetClient::stop()
{
  if (_socket > -1) {
    lwip_close(_socket);
  }

  _socket = -1;
  _remoteIp = (uint32_t)0;
  _remotePort = 0;
}

uint8_t EthernetClient::connected()
{
  peek();

  return (_socket > -1);
}

EthernetClient::operator bool()
{
  return (_socket > -1);
}

IPAddress EthernetClient::remoteIP()
{
  return _remoteIp;
}

uint16_t EthernetClient::remotePort()
{
  return _remotePort;
}
