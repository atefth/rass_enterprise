Remote Access Security System, Enterprise Edition

Structure of modules

#relays.h
	void initRelays()
	void toggleSwitch(int id)
	void turnOnRelay(int id)
	void turnOffRelay(int id)
	int getRelayStatus(int id)
	void showRelayData()

#users.h
	void initUsers()
	void setRfid(int id, long rfid)
	long getRfid(int id, long rfid)
	void setAccessRight(int id, int access)
	long getAccessRight(long rfid)
	void showUserData()

#site.h
	int getSite()
	long getLastSyncTime()
	void setLastSyncTime(long time)
	int getSyncDuration()	
	int getSuccessfulRequests()
	int getFailedRequests()
	int getTotalRequests()
	double getFailRate()
	void showSiteData()

#http.h
	void initGSM(int rate)
	void powerOn()
	void checkConnection
	void initRequest()
	void makeRequest(string url)
	void terminateRequest()
	boolean syncServer()
	void attemptRequest()
	boolean readRfid()
	boolean readAccessRight()
	boolean readRelay()
	void clearSerialData()
	void showSerialData()

#lcd.h


