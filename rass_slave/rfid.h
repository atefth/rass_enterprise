void initRfid() {
	wg.begin();
}

void notifyMaster(){
	digitalWrite(GRANTED, HIGH);
	delay(1000);
	digitalWrite(GRANTED, LOW);
	delay(1000);
}

void alertMaster(){
	digitalWrite(DENIED, HIGH);
	delay(1000);
	digitalWrite(DENIED, LOW);
	delay(1000);
}

void wireToMaster(){	
	Wire.write(currentAccess);
	Wire.write(currentUser);
}

void openDoor(){
	digitalWrite(DENIED, HIGH);
	delay(2000);
	digitalWrite(DENIED, LOW);
	delay(100);
}

void checkRfid(){
	if(wg.available())
	{		
        code = wg.getCode();
		for(int i=0; i<TOTAL_USERS; i++){
		    if (code == rfid[i])
			{
				openDoor();
				notifyMaster();
	        	currentUser = rfid[i];
	        	currentAccess = 1;
	        }else{
	        	alertMaster();
	        	currentUser = rfid[i];
	        	currentAccess = 0;
	        }
		}
	}
}