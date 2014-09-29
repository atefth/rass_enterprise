#define TOTAL_RELAYS 6
#define TOTAL_USERS 10
#define RFID_NUM 7
#define SITE 10
String SITE_URL = "\"softbot-ras.herokuapp.com/";
#define BAUDRATE 19200
static int connection;

#include "rfid.h"
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
	Serial.begin(19200);
	initRfid();
	initRelays();
	initusers();
	initSite();
    initLCD();    
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
	sync.check(performSync, 10000);
	if(cardSwiped){
		do{
		    performRfidSync();
		    delay(500);
		} while (cardSwiped == true);
	}
	if(!doorClosed){
		do{
		    performDoorSync();
		    delay(500);
		} while (doorClosed == false);
	}
	// performSync();
	//updateConfig();
	//showUserData();
	//showDownTime.check(showSyncDuration, 1000);
	//printDownTime.check(printTimeData, 1000);
	//printSiteStatus.check(printSiteData, 10000);
	delay(2000);
}
