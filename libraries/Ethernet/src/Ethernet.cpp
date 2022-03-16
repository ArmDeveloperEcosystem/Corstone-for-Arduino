/*
 * Copyright (c) 2022 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1
 * 
 */

#include <stdarg.h>

extern "C" {
  #include <FreeRTOS.h>
  #include <task.h>
  #include "lwip/netif.h"
  #include "lwip/dns.h"

  void net_task(void *pvParameters);
}

#include "Ethernet.h"

EthernetClass::EthernetClass()
{
}

EthernetClass::~EthernetClass()
{
}

int EthernetClass::begin(uint8_t *mac, unsigned long timeout, unsigned long responseTimeout)
{
  xTaskCreate(net_task, "net task", configMINIMAL_STACK_SIZE*2, NULL, ( configMAX_PRIORITIES - 3 ), NULL);

  while (1) {
    struct netif* en1 = netif_find("en1");

    if (en1 != NULL) {
      const ip_addr_t* ip = netif_ip_addr4(en1);

      if (ip->addr) {
          break;
      }
    }

    delay(100);
  }

  return linkStatus();
}

int EthernetClass::maintain()
{
    delay(0);

    return 0;
}

EthernetLinkStatus EthernetClass::linkStatus()
{
  struct netif* en1 = netif_find("en1");

  if (en1 && netif_is_up(en1)) {
    return LinkON;
  }

  return LinkOFF;
}

EthernetHardwareStatus EthernetClass::hardwareStatus()
{
  return EthernetCorstone300;
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip)
{
  begin(
    mac,
    ip,
    IPAddress(ip[0], ip[1], ip[2], ip[3])
  );
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns)
{
  begin(
    mac,
    ip,
    dns,
    IPAddress(ip[0], ip[1], ip[2], ip[3])
  );
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway)
{
  begin(
    mac,
    ip,
    dns,
    gateway,
    IPAddress(255, 255, 255, 0)
  );
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet)
{
  _ipAddress = ip;
  _subnetMask = subnet;
  _gatewayIp = gateway;
  _dnsServerIp = dns;
}

void EthernetClass::init(uint8_t sspin)
{
  _ipAddress = (uint32_t)0;
  _subnetMask = (uint32_t)0;
  _gatewayIp = (uint32_t)0;
  _dnsServerIp = (uint32_t)0;
}

void EthernetClass::MACAddress(uint8_t *mac_address)
{
  struct netif* en1 = netif_find("en1");

  memcpy(mac_address, en1->hwaddr, 6);
}

IPAddress EthernetClass::localIP()
{
  struct netif* en1 = netif_find("en1");

  const ip_addr_t* ip = netif_ip_addr4(en1);

  return ip->addr;
}

IPAddress EthernetClass::subnetMask()
{
  struct netif* en1 = netif_find("en1");

  const ip_addr_t* ip = netif_ip_netmask4(en1);

  return ip->addr;
}

IPAddress EthernetClass::gatewayIP()
{
  struct netif* en1 = netif_find("en1");

  const ip_addr_t* ip = netif_ip_gw4(en1);

  return ip->addr;
}

IPAddress EthernetClass::dnsServerIP()
{
  const ip_addr_t* ip = dns_getserver(0);

  return ip->addr;
}

int EthernetClass::hostByName(const char* aHostname, IPAddress& aResult)
{
  ip_addr_t ip;
  err_t result;

  while (1) {
    result = dns_gethostbyname(aHostname, &ip, NULL, NULL);
    if (result == ERR_INPROGRESS) {
      delay(100);
    } else {
      break;
    }
  }
  
  if (result == ERR_OK) {
    aResult = ip.addr;
    return 1;
  }

  aResult = (uint32_t)0;
  return 0;
}

EthernetClass Ethernet;
