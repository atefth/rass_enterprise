void initWire(){    
	Wire.begin();
}

void wireDataToSlave(){
	char temp;	
	for (int i = 0; i < 10; i++){		
		Wire.beginTransmission(4);
		Wire.write(i);
		if (userRfid[i] == "000000000"){			
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
			Wire.write(0);
		}else{
			for (int j = 0; j < 9; j++)
			{
				temp = userRfid[i][j];				
				switch(temp){
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
		Wire.endTransmission();
		delay(100);		
	}	
}

void updateConfig(){
	wireDataToSlave();
}
