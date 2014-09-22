long userRfid[TOTAL_USERS];
int userAccess[TOTAL_USERS];

void initusers(){
	for(int i=0; i<TOTAL_USERS; i++){
	    userRfid[i] = 0;
	    userAccess[i] = 0;
	}
}

void setRfid(int id, long rfid){
	userRfid[id] = rfid;
}

long getRfid(int id, long rfid){
	return userRfid[id];
}

void setAccessRight(int id, int access){
	userAccess[id] = access;
}

long getAccessRight(long rfid){
	return userAccess[rfid];
}

void showUserData(){
	for(int i=0; i<TOTAL_USERS; i++){
	    Serial.print("User with rfid ");
	    Serial.print(userRfid[i]);
	    Serial.print(" has access ");
	    Serial.print(userAccess[i]);
	    Serial.println();
	}
}
