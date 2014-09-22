#define TOTAL_RELAYS 6
#define TOTAL_USERS 10
#define SITE 10
String SITE_URL = "\"softbot-ras.herokuapp.com/";
#define BAUDRATE 19200

#include "relays.h"
#include "users.h"
#include "site.h"
#include <SoftwareSerial.h>
#include "http.h"

void setup()
{
	initRelays();
	initusers();
	initSite();
	initGsm(19200);
}

void loop()
{
	syncServer();
	delay(1000);
}
