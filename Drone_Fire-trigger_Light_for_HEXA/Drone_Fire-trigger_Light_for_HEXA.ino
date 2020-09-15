int pwm_pin = 9;
int pwm_recv;
int state = 0;
int fire = 10;
int i = 0;
//int leds[6] = {7, 2, 3, 4, 5, 6};
int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int LED5 = 6;
int LED6 = 7;
int fireCond = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pwm_pin, INPUT);
  pinMode(fire, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  delay(1500);
  digitalWrite(LED6, HIGH);
  delay(500);
  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED2, HIGH);    // turn the LED off by making the voltage LOW
  delay(500);                 // wait for a second
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED4, HIGH);
  delay(500);
  digitalWrite(LED5, HIGH);
  delay(500);
  digitalWrite(LED6, LOW);
  delay(500);
  digitalWrite(LED1, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                 // wait for a second
  digitalWrite(LED3, LOW);
  delay(500);
  digitalWrite(LED4, LOW);
  delay(500);
  digitalWrite(LED5, LOW);
  delay(500);
}

void dronemode1() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(fire, LOW);
}
void dronemode3() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
}

void dronemode2() {
  digitalWrite(fire, HIGH);
  delay(2000);
  fireCond = 1;
}
void loop() {
  Serial.print("pulse");
  Serial.println(pwm_recv);
  delay(100);
  pwm_recv = pulseIn(pwm_pin, HIGH);

  if (pwm_recv > 1100 && pwm_recv < 1200) {
    dronemode1();
    fireCond = 0;
    Serial.print("In Middle");
  }
   else if (pwm_recv >= 1300 && pwm_recv < 1650) {
      dronemode3();
      //(fireCond == 0)
    }
  else if (pwm_recv >= 1700 && pwm_recv < 2000) {
    if (fireCond == 0) {
      dronemode2();
    }
    else {
      dronemode1();
    }
  }
  else {
    digitalWrite(fire, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(fire, LOW);
  }
}
