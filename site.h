long lastSyncTime;
long syncDuration;

static int successfulRequests;
static int failedRequests;
static int totalRequests;
static double failRate;

void initSite(){
	successfulRequests = 0;
	failedRequests = 0;
	totalRequests = 0;
	failRate = 0.0;
}

int getSite(){
	return SITE;
}

long getLastSyncTime(){
	return lastSyncTime;
}

void setLastSyncTime(long timeToSet){
	lastSyncTime = timeToSet;
}

int getSyncDuration(){
	syncDuration =  millis() - lastSyncTime;
	return syncDuration;
}

int getSuccessfulRequests(){
	return successfulRequests;
}

int getFailedRequests(){
	return failedRequests;
}

int getTotalRequests(){
	return totalRequests;
}

double getFailRate(){
	return failRate;
}

void showSiteData(){
	Serial.print("Site ");
	Serial.print(SITE);
	Serial.print(" time until last sync ");
	Serial.print(syncDuration);
}