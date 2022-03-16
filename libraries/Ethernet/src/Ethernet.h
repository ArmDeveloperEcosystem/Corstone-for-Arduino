/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#include <Arduino.h>

#include "EthernetClient.h"

enum EthernetLinkStatus {
  Unknown,
  LinkON,
  LinkOFF
};

enum EthernetHardwareStatus {
	EthernetNoHardware,
	EthernetCorstone300
};

class EthernetClass {

public:
  EthernetClass();
  virtual ~EthernetClass();

  int begin(uint8_t *mac, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
  int maintain();
  EthernetLinkStatus linkStatus();
  EthernetHardwareStatus hardwareStatus();

  void begin(uint8_t *mac, IPAddress ip);
  void begin(uint8_t *mac, IPAddress ip, IPAddress dns);
  void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway);
  void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet);
  void init(uint8_t sspin = 10);

  void MACAddress(uint8_t *mac_address);
  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();

  int hostByName(const char* aHostname, IPAddress& aResult);

private:
  IPAddress _ipAddress;
  IPAddress _subnetMask;
  IPAddress _gatewayIp;
  IPAddress _dnsServerIp;
};

extern EthernetClass Ethernet;

#endif
