#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(11520); //Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  
  toggle = 0;
  digitalWrite(PIN_LED, 0);
  delay(1000);

  int i;
  for(i=1; i<=10; i++) {
    toggle = i % 2;
    digitalWrite(PIN_LED, toggle);
    delay(100);
  }
}

void loop() {
  while (1) {
  digitalWrite(PIN_LED, 1); //update LED status.
  }
}
