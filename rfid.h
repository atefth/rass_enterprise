void onDoorStateChange(){
	Serial.println("interrupted!");
	Serial.println(interruptCount);
	if (interruptCount == 0)
	{
		cardSwiped = true;
		needWire = true;
		doorClosed = false;
		openTime = millis();
		interruptCount++;
	}else if(interruptCount == 1){
		interruptCount++;
		//do nothing
	}else{
		doorClosed = true;
		doorSync = true;
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