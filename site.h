long lastSyncTime;
long syncDuration;

static int successfulRequests;
static int failedRequests;
static int totalRequests;
static double failRate;

void initSite(){
	Serial.println("Initializing Site");
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

long getSyncDuration(){
	return syncDuration;
}

void setLastSyncTime(long timeToSet){
	lastSyncTime = timeToSet;
}

void showSyncDuration(){
	syncDuration =  millis() - lastSyncTime;
	Serial.print(syncDuration * 1.0/1000);
	Serial.println(" seconds and counting...");
}

void incrementSuccessfulRequests(){
	successfulRequests++;
}

void incrementFailedRequests(){
	failedRequests++;
}

void incrementTotalRequests(){
	totalRequests++;
}

void updateFailRate(){
	failRate = ((failedRequests * 1.0/ totalRequests) * 100.0);
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
	Serial.print(" - last sync time - ");
	Serial.println(syncDuration * 1.0 / 1000);
}
