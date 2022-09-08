#include<WiFi.h>
#include <ESP32Servo.h>
#include <ThingSpeak.h>

char ssid[] = "your wifi network name";   // your network SSID (name)
char pass[] = "password";

WiFiClient client;

unsigned long myChannelNumber =  XXXXXXX;
const char * myReadAPIKey = "your read API key goes here";

#define SERVO_PIN 15 // ESP32 pin GIOP26 connected to servo motor

Servo servoMotor;
int a;

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  ThingSpeak.begin(client);
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
}

void loop() {

   if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
   }
   
   while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);    
    }
   
  Serial.println("\nConnected.");

  int a = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey); //READ THE VALUE FROM FIELD AND STORE IN A VARIABLE (a)
  Serial.println("Door State");
  Serial.print(a);
  delay(1000);

  servoMotor.write(90);
 
  
  if (a==0){
    servoMotor.write(180);
  }

   else{
    servoMotor.write(90);
    }
 }