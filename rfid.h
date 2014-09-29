volatile boolean cardSwiped = false;
volatile boolean needWire = false;
volatile boolean doorClosed = true;
volatile long openTime;
volatile long closeTime;

void onDoorStateChange(){
	Serial.println("interrupted!");
	if (doorClosed)
	{
		cardSwiped = true;
		needWire = true;
		doorClosed = false;
		openTime = millis();
	}else{
		doorClosed = true;
		closeTime = millis();
	}
}

long getDuration(){
	return (closeTime - openTime);
}

void initRfid(){
	attachInterrupt(5, onDoorStateChange, RISING);
}