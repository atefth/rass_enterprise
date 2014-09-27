static char userRfid[TOTAL_USERS][9];
static int userAccess[TOTAL_USERS];

void initusers(){
	Serial.println("Initializing Users");
	for(int i=0; i<TOTAL_USERS; i++){
	    for (int j = 0; j < 9; j++)
	    {
	    	userRfid[i][j] = '0';
	    }
	    userAccess[i] = 0;
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

void updateAccessRight(int access[]){
	for (int i = 0; i < TOTAL_USERS; i++)
	{
		userAccess[i] = access[i];
	}
}

long getAccessRight(long rfid){
	return userAccess[rfid];
}

void showUserData(){
	for(int i=0; i<TOTAL_USERS; i++){
	    Serial.print("User with rfid ");
	    for (int j = 0; j < 9; j++)
	    {
	    	Serial.print(userRfid[i][j]);
	    }
	    Serial.print(" has access ");
	    Serial.print(userAccess[i]);
	    Serial.println();
	}
}
