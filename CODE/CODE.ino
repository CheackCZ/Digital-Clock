  // Declarations
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

  // Time input
  String time = "10:52";


// Default Methods
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

  // Initialize serial communication
  Serial.begin(9600);

  PrintInput(time);
}

void loop() {
  // Trying to convert the string time to individual ints
  ConvertString(time);
}


// Method converting string to the numbers to view the time on the led display
void ConvertString(String input) {
  if (CheckInput(input)) {
    Convertion(input);
  } else {
      Error();
  }
}

// Method with the Actual Conversion
void Convertion(String input) {
  // Array with individual characters from string input declaration
  char numArray[6]; 
    
  // Convert the String to a character array
  input.toCharArray(numArray, 6);
  
  // Display each digit on the LED display
  for (int i = 0; i < input.length(); i++) {
    if (isdigit(numArray[i])) {
      if (i > 2) {
        DisplayDigit(numArray[i], i-1);
      } else {
        DisplayDigit(numArray[i], i);
      }
    } 
    delay(1); 
  }

  // Turn off all digits after displaying
  AllDigitsDown();
}

// Method printing the string input
void PrintInput(String input) {
   // Array with individual characters from string input declaration
  char numArray[6]; 
    
  // Convert the String to a character array
  input.toCharArray(numArray, 6);

  for (int i = 0; i < input.length(); i++) {
    Serial.print(numArray[i]);
  }
}

// Method checking the format of given input
bool CheckInput(const String& input) {
    if (input.length() != 5) // Input must be in format "HH:MM"
        return false;

    for (int i = 0; i < 5; i++) {
        if (i == 2 && input[i] != ':') // Check for colon at position 2
            return false;
        else if (i != 2 && !isdigit(input[i])) // Check for digits elsewhere
            return false;
    }

    // Check hours and minutes ranges
    int hours = (input.substring(0, 2)).toInt();
    int minutes = (input.substring(3)).toInt();
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
        return false;

    return true;
}

// Method displaying individual digits on individual displays
void DisplayDigit(uint8_t digit, uint8_t position) {
  // Turn off all digits
  AllDigitsDown();
  // Turn off all segments
  AllSegmentsDown();

  // Activate the desired digit
  digitalWrite(digitPins[position], digitON);

  // Activate segments based on the digit to display
  switch (digit) {
    case '0':
      digitalWrite(A, segmentON);
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(D, segmentON);
      digitalWrite(E, segmentON);
      digitalWrite(F, segmentON);
      break;
    case '1':
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      break;
    case '2':
      digitalWrite(A, segmentON);
      digitalWrite(B, segmentON);
      digitalWrite(G, segmentON);
      digitalWrite(E, segmentON);
      digitalWrite(D, segmentON);
      break;
    case '3':
      digitalWrite(A, segmentON);
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(D, segmentON);
      digitalWrite(G, segmentON);
      break;
    case '4':
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(F, segmentON);
      digitalWrite(G, segmentON);
      break;
    case '5':
      digitalWrite(A, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(D, segmentON);
      digitalWrite(F, segmentON);
      digitalWrite(G, segmentON);
      break;
    case '6':
      digitalWrite(A, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(D, segmentON);
      digitalWrite(E, segmentON);
      digitalWrite(F, segmentON);
      digitalWrite(G, segmentON);
      break;
    case '7':
      digitalWrite(A, segmentON);
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      break;
    case '8':
      digitalWrite(A, segmentON);
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(D, segmentON);
      digitalWrite(E, segmentON);
      digitalWrite(F, segmentON);
      digitalWrite(G, segmentON);
      break;
    case '9':
      digitalWrite(A, segmentON);
      digitalWrite(B, segmentON);
      digitalWrite(C, segmentON);
      digitalWrite(D, segmentON);
      digitalWrite(F, segmentON);
      digitalWrite(G, segmentON);
      break;
    default:
      // Display nothing or an error indicator
      break;
  }
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
void One() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentOFF);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Two showed on given pin with 1 second display delay
void Two() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentOFF);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Three showed on given pin with 1 second display delay
void Three() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Four showed on given pin with 1 second display delay
void Four() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentOFF);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Five showed on given pin with 1 second display delay
void Five() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Six showed on given pin with 1 second display delay
void Six() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Seven showed on given pin with 1 second display delay
void Seven() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Eight showed on given pin with 1 second display delay
void Eight() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Nine showed on given pin with 1 second display delay
void Nine() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// Number Nine showed on given pin with 1 second display delay
void Dot() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentOFF);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentOFF);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentON);
  
  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}

// char E showed on given pin
void E_char(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentOFF);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);

  delay(1);

  AllSegmentsDown();
  AllDigitsDown();
}

// char R showed on given pin
void R_char(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentON);
  digitalWrite(DP, segmentOFF);
  
  delay(1);

  AllSegmentsDown();
  AllDigitsDown();
}

// ERR showed on the display to get user to know that something is wrong
void Error() {
  Dot(D1);     // Display "."
  E_char(D2);  // Display "E"
  R_char(D3);  // Display "R"
  R_char(D4);  // Display "R"
}