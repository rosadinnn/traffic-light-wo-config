#define LED_GREEN_A 10
#define LED_RED_A 4
#define LED_GREEN_B 5
#define LED_RED_B 6
#define SENSOR_A 7
#define SENSOR_B 8

unsigned long timerA = 0;
unsigned long timerB = 0;
unsigned long TIMEOUT = 45000;
bool vehicleA = false;
bool vehicleB = false;
bool entryFromA = false;
bool entryFromB = false;
bool lastStateA = LOW;
bool lastStateB = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN_A, OUTPUT);
  pinMode(LED_RED_A, OUTPUT);
  pinMode(LED_GREEN_B, OUTPUT);
  pinMode(LED_RED_B, OUTPUT);
  pinMode(SENSOR_A, INPUT);
  pinMode(SENSOR_B, INPUT);
  standby();
}

void standby() {
  digitalWrite(LED_GREEN_A, LOW);
  digitalWrite(LED_RED_A, HIGH);
  digitalWrite(LED_GREEN_B, LOW);
  digitalWrite(LED_RED_B, HIGH);
}

void loop() {
  //  Serial.print("LED_GREEN_A: ");
  //  Serial.println(digitalRead(LED_GREEN_A));
  //  Serial.print("LED_RED_A: ");
  //  Serial.println(digitalRead(LED_RED_A));
  //  Serial.print("LED_GREEN_B: ");
  //  Serial.println(digitalRead(LED_GREEN_B));
  //  Serial.print("LED_RED_B: ");
  //  Serial.println(digitalRead(LED_RED_B));

  bool sensorA = digitalRead(SENSOR_A);
  bool sensorB = digitalRead(SENSOR_B);

  unsigned long currentMillis = millis();

  if (sensorA && !lastStateA) {
    if (!vehicleA && !entryFromB) {
      vehicleA = true;
      entryFromA = true;
      timerA = currentMillis;
      digitalWrite(LED_GREEN_B, HIGH);
      digitalWrite(LED_RED_B, LOW);
    } else if (vehicleB && entryFromB) {
      vehicleB = false;
      entryFromB = false;
      standby();
    }
  }
  lastStateA = sensorA;

  if (sensorB && !lastStateB) {
    if (!vehicleB && !entryFromA) {
      vehicleB = true;
      entryFromB = true;
      timerB = currentMillis;
      digitalWrite(LED_GREEN_A, HIGH);
      digitalWrite(LED_RED_A, LOW);
    } else if (vehicleA && entryFromA) {
      vehicleA = false;
      entryFromA = false;
      standby();
    }
  }
  lastStateB = sensorB;

  if (vehicleA && (currentMillis - timerA > TIMEOUT)) {
    vehicleA = false;
    entryFromA = false;
    standby();
  }
  if (vehicleB && (currentMillis - timerB > TIMEOUT)) {
    vehicleB = false;
    entryFromB = false;
    standby();
  }

  delay(50);
}
