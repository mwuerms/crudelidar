const uint8_t step_pin0 = 2;
const uint8_t step_pin1 = 3;
const uint8_t dir_pin0 = 5;
const uint8_t dir_pin1 = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(step_pin0, OUTPUT);
  digitalWrite(step_pin0, LOW);
  pinMode(dir_pin0, OUTPUT);
  digitalWrite(dir_pin0, LOW);
  pinMode(step_pin1, OUTPUT);
  digitalWrite(step_pin1, LOW);
  pinMode(dir_pin1, OUTPUT);
  digitalWrite(dir_pin1, LOW);
}
uint8_t c = 100;
uint8_t d = 0;
void loop() {
  
  if(c) {
    c--;
    if(c == 0) {
      // expired
      c = 100;
      if(d) {
        d = 0;
        digitalWrite(dir_pin0, LOW);
        digitalWrite(dir_pin1, LOW);
      }
      else {
        d = 1;
        digitalWrite(dir_pin0, HIGH);
        digitalWrite(dir_pin1, HIGH);
      }
    }
  }
  digitalWrite(step_pin0, LOW);
  digitalWrite(step_pin1, LOW);
  delay(10);
  digitalWrite(step_pin0, HIGH);
  digitalWrite(step_pin1, HIGH);
  delay(10);
}
