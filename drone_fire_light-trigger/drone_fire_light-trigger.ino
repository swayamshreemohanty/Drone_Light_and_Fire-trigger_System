//Fire configuration
#define fire_pulse_in_pin 5
#define fire_out_pin 8

const int fire_threshold = 1800;


//Fire Timer
// Variable to store the starting time
unsigned long fire_waiting_startTime;

// Duration to wait in seconds
const int fire_waitTime = 6;

bool isFireButtonTrigger = false;
bool isFireComplete = false;

//Light configuration
#define light_pulse_in_pin 6
#define light_out_pin 9
const int blink_light_threshold = 700;
const int constant_light_threshold = 1000;

void setup() {
  Serial.begin(9600);
  //initialize the pins
  //Input Pins
  pinMode(fire_pulse_in_pin, INPUT);
  pinMode(light_pulse_in_pin, INPUT);

  //Output Pins
  pinMode(fire_out_pin, OUTPUT);
  pinMode(light_out_pin, OUTPUT);
}

void fire_switch_off() {
  digitalWrite(fire_out_pin, LOW);
  isFireButtonTrigger = false;
  isFireComplete = false;
}

void fire() {
  digitalWrite(fire_out_pin, HIGH);
  delay(500);
  digitalWrite(fire_out_pin, LOW);
  isFireComplete = true;
}

void listenToFire() {
  // Serial.print("fire_pulse_in_pin reading: ");
  // Serial.println(pulseIn(fire_pulse_in_pin, HIGH));
  if (pulseIn(fire_pulse_in_pin, HIGH) > fire_threshold) {
    if (!isFireButtonTrigger) {
      //update the start time with current millis, when the pulse In crossed the threshold.
      fire_waiting_startTime = millis();
      isFireButtonTrigger = true;
    }
    if (!isFireComplete && millis() >= (fire_waiting_startTime + (fire_waitTime * 1000))) {
      // Serial.println("******Fired***********");
      fire();
      //Reset the timer
      fire_waiting_startTime = millis();
    }
    delay(500);
  } else {
    fire_switch_off();
  }
}


void blinkLight() {
  digitalWrite(light_out_pin, HIGH);
  delay(200);
  digitalWrite(light_out_pin, LOW);
}

void constantLight() {
  digitalWrite(light_out_pin, HIGH);
}

void lightOff() {
  digitalWrite(light_out_pin, LOW);
}

void listenToLight() {
  // Serial.print("light_pulse_in_pin reading: ");
  // Serial.println(pulseIn(fire_pulse_in_pin, HIGH));

  unsigned long light_pulse_in = pulseIn(light_pulse_in_pin, HIGH);
  if (light_pulse_in > blink_light_threshold && light_pulse_in < constant_light_threshold) {
    //Blink light
    blinkLight();
  } else if (light_pulse_in > constant_light_threshold) {
    //Constant light
    constantLight();
  } else {
    //Light off
    lightOff();
  }
}


void loop() {
  listenToFire();
  listenToLight();
}
