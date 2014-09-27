#define TOTAL_RELAYS 6
#define TOTAL_USERS 10
#define SITE 10
String SITE_URL = "\"softbot-ras.herokuapp.com/";
#define BAUDRATE 19200
static int connection;

#include "relays.h"
#include "users.h"
#include "site.h"
#include <Wire.h>
#include "wireForSlave.h"
#include <SoftwareSerial.h>
#include <LCD5110_Graph.h>
#include "lcd.h"
#include "http.h"
#include <easyscheduler.h>

Schedular showDownTime;
Schedular sync;
Schedular printDownTime;
Schedular printSiteStatus;
Schedular updater;

void setup()
{
	initRelays();
	initusers();
	initSite();
    initLCD();
    Serial.begin(19200);    
	initGsm(19200);    
	initWire();
	//showDownTime.start();
	//printDownTime.start();
	//printSiteStatus.start();
	//updater.start();
    sync.start();
}

void loop()
{
	sync.check(performSync, 8000);
	//performSync();
	//updateConfig();
	//showUserData();
	//showDownTime.check(showSyncDuration, 1000);
	//printDownTime.check(printTimeData, 1000);
	//printSiteStatus.check(printSiteData, 10000);
	delay(1000);
}
