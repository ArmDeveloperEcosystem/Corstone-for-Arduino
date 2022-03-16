/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include "Ethernet.h"
#include "EthernetUdp.h"

EthernetUDP::EthernetUDP() :
  _socket(-1),
  _txBufferIndex(0),
  _rxBufferIndex(0),
  _rxBufferLength(0)
{
  memset(&_remoteAddr, 0x00, sizeof(_remoteAddr));
}

EthernetUDP::~EthernetUDP()
{
}

uint8_t EthernetUDP::begin(uint16_t port)
{
  stop();

  _socket = lwip_socket(AF_INET, SOCK_DGRAM, 0);

  if (_socket < 0) {
    stop();

    return 0;
  }

  struct sockaddr_in localAddr;
  int reuseAddr = 1;

  lwip_setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const void*)&reuseAddr, sizeof(reuseAddr));

  memset(&localAddr, 0x00, sizeof(localAddr));
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(port);

  if (lwip_bind(_socket, (struct sockaddr *)&localAddr, sizeof(localAddr)) < 0) {
    stop();

    return 0;
  }

  return 1;
}

void EthernetUDP::stop()
{
  if (_socket > -1) {
    lwip_close(_socket);
  }

  _socket = -1;
  memset(&_remoteAddr, 0x00, sizeof(_remoteAddr));
}

int EthernetUDP::beginPacket(IPAddress ip, uint16_t port)
{
  memset(&_remoteAddr, 0x00, sizeof(_remoteAddr));
  _remoteAddr.sin_len = sizeof(_remoteAddr);
  _remoteAddr.sin_family = AF_INET;
  _remoteAddr.sin_addr.s_addr = ip;
  _remoteAddr.sin_port = htons(port);

  _txBufferIndex = 0;

  return 1;
}

int EthernetUDP::beginPacket(const char *host, uint16_t port)
{
  IPAddress ip;

  if (!Ethernet.hostByName(host, ip)) {
    return 0;
  }

  return beginPacket(ip, port);
}

int EthernetUDP::endPacket()
{
  if (lwip_sendto(_socket, _txBuffer, _txBufferIndex, 0, (struct sockaddr *)&_remoteAddr, sizeof(_remoteAddr)) < 0) {
    return 0;
  }

  return 1;
}

size_t EthernetUDP::write(uint8_t b)
{
  return this->write(&b, sizeof(b));
}

size_t EthernetUDP::write(const uint8_t *buffer, size_t size)
{
  if ((_txBufferIndex + size) > sizeof(_txBuffer)) {
    size = sizeof(_txBuffer) - _txBufferIndex;
  }

  memcpy(_txBuffer + _txBufferIndex, buffer, size);
  _txBufferIndex += size;

  return size;
}

int EthernetUDP::parsePacket()
{
  socklen_t remoteAddrLen = sizeof(_remoteAddr);

  _rxBufferLength = lwip_recvfrom(
    _socket, _rxBuffer, sizeof(_rxBuffer), MSG_DONTWAIT,
    (struct sockaddr *)&_remoteAddr, (socklen_t*)&remoteAddrLen
  );

  _rxBufferIndex = 0;

  if (_rxBufferLength > 0) {
    return _rxBufferLength;
  } else {
    return 0;
  }
}

int EthernetUDP::available()
{
  return (_rxBufferLength - _rxBufferIndex);
}

int EthernetUDP::read()
{
  if (!available()) {
    return -1;
  }

  uint8_t b;

  read(&b, sizeof(b));

  return b;
}

int EthernetUDP::read(unsigned char* buffer, size_t len)
{
  int avail = available();
  if (avail < len) {
    len = avail;
  }

  memcpy(buffer, _rxBuffer + _rxBufferIndex, len);
  _rxBufferIndex += len;

  return avail;
}

int EthernetUDP::read(char* buffer, size_t len)
{
  return read((unsigned char*)buffer, len);
}

int EthernetUDP::peek()
{
  if (available()) {
    return _rxBuffer[_rxBufferIndex];
  }

  return -1;
}

void EthernetUDP::flush()
{
}

IPAddress EthernetUDP::remoteIP()
{
  return _remoteAddr.sin_addr.s_addr;
}

uint16_t EthernetUDP::remotePort()
{
  return ntohs(_remoteAddr.sin_port);
}
