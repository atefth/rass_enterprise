void onCardSwipe(){
	Serial.println("interrupted!");
	cardSwiped = true;
	needWire = true;
	doorClosed = false;
}

void onDoorClose(){
	Serial.println("interrupted!");
	doorClosed = true;
	cardSwiped = false;
}

void initRfid(){
	attachInterrupt(5, onCardSwipe, RISING);
	attachInterrupt(4, onDoorClose, RISING);
}