// Digit control input
byte D1 = 2;
byte D2 = 3;
byte D3 = 4;
byte D4 = 5;

// Segment control input
byte A = 6;
byte B = 7;
byte C = 8;
byte D = 9;
byte E = 10;
byte F = 11;
byte G = 12;
byte DP = 13; // decimal point

// Define the input pins for the 7-segment display segments.
const int segmentPins[] = {A, B, C, D, E, F, G, DP};

// Define the input pins for the 7-segment display digits.
const int digitPins[] = {D1, D2, D3, D4};

// For common cathode
uint8_t digitON = HIGH;
uint8_t digitOFF = LOW;

uint8_t segmentON = LOW;
uint8_t segmentOFF = HIGH;

void setup() {
    // Pin segments initialization.
   for (int i = 0; i < 8; i++) {
      pinMode(segmentPins[i], OUTPUT);
   }
   // Pin digits initialization
   for (int i = 0; i < 4; i++) {
      pinMode(digitPins[i], OUTPUT);
      digitalWrite(digitPins[i], digitOFF);
   }
}

void loop() {
  One(D1);

  Two(D2);

  Three(D3);

  Four(D4);

  Five(D1);

  Six(D2);

  Seven(D3);

  Eight(D4);

  Nine(D1);

  loop();
}

// Method turning on all digit fields
void AllDigitsDown() {
 for (int i = 0; i < 4; i++) {
      digitalWrite(digitPins[i], digitOFF);
  }
}
// Method turning off all digit fields
void AllDigitsUp() {
 for (int i = 0; i < 4; i++) {
      digitalWrite(digitPins[i], digitON);
  }
}

// Method turning off all segments on given field digit fields
void AllSegmentsDown() {
 for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], segmentOFF);
  }
}

// Method turning on all segments on given field digit fields
void AllSegmentsUp() {
 for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], segmentOFF);
  }
  delay(1000);
}

// Number One showed on given pin with 1 second display delay
void One(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentOFF);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Two showed on given pin with 1 second display delay
void Two(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentOFF);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Three showed on given pin with 1 second display delay
void Three(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Four showed on given pin with 1 second display delay
void Four(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentOFF);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Five showed on given pin with 1 second display delay
void Five(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Six showed on given pin with 1 second display delay
void Six(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Seven showed on given pin with 1 second display delay
void Seven(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Eight showed on given pin with 1 second display delay
void Eight(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}

// Number Nine showed on given pin with 1 second display delay
void Nine(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1000);

  AllSegmentsDown();
  AllDigitsDown();
}