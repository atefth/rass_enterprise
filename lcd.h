LCD5110 myGLCD(9,10,11,12,13);
extern uint8_t SmallFont[];
int duration;

void initLCD(){
	myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
  
  myGLCD.print("SoftBot Systems", CENTER, 0);
  myGLCD.print("RASS 1.1", LEFT, 12);
  myGLCD.print("PROTOTYPE", LEFT, 30);
  myGLCD.update();

  delay(3000);
  myGLCD.clrScr();
}

void printTimeData(){	
	duration = int(getSyncDuration() / 1000.0);
  myGLCD.clrScr();
  myGLCD.print("DURATION : ", LEFT, 0);
  myGLCD.printNumI((int)duration, 65, 0);
  myGLCD.update();
}
void printConnectionData(){
  myGLCD.clrScr();  
  if (connection)
  {
    myGLCD.print("Connected!", 15, 0);
  }else{
    myGLCD.print("Not Connected!", LEFT, 0);
    myGLCD.print("Retrying...", LEFT, 25);
  }
  myGLCD.update();
}
  
void printProcessing(){
  printTimeData();
  myGLCD.print("Syncing..", CENTER, 25);
  myGLCD.update();
}

void printConfigData(){
  myGLCD.clrScr();
  myGLCD.print("UPDATING CONFIG", LEFT, 0);
  myGLCD.update();
  delay(1500);
}

void printRequestData(){
  failRate = ((getFailedRequests()*1.0/getTotalRequests())*100);
  String temp = "";
  
  myGLCD.clrScr();
  myGLCD.print("SUCCESS : ", LEFT, 0);
  myGLCD.printNumI(getSuccessfulRequests(), 65, 0);
  myGLCD.print("LOSS : ", LEFT, 12);
  myGLCD.printNumI(getFailedRequests(), 65, 12);
  myGLCD.print("TOTAL : ", LEFT, 24);
  myGLCD.printNumI(getTotalRequests(), 65, 24);
  myGLCD.print("FAIL : ", LEFT, 36);
  myGLCD.printNumI((int)getFailRate(), 60, 36);
  myGLCD.print("%", RIGHT, 36);
  myGLCD.update();
}

void printStatusData(){  
  myGLCD.clrScr();
  myGLCD.print("DOOR : ", LEFT, 0);
  if (isDoorOpen())
  {
    myGLCD.print("OPEN", 45, 0);
  }else{
    myGLCD.print("CLOSED", 45, 0);
  }
  myGLCD.print("LIGHT : ", LEFT, 10);
  if (isLightOn())
  {
    myGLCD.print("ON", 65, 10);
  }else{
    myGLCD.print("OFF", 65, 10);
  }
  myGLCD.print("ALARM : ", LEFT, 20);
  if (isAlarmOn())
  {
    myGLCD.print("ON", 65, 20);
  }else{
    myGLCD.print("OFF", 65, 20);
  }
  myGLCD.print("GENERATOR : ", LEFT, 30);
  if (isGeneratorOn())
  {
    myGLCD.print("ON", 65, 30);
  }else{
    myGLCD.print("OFF", 65, 30);
  }
  myGLCD.print("AC : ", LEFT, 40);
  if (isAcOn())
  {
    myGLCD.print("ON", 65, 40);
  }else{
    myGLCD.print("OFF", 65, 40);
  }  
  myGLCD.print("MAINS : ", LEFT, 50);
  if (isMainsOn())
  {
    myGLCD.print("ON", 65, 50);
  }else{
    myGLCD.print("OFF", 65, 50);
  }
  myGLCD.update();  
  }

void printSiteData(){
	printRequestData();
	delay(3000);
	myGLCD.clrScr();
	printStatusData();
	delay(3000);
}
