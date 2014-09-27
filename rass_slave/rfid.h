void initRfid() {
	wg.begin();
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
			}else{
	            Serial.println(code);
	            Serial.println("Denied");
	        }
		}
	}
}





