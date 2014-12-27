char relay;
char status;

void initBluetooth()
{
 Serial1.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
// Serial1.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
// Serial1.print("\r\n+STNA=RassProto\r\n"); //set the bluetooth name as "RassProto"
// Serial1.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
// Serial1.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
// delay(2000); // This delay is required.
// Serial1.print("\r\n+INQ=1\r\n"); //Amake the slave bluetooth inquirable 
// Serial.println("The slave bluetooth is inquirable!");
 delay(2000); // This delay is required.
 Serial1.flush();
}