// C++ code
// Pin definitions
int pirPin = 2;      // PIR motion sensor output
int ledPin = 3;      // LED to show armed status
int buzzerPin = 4;   // Buzzer for alarm
int buttonPin = 5;   // Push button to arm/disarm

// State variables
bool armed = false;          // Tracks if system is armed
bool lastButtonState = LOW;  // Tracks previous button state for toggle


void setup() {
  pinMode(pirPin, INPUT);          // PIR sensor is input
  pinMode(ledPin, OUTPUT);         // LED is output
  pinMode(buzzerPin, OUTPUT);      // Buzzer is output
  pinMode(buttonPin, INPUT_PULLUP);// Button input with internal pull-up resistor,When you set a pin as INPUT_PULLUP, Arduino connects this internal resistor from the pin to 5V.
  //when the buttonPin is not pressed it has 5V - HIGH

  // Start with LED and buzzer off
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // Read button state (active LOW)
  bool buttonState = !digitalRead(buttonPin);//flips it so buttonState = true when button is pressed
  // buttonState = false :0: !1: !True :[Not pressed (High : true)]

  // Detect button press (toggle)
  if (buttonState && !lastButtonState) {
    armed = !armed;                       // Change armed state as true
    // Turn LED ON or OFF
    if (armed) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    delay(200);                            // Debounce delay
  }

  lastButtonState = buttonState;           // Save state for next loop

    // If system is armed and PIR detects motion
  if (armed && digitalRead(pirPin) == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Turn buzzer ON
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn buzzer OFF
  }
}

