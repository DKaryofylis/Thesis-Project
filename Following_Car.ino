#include<AFMotor.h>
#include<NewPing.h>
#include<Servo.h>

#define ECHO_PIN_CENTER A0            // Defining the Input  Signal from Center Ultrasonic Sensor and sets pin to A0 of Arduino Motor Shield.
#define TRIGGER_PIN_CENTER A1         // Defining the Output Signal from Center Ultrasonic Sensor and sets pin to A1 of Arduino Motor Shield.
#define ECHO_PIN_RIGHT A2             // Defining the Input  Signal from Right  Ultrasonic Sensor and sets pin to A2 of Arduino Motor Shield.
#define TRIGGER_PIN_RIGHT A3          // Defining the Output Signal from Right  Ultrasonic Sensor and sets pin to A3 of Arduino Motor Shield.
#define ECHO_PIN_LEFT A4              // Defining the Input  Signal from Left   Ultrasonic Sensor and sets pin to A4 of Arduino Motor Shield.
#define TRIGGER_PIN_LEFT A5           // Defining the Output Signal from Left   Ultrasonic Sensor and sets pin to A5 of Arduino Motor Shield.
#define MAX_DISTANCE 30               // Defining the Max Distance that the Sensors can send and receive a pulse.

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

void setup()

{

  Serial.begin(9600);
  myservo.attach(10);                  // Declaring the Servo Motor's pin position on Arduino Motor Shield.
  myservo.write(95);                   // Declaring the degrees of Servo Motor's starting point.

  /*pinMode(TRIGGER_PIN_CENTER, OUTPUT); // Initiating on start the OUTPUT of Center Ultrasonic Sensor.
  pinMode(ECHO_PIN_CENTER, INPUT);     // Initiating on start the INPUT  of Center Ultrasonic Sensor.
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);  // Initiating on start the OUTPUT of Right Ultrasonic Sensor.
  pinMode(ECHO_PIN_RIGHT, INPUT);      // Initiating on start the INPUT  of Right Ultrasonic Sensor.
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);   // Initiating on start the OUTPUT of Left Ultrasonic Sensor.
  pinMode(ECHO_PIN_LEFT, INPUT);       // Initiating on start the INPUT  of Left Ultrasonic Sensor.*/
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
  unsigned int distanceRight = sonarRight.ping_cm();   // Defining the distanceRight  as sonarRight  provided by the NewPing Library.
  unsigned int distanceLeft = sonarLeft.ping_cm();     // Defining the distanceLeft   as sonarLeft   provided by the NewPing Library.

 

  if (distanceCenter >= 20  && distanceCenter <= 30) // MOVE FORWARD,OBJECT IN GIVEN RANGE. // If distance of Center Sensor and object is >= 20cm && <= 30cm then procede to the following code.

  {

    digitalWrite(LED1, HIGH); // Right LEDs turn ON.
    digitalWrite(LED2, HIGH); // Left  LEDs turn ON.
    Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
    Motor1.run(BACKWARD);     // MOVE FORWARD
    Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
    Motor2.run(BACKWARD);     // MOVE FORWARD
    Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
    Motor3.run(BACKWARD);     // MOVE FORWARD
    Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
    Motor4.run(BACKWARD);     // MOVE FORWARD

    delay(100);               // Delay any actions for 100 milliseconds.

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE


    Serial.print("Center distance is : "); // Serial Monitor display "Center distance is : ".
    Serial.println(distanceCenter);        // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    Serial.println("MOVING FORWARD. (20cm - 30cm)");     // Serial Monitor display "MOVING FORWARD. (20cm - 30cm)."

    delay(5);                              // Delay any action for 5 milliseconds.
    digitalWrite(LED1, LOW);               // Right LEDs turn OFF.
    digitalWrite(LED2, LOW);               // Left LEDs turn OFF.

  }

  else if (distanceCenter >= 11  && distanceCenter <= 19) // FREEZE,OBJECT IN GIVEN RANGE. // If distance of Center Sensor and object is >= 11cm && <= 19cm then procede to the following code.

  {
    
    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE


    Serial.print("Center distance is : ");         // Serial Monitor display "Center distance is : ".
    Serial.println(distanceCenter);                // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    Serial.println("Range of Neutral State. (11cm - 19cm)");     // Serial Monitor display "Range of Neutral State. (11cm - 19cm)"

    delay(5);                                      // Delay any actions for 5 milliseconds.

  }

  else if (distanceCenter <= 10 && distanceCenter >= 3) // MOVE BACKWARDS,OBJECT TOO CLOSE. // If distance of Center Sensor and object is <= 10cm && >= 3cm then procede to the following code.

  {

    Motor1.setSpeed(255); // Set Speed of Motor1 at 255 RPM.
    Motor1.run(FORWARD);  // MOVE BACKWARD
    Motor2.setSpeed(255); // Set Speed of Motor2 at 255 RPM.
    Motor2.run(FORWARD);  // MOVE BACKWARD
    Motor3.setSpeed(255); // Set Speed of Motor3 at 255 RPM.
    Motor3.run(FORWARD);  // MOVE BACKWARD
    Motor4.setSpeed(255); // Set Speed of Motor4 at 255 RPM.
    Motor4.run(FORWARD);  // MOVE BACKWARD

    delay(100);           // Delay any actions for 100 milliseconds.

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Center distance is : "); // Serial Monitor display "Center distance is : ".
    Serial.println(distanceCenter);        // Serial Monitor display the distanceCenter provided by the Ultrasonic Sensor.
    Serial.println("MOVING BACKWARDS. (3cm - 10cm)");   // Serial Monitor display "MOVING BACKWARDS. (3cm - 10cm)".

    delay(5);                              // Delay any actions for 5 milliseconds.

  }

  else if (distanceRight >= 10 && distanceRight <= 15) // TURN RIGHT,OBJECT IN GIVEN RANGE. // If distance of Right Sensor and object is >= 10cm && <= 15cm then procede to the following code.

  {

    digitalWrite(LED1, HIGH); // Right LEDs turn ON.
    Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
    Motor1.run(FORWARD);      // MOVE BACKWARD
    Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
    Motor2.run(BACKWARD);     // MOVE FORWARD
    Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
    Motor3.run(BACKWARD);     // MOVE FORWARD
    Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
    Motor4.run(FORWARD);      // MOVE BACKWARD

    delay(250);               // Delay any actions for 250 milliseconds.

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Right distance is : ");   // Serial Monitor display "Right distance is : ".
    Serial.println(distanceRight);          // Serial Monitor display the distanceRight provided by the Ultrasonic Sensor.
    Serial.println("MOVING FORWARD RIGHT. (10cm - 15cm)"); // Serial Monitor display "MOVING FORWARD RIGHT. (10cm - 15cm)".

    delay(5);                               // Delay any actions for 5 milliseconds.
    digitalWrite(LED1, LOW);                // Right LEDs turn OFF.

  }

  else if (distanceRight >= 16) // FREEZE. EXCEEDED RANGE,OBJECT NOT FOUND. // If distance of Right Sensor and object is >= 16cm then procede to the following code.

  {

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Right distance is : ");    // Serial Monitor display "Right distance is : ".
    Serial.println(distanceRight);           // Serial Monitor display the distanceLeft provided by the Ultrasonic Sensor.
    Serial.println("Freeze. (>= 16cm)"); // Serial Monitor display "MOVING FORWARD LEFT. ( >= 16cm )".

    delay(5);                               // Delay any actions for 5 milliseconds.
    digitalWrite(LED2, LOW);                // Left LEDs turn OFF.

  }

  else if (distanceRight <=9 && distanceRight >=2) // FREEZE. EXCEEDED RANGE,OBJECT NOT FOUND. // If distance of Right Sensor and object is >= 16cm then procede to the following code.

  {

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Right distance is : ");    // Serial Monitor display "Right distance is : ".
    Serial.println(distanceRight);           // Serial Monitor display the distanceLeft provided by the Ultrasonic Sensor.
    Serial.println("Freeze. ( <= 9cm)");     // Serial Monitor display "MOVING FORWARD LEFT. ( >= 16cm )".

    delay(5);                               // Delay any actions for 5 milliseconds.
    digitalWrite(LED2, LOW);                // Left LEDs turn OFF.

  }

  /*else if (distanceRight <= 6 && distanceRight >= 3) // MOVE BACKWARDS RIGHT,OBJECT TOO CLOSE. // If distance of Right Sensor and object is <= 6cm && >= 3cm then procede to the following code.

  {

    Motor1.setSpeed(255); // Set Speed of Motor1 at 255 RPM.
    Motor1.run(BACKWARD); // MOVE FORWARD
    Motor2.setSpeed(255); // Set Speed of Motor2 at 255 RPM.
    Motor2.run(FORWARD);  // MOVE BACKWARD
    Motor3.setSpeed(255); // Set Speed of Motor3 at 255 RPM.
    Motor3.run(FORWARD);  // MOVE BACKWARD
    Motor4.setSpeed(255); // Set Speed of Motor4 at 255 RPM.
    Motor4.run(BACKWARD); // MOVE FORWARD

    delay(250);           // Delay any actions for 250 milliseconds.

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Right distance is : ");      // Serial Monitor display "Right distance is : ".
    Serial.println(distanceRight);             // Serial Monitor display the distanceRight provided by the Ultrasonic Sensor.
    Serial.println("MOVING BACKWARDS RIGHT. (3cm - 6cm)"); // Serial Monitor display "MOVING BACKWARDS RIGHT. (3cm - 6cm)".

    delay(5);                                  // Delay any actions for 5 milliseconds.

  }*/

  else if (distanceLeft >= 10 && distanceLeft <= 15) // TURN LEFT,OBJECT IN GIVEN RANGE. // If distance of Left Sensor and object is >= 10cm && <= 15cm then procede to the following code.

  {

    digitalWrite(LED2, HIGH); // Left LEDs turn ON.
    Motor1.setSpeed(255);     // Set Speed of Motor1 at 255 RPM.
    Motor1.run(BACKWARD);     // MOVE FORWARD
    Motor2.setSpeed(255);     // Set Speed of Motor2 at 255 RPM.
    Motor2.run(FORWARD);      // MOVE BACKWARD
    Motor3.setSpeed(255);     // Set Speed of Motor3 at 255 RPM.
    Motor3.run(FORWARD);      // MOVE BACKWARD
    Motor4.setSpeed(255);     // Set Speed of Motor4 at 255 RPM.
    Motor4.run(BACKWARD);     // MOVE FORWARD

    delay(250);               // Delay any actions for 250 milliseconds.

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Left distance is : ");    // Serial Monitor display "Left distance is : ".
    Serial.println(distanceLeft);           // Serial Monitor display the distanceLeft provided by the Ultrasonic Sensor.
    Serial.println("MOVING FORWARD LEFT. (10cm - 15cm)"); // Serial Monitor display "MOVING FORWARD LEFT. (10cm - 15cm)".

    delay(5);                               // Delay any actions for 5 milliseconds.
    digitalWrite(LED2, LOW);                // Left LEDs turn OFF.

  }
  
  else if (distanceLeft >= 16) // FREEZE. EXCEEDED RANGE,OBJECT NOT FOUND. // If distance of Left Sensor and object is >= 16cm then procede to the following code.

  {

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Left distance is : ");    // Serial Monitor display "Left distance is : ".
    Serial.println(distanceLeft);           // Serial Monitor display the distanceLeft provided by the Ultrasonic Sensor.
    Serial.println("Freeze. (>= 16cm)"); // Serial Monitor display "MOVING FORWARD LEFT. ( >= 16cm )".

    delay(5);                               // Delay any actions for 5 milliseconds.
    digitalWrite(LED2, LOW);                // Left LEDs turn OFF.

  }

  else if (distanceLeft <=9 && distanceLeft >=2) // FREEZE. EXCEEDED RANGE,OBJECT NOT FOUND. // If distance of Left Sensor and object is >= 16cm then procede to the following code.

  {

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Left distance is : ");    // Serial Monitor display "Left distance is : ".
    Serial.println(distanceLeft);           // Serial Monitor display the distanceLeft provided by the Ultrasonic Sensor.
    Serial.println("Freeze. ( <=9 cm)"); // Serial Monitor display "MOVING FORWARD LEFT. ( >= 16cm )".

    delay(5);                               // Delay any actions for 5 milliseconds.
    digitalWrite(LED2, LOW);                // Left LEDs turn OFF.

  }

 /* else if (distanceLeft <= 6 && distanceLeft >= 3 ) // MOVE BACKWARDS LEFT,OBJECT TOO CLOSE. // If distance of Left Sensor and object is <= 6cm && >= 3cm then procede to the following code.

  {

    Motor1.setSpeed(255); // Set Speed of Motor1 at 255 RPM.
    Motor1.run(FORWARD);  // MOVE BACKWARD
    Motor2.setSpeed(255); // Set Speed of Motor2 at 255 RPM.
    Motor2.run(BACKWARD); // MOVE FORWARD
    Motor3.setSpeed(255); // Set Speed of Motor3 at 255 RPM.
    Motor3.run(BACKWARD); // MOVE FORWARD
    Motor4.setSpeed(255); // Set Speed of Motor4 at 255 RPM.
    Motor4.run(FORWARD);  // MOVE BACKWARD

    delay(250);           // Delay any actions for 250 milliseconds.

    Motor1.setSpeed(0);       // Set Speed of Motor1 at 0 RPM.
    Motor1.run(RELEASE);      // FREEZE
    Motor2.setSpeed(0);       // Set Speed of Motor2 at 0 RPM.
    Motor2.run(RELEASE);      // FREEZE
    Motor3.setSpeed(0);       // Set Speed of Motor3 at 0 RPM.
    Motor3.run(RELEASE);      // FREEZE
    Motor4.setSpeed(0);       // Set Speed of Motor4 at 0 RPM.
    Motor4.run(RELEASE);      // FREEZE

    Serial.print("Left distance is : ");    // Serial Monitor display "Left distance is : ".
    Serial.println(distanceLeft);           // Serial Monitor display the distanceLeft provided by the Ultrasonic Sensor.
    Serial.println("MOVING BACKWARD LEFT. (3cm - 6cm)"); // Serial Monitor display "MOVING BACKWARD LEFT. (3cm - 6cm)".


    delay(5);                               // Delay any actions for 5 milliseconds.

  }*/
}
