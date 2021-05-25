#include<AFMotor.h>
#include<NewPing.h>
#include<Servo.h>

#define ECHO_PIN_CENTER A0            // Defining the Input  Signal from Center Ultrasonic Sensor and sets pin to A0 of Arduino Motor Shield.
#define TRIGGER_PIN_CENTER A1         // Defining the Output Signal from Center Ultrasonic Sensor and sets pin to A1 of Arduino Motor Shield.
#define ECHO_PIN_RIGHT A2             // Defining the Input  Signal from Right  Ultrasonic Sensor and sets pin to A2 of Arduino Motor Shield.
#define TRIGGER_PIN_RIGHT A3          // Defining the Output Signal from Right  Ultrasonic Sensor and sets pin to A3 of Arduino Motor Shield.
#define ECHO_PIN_LEFT A4              // Defining the Input  Signal from Left   Ultrasonic Sensor and sets pin to A4 of Arduino Motor Shield.
#define TRIGGER_PIN_LEFT A5           // Defining the Output Signal from Left   Ultrasonic Sensor and sets pin to A5 of Arduino Motor Shield.
#define MAX_DISTANCE 30              // Defining the Max Distance that the Sensors can send and receive a pulse.

NewPing sonarCenter(TRIGGER_PIN_CENTER, ECHO_PIN_CENTER, MAX_DISTANCE); // Defining the NewPing Library for Center Ultrasonic Sensor.
NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);    // Defining the NewPing Library for Right  Ultrasonic Sensor.
NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);       // Defining the NewPing Library for Left   Ultrasonic Sensor.

AF_DCMotor Motor1(1, MOTOR12_1KHZ);   // Defining the AF_DCMotor Library for FRONT RIGHT Motor.
AF_DCMotor Motor2(2, MOTOR12_1KHZ);   // Defining the AF_DCMotor Library for FRONT LEFT  Motor.
AF_DCMotor Motor3(3, MOTOR34_1KHZ);   // Defining the AF_DCMotor Library for REAR  LEFT  Motor.
AF_DCMotor Motor4(4, MOTOR34_1KHZ);   // Defining the AF_DCMotor Library for REAR  RIGHT Motor.

Servo myservo;                        // Defining the Servo Library for Servo Motor.
int LED1 = 2;                         // Declaring the Right LEDs pin position on Arduino Motor Shield.
int LED2 = 13;                        // Declaring the Left LEDs pin position on Arduino Motor Shield.

void setup() {

  Serial.begin(9600);                  // Sets the data rate in bits per second (baud) for serial data transmission.
  myservo.attach(10);                  // Declaring the Servo Motor's pin position on Arduino Motor Shield.
  myservo.write(95);                   // Declaring the degrees of Servo Motor's starting point.
  pinMode(LED1, OUTPUT);               // Initiating on start the OUTPUT of Right LEDs.
  pinMode(LED2, OUTPUT);               // Initiating on start the OUTPUT of Left  LEDs.


  if (digitalRead(LED1) == LOW && digitalRead(LED2) == LOW) //Declares that if Right LEDs and Left LEDs are turned OFF,specifically the readings are 0(LOW),then proceed to the following code.

  {
    
    for (int i = 0; i <= 4; i++) //For loop to count and perform one by one the instuctions given.
    
    {
      digitalWrite(LED1, HIGH);  // Right LEDs turn ON.
      delay (150);               // Delay any action for 150 milliseconds.
      digitalWrite(LED1, LOW);   // Right LEDs turn OFF.
      delay (50);                // Delay any action for 50 milliseconds.
      digitalWrite(LED2, HIGH);  // Left LEDs turn ON.
      delay (150);               // Delay any action for 150 milliseconds.
      digitalWrite(LED2, LOW);   // Left LEDs turn OFF.
      delay (50);                // Delay any action for 50 milliseconds.
      
    }
    
  }
}

void loop()

{

  unsigned int distanceCenter = sonarCenter.ping_cm(); // Defining the distanceCenter as sonarCenter provided by the NewPing Library.
  unsigned int distanceRight  = sonarRight.ping_cm();  // Defining the distanceRight  as sonarRight  provided by the NewPing Library.
  unsigned int distanceLeft   = sonarLeft.ping_cm();   // Defining the distanceLeft   as sonarLeft   provided by the NewPing Library.



  moveForward();                         // Calls the moveForward() funtion.
  Serial.print("Center distance is : "); // Serial Monitor display "Center distance is : ".
  Serial.println(distanceCenter);        // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
  delay(5);;                             // Delay any action for 5 milliseconds.


  if (distanceCenter >= 10  && distanceCenter <= 15) // MOVE FORWARD,OBJECT IN GIVEN RANGE. //Declares that if distance of Center Sensor and object is >= 10cm && <= 15cm then proceed to the following code.

  {
    
    moveBackward();                        // Calls the moveBackward() funtion.
    Serial.println("MOVING BACKWARDS.");   // Serial Monitor display "MOVING BACKWARDS.".
    delay(250);                            // Delay any action for 250 milliseconds.
    Freeze();                              // Calls the Freeze() funtion.
    delay(200);                            // Delay any action for 200 milliseconds.
    distanceRight = lookRight();           // Defining that the specific variable equals the provided function.
    Serial.print("Right distance is : ");  // Serial Monitor display "Center distance is : ".
    Serial.println(distanceRight);         // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    delay(200);                            // Delay any action for 200 milliseconds.
    distanceLeft = lookLeft();             // Defining that the specific variable equals the provided function.
    Serial.print("Left distance is : ");   // Serial Monitor display "Center distance is : ".
    Serial.println(distanceLeft);          // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    delay(200);                            // Delay any action for 200 milliseconds.

    if (distanceRight >= distanceLeft)     //Declares that if Right Ultrasonic Sernor's readings are >= to Left Ultrasonic Sernor's readings then proceed to the following code.
    
    {
      turnLeft();                          // Calls the turnLeft() funtion.
      Freeze();                            // Calls the Freeze() funtion.
    }
    
    else //(distanceLeft >= distanceRight) //Declares that if Left Ultrasonic Sernor's readings are >= to Right Ultrasonic Sernor's readings then proceed to the following code.
    
    {
      turnRight();                         // Calls the turnRight() funtion.
      Freeze();                            // Calls the Freeze() funtion.
    }
  }
  
  else if (distanceRight >= 2 && distanceRight <= 10) // MOVE LEFT,OBJECT TOO CLOSE. //Declares that if distance of Right Sensor and object is >= 2cm && <= 10cm then proceed to the following code.
  
  {
    
    Motor1.setSpeed(255);                 // Set Speed of Motor1 at 255 RPM.
    Motor1.run(BACKWARD);                 // MOVE FORWARD
    Motor2.setSpeed(255);                 // Set Speed of Motor2 at 255 RPM.
    Motor2.run(FORWARD);                  // MOVE BACKWARD
    Motor3.setSpeed(255);                 // Set Speed of Motor3 at 255 RPM.
    Motor3.run(FORWARD);                  // MOVE BACKWARD
    Motor4.setSpeed(255);                 // Set Speed of Motor4 at 255 RPM.
    Motor4.run(BACKWARD);                 // MOVE FORWARD
    delay(200);;                          // Delay any action for 200 milliseconds.

    digitalWrite(LED1, HIGH);             // Right LEDs turn ON.
    delay (150);                          // Delay any action for 150 milliseconds.
    digitalWrite(LED1, LOW);              // Right LEDs turn OFF.
    delay (50);                           // Delay any action for 50 milliseconds.

    Serial.print("RIGHT distance is : "); // Serial Monitor display "Center distance is : ".
    Serial.println(distanceRight);        // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    Serial.println("MOVING LEFT.");       // Serial Monitor display "MOVING BACKWARDS.".
    delay(5);                             // Delay any actions for 5 milliseconds.
    
  }
  
  else if (distanceLeft >= 2 && distanceLeft <= 10)  // MOVE RIGHT,OBJECT TOO CLOSE. //Declares that if distance of Left Sensor and object is >= 2cm && <= 10cm then proceed to the following code.
  
  {
    
    Motor1.setSpeed(255);                // Set Speed of Motor1 at 255 RPM.
    Motor1.run(FORWARD);                 // MOVE BACKWARD
    Motor2.setSpeed(255);                // Set Speed of Motor2 at 255 RPM.
    Motor2.run(BACKWARD);                // MOVE FORWARD
    Motor3.setSpeed(255);                // Set Speed of Motor3 at 255 RPM.
    Motor3.run(BACKWARD);                // MOVE FORWARD
    Motor4.setSpeed(255);                // Set Speed of Motor4 at 255 RPM.
    Motor4.run(FORWARD);                 // MOVE BACKWARD
    delay(200);;                         // Delay any action for 200 milliseconds.


    digitalWrite(LED2, HIGH);            // Left LEDs turn ON.
    delay (150);                         // Delay any action for 150 milliseconds.
    digitalWrite(LED2, LOW);             // Left LEDs turn OFF.
    delay (50);                          // Delay any action for 50 milliseconds.

    Serial.print("Left distance is : "); // Serial Monitor display "Center distance is : ".
    Serial.println(distanceLeft);        // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    Serial.println("MOVING RIGHT.");     // Serial Monitor display "MOVING BACKWARDS.".
    delay(5);                            // Delay any actions for 5 milliseconds.
    
  }
}

int lookRight()             //Declaring the lookRight() Function.

{
  
  myservo.write(30);        // Sets the Servo Motor's degrees at 30.
  delay(500);               // Delay any action for 500 milliseconds.
  int distanceRight = sonarRight.ping_cm();
  delay(100);               // Delay any action for 100 milliseconds.
  myservo.write(95);        // Sets the Servo Motor's degrees at 95.
  return distanceRight;     // Terminates the lookRight function and returns its value.
  
}

int lookLeft()              //Declaring the lookLeft() Function.

{
  
  myservo.write(170);       // Sets the Servo Motor's degrees at 170.
  delay(500);               // Delay any action for 500 milliseconds.
  unsigned int distanceLeft = sonarLeft.ping_cm();
  delay(100);               // Delay any action for 100 milliseconds.
  myservo.write(95);        // Sets the Servo Motor's degrees at 95.
  return distanceLeft;      // Terminates the lookLeft function and returns its value.
  
}

void Freeze()               //Declaring the Freeze() Function.

{
  
  Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
  Motor1.run(RELEASE);      // FREEZE
  Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
  Motor2.run(RELEASE);      // FREEZE
  Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
  Motor3.run(RELEASE);      // FREEZE
  Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
  Motor4.run(RELEASE);      // FREEZE

}

void moveForward()          //Declaring the moveForward() Function.

{

  Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
  Motor1.run(BACKWARD);     // MOVE FORWARD
  Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
  Motor2.run(BACKWARD);     // MOVE FORWARD
  Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
  Motor3.run(BACKWARD);     // MOVE FORWARD
  Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
  Motor4.run(BACKWARD);     // MOVE FORWARD

}

void moveBackward()         //Declaring the moveBackward() Function.

{
  
  Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
  Motor1.run(FORWARD);      // MOVE BACKWARD
  Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
  Motor2.run(FORWARD);      // MOVE BACKWARD
  Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
  Motor3.run(FORWARD);      // MOVE BACKWARD
  Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
  Motor4.run(FORWARD);      // MOVE BACKWARD

  digitalWrite(LED1, HIGH); // Right LEDs turn ON.
  digitalWrite(LED2, HIGH); // Left  LEDs turn ON.
  delay(200);               // Delay any action for 200 milliseconds.
  digitalWrite(LED1, LOW);  // Right LEDs turn OFF.
  digitalWrite(LED2, LOW);  // Left LEDs turn OFF.
  delay (50);               // Delay any action for 50 milliseconds.

}

void turnRight()            //Declaring the turnRight() Function.

{
  
  Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
  Motor1.run(FORWARD);      // MOVE BACKWARD
  Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
  Motor2.run(BACKWARD);     // MOVE FORWARD
  Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
  Motor3.run(BACKWARD);     // MOVE FORWARD
  Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
  Motor4.run(FORWARD);      // MOVE BACKWARD
  delay(1000);              // Delay any action for 1000 milliseconds.

}

void turnLeft()             //Declaring the turnLeft() Function.

{
  
  Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
  Motor1.run(BACKWARD);     // MOVE FORWARD
  Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
  Motor2.run(FORWARD);      // MOVE BACKWARD
  Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
  Motor3.run(FORWARD);      // MOVE BACKWARD
  Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
  Motor4.run(BACKWARD);     // MOVE FORWARD
  delay(1000);              // Delay any action for 1000 milliseconds.

}
