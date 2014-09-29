volatile boolean cardSwiped = false;
volatile boolean needWire = false;
volatile boolean doorClosed = true;
volatile long openTime;
volatile long closeTime;
volatile byte interruptCount = 0;

void onDoorStateChange(){
	Serial.println("interrupted!");
	if (!doorClosed && interruptCount != 2)
	{
		cardSwiped = true;
		needWire = true;
		doorClosed = false;
		openTime = millis();
		interruptCount++;
	}else{
		doorClosed = true;
		interruptCount = 0;
		closeTime = millis();
	}
}

long getDuration(){
	return (closeTime - openTime);
}

void initRfid(){
	pinMode(18, INPUT);
	digitalWrite(18, 1);
	attachInterrupt(5, onDoorStateChange, RISING);
}