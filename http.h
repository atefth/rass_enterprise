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
    Serial.begin(rate);
    gsm.begin(rate);
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

    String requestURL = "AT+HTTPPARA=\"URL\",";
    requestURL += SITE_URL + url;

    initRequest();

    gsm.println("AT+HTTPPARA=\"CID\",1");  
    delay(1000); 
    showSerialData();
    
    // setting the httppara, the second parameter is the website you want to access
    Serial.println(requestURL);
    gsm.println(requestURL);
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

void attemptSyncRequest(){
    String url = "syncServer/";
    url =  url + SITE + "\"";
    makeRequest(url);
}

void attemptDoorCloseRequest(){
    String url = "closeDoor/";
    url = url + SITE +"\"";
    makeRequest(url);
}

void attemptRfidRequest(){
    String url = "remoteToOrigin/";
    url = url + SITE + "/0/1/1234567/1/10/10/2014/12/34/14" + "\"";
    makeRequest(url);
}

boolean readUserAccessRight(){
    boolean isLoss = true;
	int count = 0;
    char tempUsers[TOTAL_USERS][RFID_NUM];
    int tempAccess[TOTAL_USERS];

    char justRead = ' ';
    char totalRead[RFID_NUM];

    while(gsm.available()!=0 && justRead != '>'){
      justRead = gsm.read();
    }
    int index = 0;
    while(gsm.available()!=0){
        justRead = gsm.read();
        if (count == RFID_NUM)
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
	attemptSyncRequest();
    boolean isLoss = true;
    boolean relayLoss = readRelay();
    if (!relayLoss){
        updateRelayStatus();
        boolean userLoss = readUserAccessRight();
        if (!userLoss)
        {
            isLoss = false;
        }        
    }
    terminateRequest();
    clearSerialData();
    if (!isLoss)
    {
        setLastSyncTime(millis());
        incrementSuccessfulRequests();
        printConfigData();
        updateConfig();
    }else{
        incrementFailedRequests();
               
    }
    updateFailRate();
    return isLoss;
}

void performSync(){
    printProcessing();
    syncServer();
}

boolean verifyPacket(){
    boolean isLoss = true;
    char justRead = ' ';
    while(gsm.available()!=0){
        justRead = gsm.read();
        if (justRead == '#')
        {
            isLoss = false;
        }
    }
    return isLoss;
}

boolean syncDoorClose(){
    terminateRequest();
    clearSerialData();
    attemptDoorCloseRequest();
    boolean isLoss = verifyPacket();
    terminateRequest();
    clearSerialData();
    return isLoss;
}

void performDoorSync(){
    boolean isLoss = syncDoorClose();
    if (!isLoss)
    {
        doorClosed = true;
    }
}

boolean syncRfid(){
    terminateRequest();
    clearSerialData();
    long rfid = readRfidFromSlave();
    Serial.println(rfid);
    attemptRfidRequest();
    boolean isLoss = verifyPacket();
    terminateRequest();
    clearSerialData();
    return isLoss;
}

void performRfidSync(){
    boolean isLoss = syncRfid();
    if (!isLoss)
    {
        cardSwiped = false;
    }
}