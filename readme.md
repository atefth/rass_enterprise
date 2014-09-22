Remote Access Security System, Enterprise Edition

Structure of modules

#relay.h
	void toggleSwitch(int id)
	int getRelayStatus(int id)

#users.h
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
	void showSiteData()

#http.h
	void initRequest()
	void makeRequest(string url)
	void terminateRequest()
	long readRfid()
	long readAccessRight()
	int readRelay()



