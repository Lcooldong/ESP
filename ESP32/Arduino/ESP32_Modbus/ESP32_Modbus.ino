#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>



const int REG = 528;               // Modbus Hreg Offset
IPAddress remote(192, 168, 30, 13);  // Address of Modbus Slave device
const int LOOP_COUNT = 1;

ModbusIP mb;  //ModbusIP object

void setup() {
  Serial.begin(115200);
 
  WiFi.begin("it", "@Polytech");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.client();
}

uint16_t res = 0;
uint8_t show = LOOP_COUNT;

void loop() {
  if (mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established
    mb.readHreg(remote, REG, &res);  // Initiate Read Coil from Modbus Slave
  } else {
    mb.connect(remote);           // Try to connect if no connection
  }
  mb.task();                      // Common local Modbus task
  delay(1);                     // Pulling interval
  Serial.println(res);
  if (!show--) {                   // Display Slave register value one time per second (with default settings)
    //Serial.println(res);
    show = LOOP_COUNT;
  }
}
