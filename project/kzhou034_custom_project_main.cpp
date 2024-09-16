#include "kzhou034_LCD.cpp"
#include "kzhou034_servo_motor.cpp"
#include "kzhou034_ultrasonic sensor.cpp"

//ultrasonic sensor
#define trigPin 3
#define echoPin 2
int reading=0; //reading=lastpulsetime/58

//servo motor
#define motor1pin 9
#define motor2pin 10
int degree1 = 67;
int degree2 = 67;
bool motor1 = false;
bool moved1 = false;
bool motor2 = false;
bool moved2 = false;

int period = 500;
unsigned long time_now_micros = 0;
unsigned long time_now_millis = 0;

volatile unsigned long LastPulseTime;
int duration;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 4;
task tasks[tasksNum];

//ULTRASONIC SENSOR (echo 2, trig 13)
enum sensor{init_sensor};
int sensor_Tick(int state_sensor) {
  switch(state_sensor) {//state transition
    case init_sensor:
      Pulse();
      reading = LastPulseTime/58;
      //checking for alt motor (motor1)
      if (reading <= 15){
        Serial.println("LESS THAN 15 CM!");
        motor1=true;
        moved1=false;
      }
      else {
        motor1=false;
      }

      //checking for tab motor (motor2)
      if (reading <= 5){
        Serial.println("LESS THAN 5 CM!");
        motor2=true;
        moved2=false;
      }
      else {
        motor2=false;
      }

      state_sensor = init_sensor; //loop here forever

      break;
  }//state transition

  switch(state_sensor) {//state action
    case init_sensor:
      Serial.print((LastPulseTime/58),1);
      Serial.println(" cm");
      break;
  }//state action
  return state_sensor;
}

//SERVO MOTOR 1 (ALT) (pin 9)
enum motor1{init_motor1, moving1};
int motor1_Tick(int state_motor1) {
  switch(state_motor1) {//state transition
    case init_motor1:
      if (motor1==false) {
        state_motor1 = init_motor1;
      }
      else {
        state_motor1 = moving1;
      }
      break;
    case moving1:
      motor1=false;
      moved1=true;
      for (int i = 15; i < degree1; i++) { //move 
          if (moved2==false) {
            turn(i, motor1pin);
          }
          else {
            state_motor1 = init_motor1;
          }
      }
      delay(10);
      for (int i = degree1; i > 15; i--) { //move back
        if (moved2==false) {
            turn(i, motor1pin);
        }
        else {
            state_motor1 = init_motor1;
        }       
      }
      delay(10);

      state_motor1 = init_motor1;

      break;
  }//state transition

  switch(state_motor1) {//state action
    case init_motor1:
      degree1 = 0;
      break;
    case moving1:
      degree1 = 67;
      break;
  }//state action
  return state_motor1;
}

//SERVO MOTOR 2 (TAB) (pin 10)
enum motor2{init_motor2, moving2};
int motor2_Tick(int state_motor2) {
  switch(state_motor2) {//state transition
    case init_motor2:
      if (motor2==false) {
        state_motor2 = init_motor2;
      }
      else {
        state_motor2 = moving2;
      }
      break;
    case moving2:
      motor2=false;
      moved2=true;
      for (int i = 15; i < degree2; i++) { //move 
          turnBoth(i);
      }
      //delay(10);
      for (int i = degree2; i > 15; i--) { //move back
        turnBoth(i);             
      }
      //delay(10);

      state_motor2 = init_motor2;

      break;
  }//state transition

  switch(state_motor2) {//state action
    case init_sensor:
      degree2 = 0;
      break;
    case moving2:
      degree2 = 67;
      break;
  }//state action
  return state_motor2;
}

//NOKIA LCD 5110
enum lcd{output, over15, lessthan5, lessthan15};
int lcd_Tick(int state_lcd) {
  switch(state_lcd) {//state transition
    case output:
      //clearScreen();
      if(reading>15) {
        state_lcd = over15;
      }
      if(reading <=15) {
        state_lcd = lessthan15;
      }
      if(reading<=5) {
        state_lcd = lessthan5;
      }
      break;
    case over15:
      if(reading>15) {
        state_lcd = over15;
      }
      else {
        state_lcd = output;
      }
      break;
    case lessthan15:
      if(reading <=15) {
        state_lcd = lessthan15;
      }
      else if (reading <=5) {
        state_lcd = lessthan5;
      }
      else {
        state_lcd = output;
      }
      break;
    case lessthan5:
      if(reading<=5) {
        state_lcd = lessthan5;
      } 
      else {
        state_lcd = output;
      }
      break;
    
  }//state transition

  switch(state_lcd) {//state action
    case output:
      break;
    case over15: 
      over15Display();
      break;
    case lessthan15: 
      lessthan15Display();
      break;
    case lessthan5: 
      lessthan5Display();
      break;
  }//state action
}



void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  attachInterrupt(0, EchoPinISR, CHANGE);  // Pin 3 interrupt on any change

  lcd_begin();
  
  unsigned char i = 0;
    tasks[i].state = init_sensor; //sensor task 1
    tasks[i].period = 50;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &sensor_Tick;
    i++;
    tasks[i].state = init_motor1; //servo motor 1 task 2
    tasks[i].period = 50;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &motor1_Tick;
    i++;
    tasks[i].state = init_motor2; //servo motor 2 task 3
    tasks[i].period = 50;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &motor2_Tick;
    i++;
    tasks[i].state = output; //LCD task 4 
    tasks[i].period = 50;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &lcd_Tick;


    delay_gcd = 1000; // GCD
  
  Serial.begin(9600);
}

void loop() {
  time_now_micros = micros();
  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}