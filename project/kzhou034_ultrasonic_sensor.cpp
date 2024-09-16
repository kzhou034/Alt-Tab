#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__

void EchoPinISR() {
  static unsigned long startTime;
  if (digitalRead(echoPin)){ // Gone HIGH
    startTime = micros();
  }
  else { // Gone LOW
    LastPulseTime = micros() - startTime;
  }
};

void Pulse() {
  //time_now = micros();
  digitalWrite(trigPin, LOW); 
  if(micros() - time_now_micros > period){
        //digitalWrite(trigPin, LOW); 
        time_now_micros += period;
    }
  digitalWrite(trigPin, HIGH);
  if(micros() - time_now_micros > (2*period)){
        //digitalWrite(trigPin, HIGH);
        time_now_micros += (2*period);
    }
  digitalWrite(trigPin, LOW);
};

#endif