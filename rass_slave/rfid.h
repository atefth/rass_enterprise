void initRfid() {
	wg.begin();
}

void alertMaster(){
	digitalWrite(MASTER, HIGH);
	delay(1000);
	digitalWrite(MASTER, LOW);
	delay(1000);
}

void checkRfid(){
	if(wg.available())
	{		
        code = wg.getCode();
		for(int i=0; i<TOTAL_USERS; i++){
		    if (code == rfid[i])
			{
	        	Serial.println(code);
				Serial.println("Granted");
				alertMaster();
	        }
		}
	}
}





