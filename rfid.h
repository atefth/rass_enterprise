void onCardSwipe(){
	Serial.println("interrupted!");
	cardSwiped = true;
	doorClosed = false;
}

void onDoorClose(){
	Serial.println("interrupted!");
	doorClosed = true;
	cardSwiped = false;
}

void initRfid(){
	attachInterrupt(5, onCardSwipe, CHANGE);
	attachInterrupt(4, onDoorClose, CHANGE);
}