static char userRfid[TOTAL_USERS][9];

void initusers(){
	Serial.println("Initializing Users");
	for(int i=0; i<TOTAL_USERS; i++){
	    for (int j = 0; j < 9; j++)
	    {
	    	userRfid[i][j] = '0';
	    }
	}
}

void updateRfid(char rfid[TOTAL_USERS][9]){
	for (int i = 0; i < TOTAL_USERS; i++)
	{
		for (int j = 0; j < 9; ++j)
		{
			userRfid[i][j] = rfid[i][j];
		}
	}
}

void showUserData(){
	for(int i=0; i<TOTAL_USERS; i++){
	    Serial.print("User with rfid ");
	    for (int j = 0; j < 9; j++)
	    {
	    	Serial.print(userRfid[i][j]);
	    }
	    Serial.println();
	}
}
