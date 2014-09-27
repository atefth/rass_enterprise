const uint8_t chipSelect = 10;
SdFat sd;
SdFile config;
const uint8_t spiSpeed = SPI_HALF_SPEED;
int siteRead = 0;
int rfidRead[TOTAL_USERS];

void connectToSD(){
	if (!sd.begin(chipSelect, SPI_FULL_SPEED)) sd.initErrorHalt();  
}
void clearConfig(){
	//open the current config.txt file to delete
	if (!config.open("config.txt", O_RDWR | O_CREAT | O_AT_END)) {
	  sd.errorHalt("opening config.txt for write failed");
	}

	Serial.println("removing old config file");

	//remove the file
	if (!config.remove()) Serial.println("failed to remove existing config file");
}

void initConfig(){
    // re-open the file for reading:
    if (!config.open("config.txt", O_READ)) {
      sd.errorHalt("opening config.txt for read failed");
    }
    Serial.println("config.txt:");

    // read from the file until there's nothing else in it:
    int data = config.read();
    while (data >= 0) {
      char c = (char)data;

      //skip input
      while (c != ' ') {
        data = config.read();
        c = (char)data;
      }
      data = config.read();
      c = (char)data;
      char site[4];
      int count = 0;

      //read site id if not read
      if (!siteRead)
      {
        //read site id
        while (data != 13) {
          site[count] = c;
          data = config.read();
          c = (char)data;      
          count++;
        }

        //store site id in ram
        // site_id = atol(site);
        siteRead = 1;
      }

      count = 0;
      data = config.read();
      c = (char)data;
      while (c != '!' && count < 10) {
        //skip inputs
        while (c != ' ') {
          data = config.read();
          c = (char)data;
        }

        data = config.read();
        c = (char)data;
        
        if (rfidRead[count] == 0)
        {
          char digits[10];
          for (int i = 0; i < 9; i++)
          {
            digits[i] = 0;
          }
          //read all 9 rfid digits
          for (int i = 0; i < 9; i++)
          {
            digits[i] = c;
            data = config.read();
            c = (char)data;
          }

          data = config.read();
          c = (char)data;

          //update access to rfid
          if (c == 'F' || c == 'T')
          {
            if (c == 'T')
            {
              access[count] = 1;
            }else{
              access[count] = 0;
            }
          }

          //store rfid in ram
          rfid[count] = atol(digits);
          if (rfid[count] < 100)
          {
            rfid[count] = 0;
            count++;
            break;
          }

          rfidRead[count] = 1;
          count++;
        }

        data = config.read();
        c = (char)data;      

      }
      break;
    }
    // close the file:
    config.close();
  }

void updateConfig(){
    clearConfig();
    // open the file for write at end like the Native SD library
    if (!config.open("config.txt", O_RDWR | O_CREAT | O_AT_END)) {
      sd.errorHalt("opening config.txt for write failed");
    }
    // if the file opened okay, write to it:
    Serial.print("Updating Config File");
    config.print("site_id ");
    config.println(SITE);
    for (int i = 0; i < TOTAL_USERS; i++)
    {
      config.print("rfid ");
      config.print(rfid[i]);
      config.print(" ");
      if (access[i])
      {
        config.print("T");
      }else{
        config.print("F");
      }
      config.println();
    }

    config.println("!");

    // close the file:
    config.close();
    Serial.println("done.");
}
