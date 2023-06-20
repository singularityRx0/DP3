#include "Arduino.h"
#include <ESP32Servo.h>

//#include <LiquidCrystal_I2C.h>

#define SERVO_1_PIN  12
#define SERVO_2_PIN  14
#define SERVO_3_PIN  2
#define LIMIT_SW_PIN 4

#define L_ACTUATOR_PWM_PIN 27
#define L_ACTUATOR_DIR_PIN 26

#define P_WINDOW_PWM_PIN 33
#define P_WINDOW_DIR_PIN 25

#define MOTOR1_PIN 5
#define MOTOR2_PIN 18
#define MOTOR3_PIN 19
#define MOTOR4_PIN 23

#define MOTOR1_STARTING 184
#define MOTOR2_STARTING 188
#define MOTOR3_STARTING 190
#define MOTOR4_STARTING 184

#define RIGHT_KEYENCE_1_PIN 35
#define RIGHT_KEYENCE_2_PIN 34

#define SPEED_CHG_PER_YAW 1

#define DEFAULT_FLIPSKY_RPM 10500
#define FLIPSKY_HIGHEST_RPM 24500
#define FLIPSKY_LOWEST_RPM 3500

// #define Pole_Distance 100 //in cm

#define MAX_YAW_TOLERANCE 1
#define MAX_PITCH_TOLERANCE 0.5
#define MAX_LIDAR_TOLERANCE 20


VescUart vesc1;

//int lcdColumns = 16;
//int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
//LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

int motor1_pwm_channel     = 3;
int motor2_pwm_channel     = 4;
int motor3_pwm_channel     = 5;
int motor4_pwm_channel     = 6;
int l_actuator_pwm_channel = 7;
int p_window_pwm_channel   = 10;

int frequency_actuator     = 500;
int resolution_actuator = 8;

int frequency_dji = 500;
int resolution_dji = 8; //max is 255 bits

char input;

int angle_count = 0;
int angle_count2 = 0;



Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup() {
  Serial.begin(115200); // initialize serial communication

  myservo1.attach(SERVO_1_PIN); // attach the servo signal pin to GPIO 12
  myservo2.attach(SERVO_2_PIN); // attach the servo signal pin to GPIO 14
  myservo3.attach(SERVO_3_PIN); // attach the servo signal pin to GPIO 4
}

void loop() {
  while (Serial.available() == 0) {
    // wait for user input
  }
  input = Serial.read(); // read user input

  if(input == 'c') //+ is open
  {
    angle_count+= 5;
    myservo3.write(90 + angle_count);
    Serial.println("Angle now_c: ");
    Serial.println(angle_count);
    //ledcWrite(motor_pwm_channel,pulse);
    //Serial.print("Middle pulse");
  
  }
  if(input == 'z'){
    myservo3.write(180);
    // angle_count += 5;
    // myservo3.write(90-angle_count2);
    // Serial.println("Angle now_z: ");
    // Serial.println(angle_count);
  }
  

  if(input == 'u')  
  {

    //myservo3.write(270);
    angle_count += 5;
   // myservo1.write(angle_count);
    // for(int i = 0; i<4 ; i++)
    // {
    //   pulse_M[i]+=1;
    //   ledcWrite(i,pulse_M[i]);
    // }
   // Serial.println("Angle now_u: ");
   myservo3.write(angle_count);
   Serial.print("Angle Now: ");
    Serial.println(angle_count);
  }

  if(input == 'd')
  {
    angle_count -= 5;

    myservo3.write(angle_count);
    // for(int i = 0; i<4 ; i++)
    // {
    //   pulse_M[i] -= 1;
    //   ledcWrite(i,pulse_M[i]);
    // }
    Serial.println("Angle now: ");
    Serial.println(angle_count);
  }

// if(input == a){



// }



}
