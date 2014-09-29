void initRfid() {
	wg.begin();
}

void wireRfidToMaster(){
	for (int i = 0; i < 7; i++)
	{
		Serial.println(currentUser[i]);
	}
	Wire.write(currentUser);
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
	        }else{	        	
	        	for (int j = 0; j < 7; j++)
	        	{
	        		currentUser[j] = digits[j];
	        	}
	        	currentAccess = 0;
	        	currentIndex = i;
	        }
		}
	}
}