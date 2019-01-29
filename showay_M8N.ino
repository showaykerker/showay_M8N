#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   9600-baud serial GPS device hooked up on pins 8(rx) and 9(tx) and a HMC5883 Magnetic Compass
   connected to the SCL/SDA pins.
*/

static const int RXPin = 8, TXPin = 9;
static const uint32_t GPSBaud = 9600;
const int decimals = 8;

// Assign a Uniquej ID to the HMC5883 Compass Sensor
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the NEO-6m GPS module
SoftwareSerial ss(RXPin, TXPin);


void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayGpsInfo();
}

void displayGpsInfo(){
  Serial.print(F("Location: ")); 
  if (gps.location.isValid()){
    Serial.print(gps.location.lat(), decimals);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), decimals);
    Serial.print(F(","));
  }
  else{
	Serial.print(0, decimals);
    Serial.print(F(","));
	Serial.print(0, decimals);
    Serial.print(F(","));
  }

  if(mag.begin()){
    float heading = displayCompassInfo();
	Serial.println(heading, decimals);
  }
  else{
	Serial.println(0, decimals);
  }
  delay(500);
}

float displayCompassInfo(){
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = -0.0773762577 + M_PI/2;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI) heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  return headingDegrees;
}

