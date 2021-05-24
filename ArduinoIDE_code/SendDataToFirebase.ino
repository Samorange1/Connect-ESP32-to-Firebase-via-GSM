/**************************************************************
 *
 * Send sensor data to Firebase via HTTP Post Request using Webclient 
 * Credits: Madhav Rawal and Aryaman Patel
 * Date: 05/2021
 *
 **************************************************************/
// To run this sketch, changes are required in line 32, 39 and 136




#define TINY_GSM_MODEM_SIM800


// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
#define SerialAT Serial1


//#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 64
//#endif
#define TINY_GSM_DEBUG SerialMon
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26

// Your GPRS credentials, if any
const char apn[]  = "xxxxxxxx";// CHANGES: Add your apn from the service provider of your simcard
const char gprsUser[] = "";
const char gprsPass[] = "";

// Server details

// CHANGES: Add the name of your website. NOTE: DONT put any preceeding headers like "https://.."
const char server[] = "xxxxxxxxxxxxxxxxxxxxx"; 

/* 
 *  The data that you want to send should be in this format
 *  /upload.php is the php file on the server and a=8 is data
 *  sent to it. 
 *  
 *  To record a datapoint, append the value at the end of the 
 *  character array resource
 *  
 *  if you want to send an array of data values, form the request as 
 *  a[]=1&a[]=2....
 *  
    */
    
char resource[] = "/upload.php?a[]=8"; 
const int  port = 80;

#include <TinyGsmClient.h>


#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);
 
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1L * 1000L;

void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  SerialMon.println("Wait...");

  // Set GSM module baud rate
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  SerialMon.println("Initializing modem...");
  modem.init();
  SerialMon.print(F("Connecting to "));
   SerialMon.print(apn);
   if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" fail");
      delay(10000);
      return;
    }
   SerialMon.println(" success");

   if (modem.isGprsConnected()) {
      SerialMon.println("GPRS connected");
  }

  SerialMon.print("Connecting to ");
  SerialMon.println(server);
  if (!client.connect(server, port)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");
  
  
}


void loop() {
   // send HTTP request every one second
  if(millis() - lastUpdateTime >=  updateInterval) {
      httpPostRequest();
      lastUpdateTime = millis();
   } 
}


void httpPostRequest(){
   // Makes the HTTP POST request
  SerialMon.println("Performing HTTP POST request...");
  
  
  if (client.connect(server,port)) {
    
  client.println("POST /upload.php? HTTP/1.1");
  // CHANGES: Add server name in place of XXXX
  client.println("Host:  XXXXXXXXXXXXXXXXX");
  client.println("User-Agent: TTGO-TCALL/1.0");
  client.println("Content-Type: application/x-www-form-urlencoded;");
  client.print("Content-Length: ");
  client.println(resource);
  client.println();
  
  
    
  uint32_t timeout = millis();
  
  while (client.connected() && millis() - timeout < 10000L) {
     // Print available data
     while (client.available()) {
         char c = client.read();
         SerialMon.print(c);
         timeout = millis();
     }
    } 
   }
  
  client.stop();
  Serial.println("Server Disconnected");
}
