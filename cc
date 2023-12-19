int dataPin = 11;
int clockPin = 13;
int latchPin = 10;

unsigned char PWMB = 0;
unsigned char counter = 0;

unsigned char _mode = 0;
unsigned char counter1 = 0;

#define Mode PD6
#define PWM PD5

ISR(PCINT2_vect) {
  if (!(PIND & (1 << Mode))) {
    _mode |= (1 << counter1);
    counter1++;
    if (counter1 > 7) {_mode = 1; counter1 = 0;}
    Serial.println(counter1);
  }
  else if (!(PIND & (1 << PWM))) {
    PWMB |= (1 << counter);
    counter++;
    
    if (counter > 8) { PWMB = 0; counter = 0; }
    
    Serial.println(PWMB);
    analogWrite(3, PWMB);
  }
}

void setup() {
    Serial.begin(9600);
  
    SREG |= (1 << 7);
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, LOW);
}

void loop() {
      if (_mode & (1 << 7)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b00110011);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
        
      if (_mode & (1 << 6)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b11001100);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
        
      if (_mode & (1 << 5)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b01010101);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
        
      if (_mode & (1 << 4)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b10101010);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
        
      if (_mode & (1 << 3)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b10011001);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
        
      if (_mode & (1 << 2)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b10000001);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
        
      if (_mode & (1 << 1)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b00000001);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
      
      if (_mode & (1 << 0)) {
        digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, 0b10000000);
      digitalWrite(latchPin, HIGH);
        delay(1000);
      }
}
