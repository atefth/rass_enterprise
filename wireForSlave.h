void initWire(){
	Wire.begin();
}

void wireDataToSlave(){
	for (int i = 0; i < TOTAL_USERS; i++){
		Wire.beginTransmission(4);
		Wire.write(i);
		char digits[9];
		sprintf(digits, "%ld", userRfid[i]);
		Wire.write(userAccess[i]);
		if (userRfid[i] == "000000000"){
			// Wire.write(userRfid[i]);
			Wire.write(0);
			Wire.write(6);
			Wire.write(7);
			Wire.write(0);
			Wire.write(9);
			Wire.write(8);
			Wire.write(1);
			Wire.write(0);
			Wire.write(9);
		}else{
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
		}
		Wire.endTransmission();
		delay(500);
	}
}

void updateConfig(){
	wireDataToSlave();
}
