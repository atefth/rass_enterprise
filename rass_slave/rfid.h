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

void wireRfidToMaster(){	
	Wire.write(currentAccess);
	for (int i = 0; i < 7; i++)
	{
		switch(currentUser[i]){
			case '0':
				Wire.write(0);
				break;
			case '1':
				Wire.write(1);
				break;
			case '2':
				Wire.write(2);
				break;
			case '3':
				Wire.write(3);
				break;
			case '4':
				Wire.write(4);
				break;
			case '5':
				Wire.write(5);
				break;
			case '6':
				Wire.write(6);
				break;
			case '7':
				Wire.write(7);
				break;
			case '8':
				Wire.write(8);
				break;
			case '9':
				Wire.write(9);
				break;
		}
	}	
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
	    	Serial.println(digits);
		    if (code == rfid[i])
			{
				openDoor();
				notifyMaster();
				for (int j = 0; j < 7; j++)
	        	{
	        		currentUser[j] = digits[j];
	        	}	        	
	        	currentAccess = 1;
	        	currentIndex = i;
	        }else{
	        	alertMaster();
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