static char userRfid[TOTAL_USERS][RFID_NUM];

void initusers(){
	Serial.println("Initializing Users");
	for(int i=0; i<TOTAL_USERS; i++){
	    for (int j = 0; j < RFID_NUM; j++)
	    {
	    	userRfid[i][j] = '0';
	    }
	}
}

void updateRfid(char rfid[TOTAL_USERS][RFID_NUM]){
	for (int i = 0; i < TOTAL_USERS; i++)
	{
		for (int j = 0; j < RFID_NUM; ++j)
		{
			userRfid[i][j] = rfid[i][j];
		}
	}
}

void showUserData(){
	for(int i=0; i<TOTAL_USERS; i++){
	    Serial.print("User with rfid ");
	    for (int j = 0; j < RFID_NUM; j++)
	    {
	    	Serial.print(userRfid[i][j]);
	    }
	    Serial.println();
	}
}
