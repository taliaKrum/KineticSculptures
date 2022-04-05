#include <Ticker.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial

/** Task handle for the light value read task */
TaskHandle_t wifiTaskHandle = NULL;
/** Ticker for temperature reading */
Ticker wifiTicker;
/** Flag if task should run */
bool tasksEnabled = false;
uint32_t delayMS;
bool wifiVal = false;
String address= "http://134.122.113.13/trk2123/running";

//Hotspot name and password 
const char *ssid_Router     = "Ariel's phone"; 
const char *password_Router = "hi!!!!!!"; 

//DC motors stuff 
int in1Pin = 12;      // Define L293D channel 1 pin
int in2Pin = 22;      // Define L293D channel 2 pin
int enable1Pin = 13;  // Define L293D enable 1 pin
int channel = 0;
boolean rotationDir;  // Define a variable to save the motor's rotation direction
int rotationSpeed;    // Define a variable to save the motor rotation speed

//Stepper Motor stuff 
int outPorts[] = {33, 27, 26, 25};
int outPorts2[] = {12, 13, 15, 17};
int posVal = 0;    // variable to store the servo position

// Wifi setup should go here
void setup() {
  //DC motor
  // Initialize the pin into an output mode:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  //turn off motors - initial state
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  
  USE_SERIAL.begin(115200);
  
  WiFi.begin(ssid_Router, password_Router);
  USE_SERIAL.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    USE_SERIAL.print(".");
  }
  USE_SERIAL.println("\nConnected, IP address: ");
  USE_SERIAL.println(WiFi.localIP());
  USE_SERIAL.println("Setup End");
  
  //STEP
  // set pins to output
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }

  //STEP2
  for(int i = 0; i < 4; i++) {
    pinMode(outPorts2[i], OUTPUT);
  }
  
  xTaskCreatePinnedToCore(
      wifiTask,                       /* Function to implement the task */
      "wifiTask ",                    /* Name of the task */
      4000,                           /* Stack size in words */
      NULL,                           /* Task input parameter */
      5,                              /* Priority of the task */
      &wifiTaskHandle,                /* Task handle. */
      1                               /* Core where the task should run */
  );

  Serial.println("created wifi task");

  if (wifiTaskHandle == NULL) {
    Serial.println("Failed to start task for wifi update");
  } else {
    // Start update of environment data every 4 seconds, could make this check more often 
    wifiTicker.attach(4, triggerGetWifi);
  }
}

/**
 * triggerGetWifi
 * Sets flag dhtUpdated to true for handling in loop()
 * called by Ticker getWifiTimer
 */
void triggerGetWifi() {
  if (wifiTaskHandle != NULL) {
     xTaskResumeFromISR(wifiTaskHandle);
  }
}

void wifiTask(void *pvParameters) {
  Serial.println("wifiTask loop started");
  while (1) // tempTask loop
  {
    if (tasksEnabled) {
      // Get temperature values
      goWifi();
    }
    // Got sleep again
    vTaskSuspend(NULL);
  }
}

bool goWifi() {
  //WIFI STUFF
  if((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(address);
 
    int httpCode = http.GET(); // start connection and send HTTP header
    if (httpCode == HTTP_CODE_OK) { 
        String response = http.getString();
        if (response.equals("false")) {
            // Do not run sculpture, perhaps sleep for a couple seconds
            wifiVal = false;
            delay(2000); //3 seconds 
        }
        else if(response.equals("true")) {
            // Run sculpture FIGURE OUT WHAT TO DO HERE
            wifiVal = true;
        }
        USE_SERIAL.println("Response was: " + response);
    } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(500); // sleep for half of a second
  }
  return true;
}

void loop() { //first core (Core 0)
  // Delay between measurements.
  if (!tasksEnabled) {
    // Enable task that will read values from the DHT sensor
    tasksEnabled = true;
    if (wifiTaskHandle != NULL) {
      vTaskResume(wifiTaskHandle); //pass in tempTaskHandle to resume this task
    }
  }

  if(wifiVal == true) {
    //run motors
    //STEPPER FULL TURN (connected to same pins????) 
    moveSteps(true, 32 * 64, 3);
    moveSteps(false, 32 * 64, 3);
    //DC MOTOR
    analogWrite(enable1Pin, 150);
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
   }
   else {
    //DC motor is off when wifiVal == false
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
   }
  yield();
}

//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms,3,20));        // Control the speed
  }
}

void moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) {  // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else {      // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

void moveAround(bool dir, int turns, byte ms){
  for(int i=0;i<turns;i++)
    moveSteps(dir,32*64,ms);
}
void moveAngle(bool dir, int angle, byte ms){
  moveSteps(dir,(angle*32*64/360),ms);
}
