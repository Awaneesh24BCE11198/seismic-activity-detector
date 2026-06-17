#include <Wire.h> 

const int ADXL345 = 0x53;     
const int ledPin = 13;        
const int buzzerPin = 12;     

// 1.0g represents standard Earth gravity. 
// A threshold of 1.5g requires a deliberate physical shock.
const float threshold = 1.5;  

void setup() {
  Serial.begin(9600);         
  Wire.begin();               

  pinMode(ledPin, OUTPUT);    
  pinMode(buzzerPin, OUTPUT); 
  
  digitalWrite(ledPin, LOW);     
  // Buzzer uses "Active-Low" logic. HIGH forces it to stay quiet.
  digitalWrite(buzzerPin, HIGH); 

  // Wake Up the ADXL345 Sensor
  Wire.beginTransmission(ADXL345); 
  Wire.write(0x2D);           
  Wire.write(8);              
  Wire.endTransmission();
}

void loop() {
  // Request 6 bytes of data (X, Y, Z axes)
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);                   
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); 

  // Stitch raw bytes into integers
  int16_t x = (Wire.read() | Wire.read() << 8);
  int16_t y = (Wire.read() | Wire.read() << 8);
  int16_t z = (Wire.read() | Wire.read() << 8);

  // Convert raw data to real-world G-Force
  float xG = x / 256.0;
  float yG = y / 256.0;
  float zG = z / 256.0;

  // Calculate total 3D vector magnitude
  float totalForce = sqrt((xG * xG) + (yG * yG) + (zG * zG));

  // The Alarm Trigger Logic
  if (totalForce > threshold) {
    // Trigger Active-Low buzzer (LOW = ON)
    digitalWrite(buzzerPin, LOW); 
    
    // Rapid strobe sequence
    for (int i = 0; i < 10; i++) { 
      digitalWrite(ledPin, HIGH); 
      delay(50);                  
      digitalWrite(ledPin, LOW);  
      delay(50);                  
    }
    
    // Shut off Active-Low buzzer (HIGH = OFF)
    digitalWrite(buzzerPin, HIGH); 
    delay(1000); 
  }

  delay(100); 
}