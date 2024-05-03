/**
 * @file
 * @brief Arduino sketch for controlling a 7-segment LED display to show time.
 * 
 * This sketch controls a 7-segment display to show time in "HH:MM" format.
 * It displays the current time on the display.
 * 
 * @author Ondřej Faltin
 * @date 2.5.2024
 */

// Declarations

  /**
  * @brief Pin declarations for digit control inputs.
  */
  byte D1 = 2;
  byte D2 = 3;
  byte D3 = 4;
  byte D4 = 5;

  /**
  * @brief Pin declarations for segment control inputs.
  */
  byte A = 6;
  byte B = 7;
  byte C = 8;
  byte D = 9;
  byte E = 10;
  byte F = 11;
  byte G = 12;
  byte DP = 13; // decimal point

  /**
  * @brief Arrays defining input pins for the 7-segment display segments and digits.
  */
  const int segmentPins[] = {A, B, C, D, E, F, G, DP};
  const int digitPins[] = {D1, D2, D3, D4};

  /**
  * @brief Constants for controlling common cathode behavior.
  */
  uint8_t digitON = HIGH;
  uint8_t digitOFF = LOW;
  uint8_t segmentON = LOW;
  uint8_t segmentOFF = HIGH;


  /**
  * @brief Time input in "HH:MM" format.
  */
  String time = "23:58";

  /**
  * @brief Variables for storing hours and minutes.
  */
  int hours = 0;
  int minutes = 0;

  /**
  * @brief Variables used for managing time intervals.
  */
  unsigned long previousMillis = 0;  // Stores last time the LED was updated
  const long interval = 60000;       // 60 sec / 1 minute interval constant


// Default Methods

  /**
  * @brief Initialization function for setting up pins and serial communication.
  */
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

  /**
  * @brief Main loop for the Arduino sketch.
  * 
  * This function continuously updates the time display and checks for
  * changes every 60 seconds.
  */
  void loop() {
    ConvertString(time);

    // Gets the current time (milliseconds)
    unsigned long currentMillis = millis();  

    // Condition measuring the 60 seconds to change the clock
    if (currentMillis - previousMillis >= interval) {
      // Save the last time the LED was updated
      previousMillis = currentMillis;

      // Counts the Time every 60 seconds
      CurrentTimeCounter();
    }

    // Prints the current time in the serial monitor  
    Serial.println(FormatTime(hours, minutes));
  }


// Other Methods (Created)

  /**
  * @brief Convert the time string to numbers for hour and minute.
  * 
  * @param input The time string in "HH:MM" format.
  */
  void ConvertString(String input) {
    if (CheckInput(input)) {
      //CurrentTimeCounter();
      String currentTime = FormatTime(hours, minutes);
      
      Convertion(currentTime);
    } else {
        Error();
    }
  }

  /**
  * @brief Convert the time string to individual digit characters.
  * 
  * @param input The time string in "HH:MM" format.
  */
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

  /**
  * @brief Print the time input to the serial monitor.
  * 
  * @param input The time string in "HH:MM" format.
  */
  void PrintInput(String input) {
    // Array with individual characters from string input declaration
    char numArray[6]; 
      
    // Convert the String to a character array
    input.toCharArray(numArray, 6);

    for (int i = 0; i < input.length(); i++) {
      Serial.print(numArray[i]);
    }
  }

  /**
  * @brief Check the format of the given time input.
  * 
  * @param input The time string to check.
  * @return True if the format is correct, otherwise false.
  */
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

  /**
  * @brief Display an individual digit on the 7-segment display.
  * 
  * @param digit The digit to display.
  * @param position The position of the digit on the display.
  */
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

  /**
  * @brief Increment hours and minutes, adjusting as necessary.
  */
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

  /**
  * @brief Format the time as a string in "HH:MM" format.
  * 
  * @param hour The hour value.
  * @param minute The minute value.
  * @return The formatted time string.
  */
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


  /**
  * @brief Turn off all digit control inputs.
  */
  void AllDigitsDown() {
  for (int i = 0; i < 4; i++) {
        digitalWrite(digitPins[i], digitOFF);
    }
  }

  /**
  * @brief Turn on all digit control inputs.
  */
  void AllDigitsUp() {
  for (int i = 0; i < 4; i++) {
        digitalWrite(digitPins[i], digitON);
    }
  }

  /**
  * @brief Turn off all segment control inputs.
  */
  void AllSegmentsDown() {
  for (int i = 0; i < 8; i++) {
        digitalWrite(segmentPins[i], segmentOFF);
    }
  }

  /**
  * @brief Turn on all segment control inputs.
  */
  void AllSegmentsUp() {
  for (int i = 0; i < 8; i++) {
        digitalWrite(segmentPins[i], segmentOFF);
    }
    delay(1000);
  }

  /**
  * @brief Display the number zero on the 7-segment display.
  */
  void Zero() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentON);
    digitalWrite(E, segmentON);
    digitalWrite(F, segmentON);
    digitalWrite(G, segmentOFF);
    digitalWrite(DP, segmentOFF);
  }


  /**
  * @brief Display the number one on the 7-segment display.
  */ 
  void One() {
    digitalWrite(A, segmentOFF);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentOFF);
    digitalWrite(E, segmentOFF);
    digitalWrite(F, segmentOFF);
    digitalWrite(G, segmentOFF);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number two on the 7-segment display.
  */
  void Two() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentOFF);  
    digitalWrite(D, segmentON);
    digitalWrite(E, segmentON);
    digitalWrite(F, segmentOFF);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number three on the 7-segment display.
  */
  void Three() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentON);
    digitalWrite(E, segmentOFF);
    digitalWrite(F, segmentOFF);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number four on the 7-segment display.
  */
  void Four() {
    digitalWrite(A, segmentOFF);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentOFF);
    digitalWrite(E, segmentOFF);
    digitalWrite(F, segmentON);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number five on the 7-segment display.
  */
  void Five() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentOFF);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentON);
    digitalWrite(E, segmentOFF);
    digitalWrite(F, segmentON);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number six on the 7-segment display.
  */
  void Six() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentOFF);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentON);
    digitalWrite(E, segmentON);
    digitalWrite(F, segmentON);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number seven on the 7-segment display.
  */
  void Seven() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentOFF);
    digitalWrite(E, segmentOFF);
    digitalWrite(F, segmentOFF);
    digitalWrite(G, segmentOFF);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number eight on the 7-segment display.
  */
  void Eight() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentON);
    digitalWrite(E, segmentON);
    digitalWrite(F, segmentON);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display the number nine on the 7-segment display.
  */
  void Nine() {
    digitalWrite(A, segmentON);
    digitalWrite(B, segmentON);
    digitalWrite(C, segmentON);  
    digitalWrite(D, segmentOFF);
    digitalWrite(E, segmentOFF);
    digitalWrite(F, segmentON);
    digitalWrite(G, segmentON);
    digitalWrite(DP, segmentOFF);
  }

  /**
  * @brief Display a dot on the 7-segment display.
  * 
  * @param pin The pin to control the dot.
  */
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

  /**
  * @brief Display the character 'E' on the 7-segment display.
  * 
  * @param pin The pin to control the segments.
  */
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

  /**
  * @brief Display the character 'R' on the 7-segment display.
  * 
  * @param pin The pin to control the segments.
  */
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

  /**
  * @brief Display the error message '.ERR' on the 7-segment display.
  */
  void Error() {
    Dot(D1);     // Display "."
    E_char(D2);  // Display "E"
    R_char(D3);  // Display "R"
    R_char(D4);  // Display "R"
  }