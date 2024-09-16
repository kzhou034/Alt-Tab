#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

void turn(int x, int pin){
  digitalWrite(motor1pin,HIGH);
  delayMicroseconds((x*10)+500);
  digitalWrite(motor1pin,LOW);
  delay(1);
}

void turnBoth(int x){
  digitalWrite(motor1pin,HIGH);
   if (moved2==true) { 
    digitalWrite(motor2pin,HIGH);
   }
  delayMicroseconds((x*10)+500);
  digitalWrite(motor1pin,LOW);
  if (moved2==true) {
    digitalWrite(motor2pin,LOW);
  }
  delay(1);
};

#endif