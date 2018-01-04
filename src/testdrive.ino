/*
 * Test the motor and servo of the car.
 *      
 */
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>

Servo carServo;
Adafruit_MMA8451 mma = Adafruit_MMA8451();

#define pwmToMotor    2             // Defining the PWM pin to run the motor
#define servoPin      48            // Defining the servo control pin
#define dirPin        3             // Determines wherether wheels move forward or reverse

void driveCircle();     
void driveStraight();            
void carStop();                     


int carSpeed        = 20;           // Speed of the car [0-255]
int turnAngle         = 130;        // Angle to turn to make a circle
int straightAngle     = 90;         // Wheel reset angle
int adjustingDelay    = 250;        // Time delay to allow servo to adjust wheel angle

void setup() {
  Serial.begin(9600);
  
  //check MMA sensor before starting
  if( !mma.begin() ) {
    Serial.println("Cannot find MMA8451");
    while (1);
  }

  mma.setRange(MMA8451_RANGE_2_G);


  carServo.attach(servoPin);        // setting the Servo motor control for the pin 

  // Re-adjust wheels and pause for half a second
  carServo.write(straightAngle);
  delay(adjustingDelay);

  driveStraight();
}

void loop() {

  /* Detect collision and back up if detected */

  mma.read();
  sensors_event_t event;
  mma.getEvent(&event);

  if(event.acceleration.y < 1.0) {
    carStop();
    digitalWrite(dirPin, HIGH);
    carServo.write(turnAngle);
    analogWrite(pwmToMotor, -carSpeed);
    delay(3000);
    
  } else {
    driveStraight();
  }

}

void driveCircle() {  
  carServo.write(turnAngle);
  analogWrite(pwmToMotor, carSpeed);
  delay(4000); //run for 4 seconds
}

void driveStraight() {
  digitalWrite(dirPin, LOW);
  carServo.write(straightAngle);
  analogWrite(pwmToMotor, carSpeed);
  delay(3000);
}

void carStop() {
  analogWrite(pwmToMotor, 0);
  carServo.write(straightAngle);
  delay(adjustingDelay);
}






