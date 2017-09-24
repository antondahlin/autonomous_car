/*
 * Test the motor and servo of the car.
 *      
 */
 
#include <Servo.h>

Servo carServo;

#define pwmToMotor    2             // Defining the PWM pin to run the motor
#define servoPin      48            // Defining the servo control pin
#define dirPin        3             // Determines wherether wheels move forward or reverse

void driveCircle();     
void driveStraight();            
void carStop();                     


int carSpeed        = 15;           // Speed of the car [0-255]
int turnAngle         = 130;        // Angle to turn to make a circle
int straightAngle     = 90;         // Wheel reset angle
int adjustingDelay    = 250;        // Time delay to allow servo to adjust wheel angle

void setup() {
  carServo.attach(servoPin);        // setting the Servo motor control for the pin 
}

void loop() {
  // Re-adjust wheels and pause for half a second
  carServo.write(straightAngle);
  delay(adjustingDelay);

  driveStraight();

  carSpeed = carSpeed;
  driveCircle();
  carStop();

  delay(2000);
}

void driveCircle() {  
  carServo.write(turnAngle);
  analogWrite(pwmToMotor, carSpeed);
  delay(4000); //run for 4 seconds
}

void driveStraight() {
  carServo.write(straightAngle);
  analogWrite(pwmToMotor, carSpeed);
  delay(3000);
}

void carStop() {
  analogWrite(pwmToMotor, 0);
  carServo.write(straightAngle);
  delay(adjustingDelay);
}






