#ifndef MYWIFI
#define MYWIFI

#include <Wifi.h>
#include <deque>

#include "WifiCredentials.h"

void wifiSetup();

 extern std::deque<IPAddress> ipAddressesInQueue;

#endif