#define GSM_POWER 6
SoftwareSerial gsm(50, 51);

void clearSerialData(){
	while(gsm.available()!=0)
	gsm.read();
}

void showSerialData(){
	while(gsm.available()!=0)
	Serial.write(gsm.read());
}

void showRequestData(){
    Serial.print("Successful : ");
    Serial.print(getSuccessfulRequests());
    Serial.print(" Failed : ");
    Serial.print(getFailedRequests());
    Serial.print(" Total : ");
    Serial.print(getTotalRequests());
    Serial.print(" Fail Rate : ");
    Serial.print(getFailRate());
    Serial.println(" %");
}

void checkConnection(){
    char current;
    while(gsm.available() != 0){
    	current = gsm.read();
		if ( current == '1')
		{
	    	connection = true;
            Serial.println("Connected!");
		}else if( current == '0'){
            Serial.println("Not Connected... Retrying!");
        }
    }
    printConnectionData();
    delay(100);
}

void powerOn(){
  pinMode(GSM_POWER, OUTPUT);
  digitalWrite(GSM_POWER, HIGH);
  delay(2000);
  digitalWrite(GSM_POWER, LOW);
  delay(2000);
}

void initGsm(int rate){
    gsm.begin(rate);
    Serial.begin(rate);
    Serial.println("Initializing GSM");
    powerOn();
    connection = false;
    while(!connection){
      gsm.println("AT+CSQ");
      delay(1000);
      showSerialData();
      gsm.println("AT+CGATT?");
      showSerialData();
      delay(1000);
      checkConnection();
    }
    gsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
    showSerialData();
    delay(1500);
   
    gsm.println("AT+SAPBR=3,1,\"APN\",\"internet\"");//setting the APN, the second need you fill in your local apn server
    showSerialData();
    delay(1500);
    
    gsm.println("AT+SAPBR=1,1");//setting the APN, the second need you fill in your local apn server
    showSerialData();
    delay(1400);
    
    gsm.println("AT+SAPBR=2,1");//setting the APN, the second need you fill in your local apn server
    showSerialData();  
    delay(1400);
}

void initRequest(){
	gsm.println("AT+HTTPINIT"); //init the HTTP request
    delay(500);
    clearSerialData();
}

void terminateRequest(){
	gsm.println("AT+HTTPTERM");
    delay(500);
    clearSerialData();
}

void makeRequest(String url){
    initRequest();

    gsm.println("AT+HTTPPARA=\"CID\",1");  
    delay(1000); 
    showSerialData();
    
    // setting the httppara, the second parameter is the website you want to access
    gsm.println(url);
    delay(500);
    showSerialData();
   
    //submit the request 
    gsm.println("AT+HTTPACTION=0");
    delay(4000);
    showSerialData();

    // read the data from the website you access
    gsm.println("AT+HTTPREAD");  
    delay(1000);
    incrementTotalRequests();
}

void attemptRequest(){
String url = "AT+HTTPPARA=\"URL\",";
    url += SITE_URL + "syncServer/" + SITE + "\"";
    Serial.println(url);
    makeRequest(url);
}

boolean readUserAccessRight(){
    boolean isLoss = true;
	int count = 0;
    char tempUsers[TOTAL_USERS][9];
    int tempAccess[TOTAL_USERS];

    char justRead = ' ';
    char totalRead[9];

    while(gsm.available()!=0 && justRead != '>'){
      justRead = gsm.read();
    }
    int index = 0;
    while(gsm.available()!=0){
        justRead = gsm.read();
        if (count == 9)
        {
            count = 0;          
            index++;
        }
        if(justRead == '>' || justRead == '!'){
            isLoss = false;        
        }
        if(justRead == '0' || justRead == '1'|| justRead == '2'|| justRead == '3'|| justRead == '4'|| justRead == '5'|| justRead == '6'|| justRead == '7'|| justRead == '8'|| justRead == '9'){            
            tempUsers[index][count] = justRead;
            count++;
        }
        if(index == TOTAL_USERS) break;
    }
    if (!isLoss)
    {
        for(int i=0; i<TOTAL_USERS; i++){
            Serial.print("Temp array ");
            Serial.print(i);
            Serial.print(" has rfid ");
            for(int j=0; j<9; j++){
                Serial.print(tempUsers[i][j]);
            }
            Serial.println();
        }
        updateRfid(tempUsers);
    }
}

boolean readRelay(){
    boolean isLoss = true;
    int temp[TOTAL_RELAYS];
    char justRead = ' ';

    int count = 0;
    while(gsm.available()!=0 && justRead != '>'){
      justRead = gsm.read();
    }
    while(gsm.available()!=0){      
        justRead = gsm.read();
        if(justRead == '>'){
            isLoss = false;        
        }
        if(justRead == '0' || justRead == '1'){
            if (justRead == '0')
            {
                temp[count] = 0;
            }else{
                temp[count] = 1;
            }
            count++;
        }
        if(count == TOTAL_RELAYS) break;
    }
    if (!isLoss)
    {
        for (int i = 0; i < TOTAL_RELAYS; i++)
        {
            statuses[i] = temp[i];
        }
    }
    return isLoss;
}

boolean syncServer(){
	attemptRequest();
    boolean isLoss = true;
    boolean relayLoss = readRelay();        
    if (!relayLoss){
        boolean userLoss = readUserAccessRight();
        isLoss = false;
    }
    terminateRequest();
    clearSerialData();
    if (!isLoss)
    {
        setLastSyncTime(millis());
        incrementSuccessfulRequests();
        printConfigData();
    }else{
        incrementFailedRequests();
               
    }
    updateFailRate();
    return isLoss;
}

void performSync(){
    printProcessing();
    if(syncServer()){
        //updateConfig();
    }
}
