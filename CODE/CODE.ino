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
  String time = "23:58";
  // Declaration of time variables
  int hours = 0;
  int minutes = 0;

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

  // Declare hours and minutes
  hours = (time.substring(0, 2)).toInt();
  minutes = (time.substring(3)).toInt();

  PrintInput(time);
}

void loop() {
  // Trying to convert the string time to individual ints
  ConvertString(time);

  Serial.println(FormatTime(hours, minutes));
}

// Method converting string to the numbers to view the time on the led display
void ConvertString(String input) {
  if (CheckInput(input)) {
    CurrentTimeCounter();
    String currentTime = FormatTime(hours, minutes);
    
    Convertion(currentTime);
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
  int hours2 = (input.substring(0, 2)).toInt();
  int minutes2 = (input.substring(3)).toInt();
  if (hours2 < 0 || hours2 > 23 || minutes2 < 0 || minutes2 > 59)
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
      Zero();
      break;
    case '1':
      One();
      break;
    case '2':
      Two();
      break;
    case '3':
      Three();
      break;
    case '4':
      Four();
      break;
    case '5':
      Five();
      break;
    case '6':
      Six();
      break;
    case '7':
      Seven();
      break;
    case '8':
      Eight();
      break;
    case '9':
      Nine();
      break;
    default:
      // Display nothing or an error indicator
      break;
  }
}

// Method working with the int variables to work with the time properly
void CurrentTimeCounter() {
  minutes++;
  if (minutes == 60) {
    minutes = 0;
    hours++;
    if (hours == 24) {
      hours = 0;
    }
  }
}

// Method to format time as string (HH:MM)
String FormatTime(int hour, int minute) {
  String formattedTime = "";

  if (hour < 10) {
    formattedTime += "0"; 
  }
  formattedTime += String(hour) + ":";

  if (minute < 10) {
    formattedTime += "0";
  }
  formattedTime += String(minute);

  return formattedTime;
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

// Number Zero 
void Zero() {
  //digitalWrite(pin, digitON);

  digitalWrite(A, segmentON);
  digitalWrite(B, segmentON);
  digitalWrite(C, segmentON);  
  digitalWrite(D, segmentON);
  digitalWrite(E, segmentON);
  digitalWrite(F, segmentON);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentOFF);

  /*delay(1);

  AllSegmentsDown();
  AllDigitsDown();*/
}


// Number One 
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

// Number Two 
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

// Number Three 
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

// Number Four 
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

// Number Five 
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

// Number Six 
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

// Number Seven 
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

// Number Eight 
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

// Number Nine 
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

// Dot 
void Dot(uint8_t pin) {
  digitalWrite(pin, digitON);

  digitalWrite(A, segmentOFF);
  digitalWrite(B, segmentOFF);
  digitalWrite(C, segmentOFF);  
  digitalWrite(D, segmentOFF);
  digitalWrite(E, segmentOFF);
  digitalWrite(F, segmentOFF);
  digitalWrite(G, segmentOFF);
  digitalWrite(DP, segmentON);
  
  delay(1);

  AllSegmentsDown();
  AllDigitsDown();
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