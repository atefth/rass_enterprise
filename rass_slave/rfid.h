void initRfid() {
	wg.begin();
}

void notifyMaster(){
	digitalWrite(GRANTED, HIGH);
	delay(10);
	digitalWrite(GRANTED, LOW);
	// delay(10);
}

void alertMaster(){
	digitalWrite(DENIED, HIGH);
	delay(10);
	digitalWrite(DENIED, LOW);
	// delay(10);
}

void wireRfidToMaster(){
	String digits = "00000000";
	for (int i = 1; i < 8; i++)
	{
		digits[i] = currentUser[i];
	}
	Wire.write(digits);
}

void wireIndexToMaster(){
	Wire.write(currentIndex);
}

void openDoor(){
	digitalWrite(DOOR, HIGH);
	delay(2000);
	digitalWrite(DOOR, LOW);
	delay(100);
}

void checkRfid(){
	if(wg.available())
	{		
        code = wg.getCode();
        String digits;
		for(int i=0; i<TOTAL_USERS; i++){			
	    	digits = String(code, DEC);
	    	// Serial.println(code);
		    if (code == rfid[i])
			{
				openDoor();				
				for (int j = 0; j < 7; j++)
	        	{
	        		currentUser[j] = digits[j];
	        	}
	        	currentAccess = 1;
	        	currentIndex = i;
	        	notifyMaster();
	        }else{	        	
	        	for (int j = 0; j < 7; j++)
	        	{
	        		currentUser[j] = digits[j];
	        	}
	        	currentAccess = 0;
	        	currentIndex = i;
	        	alertMaster();
	        }
		}
	}
}