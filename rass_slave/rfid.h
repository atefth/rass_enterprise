void initRfid() {
	wg.begin();
}

void notifyMaster(){
	digitalWrite(GRANTED, HIGH);
	delay(10);
	digitalWrite(GRANTED, LOW);
	delay(10);
}

void alertMaster(){
	digitalWrite(DENIED, HIGH);
	delay(10);
	digitalWrite(DENIED, LOW);
	delay(10);
}

void wireToMaster(){	
	Wire.write(currentAccess);
	for (int i = 0; i < 7; i++)
	{
		Wire.write(currentUser[i]);
	}	
}

void openDoor(){
	digitalWrite(DOOR, LOW);
	delay(2000);
	digitalWrite(DOOR, HIGH);
	delay(100);
}

void checkRfid(){
	if(wg.available())
	{		
        code = wg.getCode();
        String digits;
		for(int i=0; i<TOTAL_USERS; i++){			
	    	digits = "0" + rfid[i];
		    if (code == rfid[i])
			{
				openDoor();
				notifyMaster();
				for (int j = 1; j < 8; j++)
	        	{
	        		currentUser[i-1] = digits[i];
	        	}	        	
	        	currentAccess = 1;
	        }else{
	        	alertMaster();
	        	for (int j = 1; j < 8; j++)
	        	{
	        		currentUser[i-1] = digits[i];
	        	}
	        	currentUser = rfid[i];
	        	currentAccess = 0;
	        }
		}
	}
}