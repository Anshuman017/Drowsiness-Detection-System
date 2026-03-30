#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create an LCD object with the I2C address 0x27 (this may vary depending on your LCD model)
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16 columns and 2 rows LCD

const int buzzer_Pin = 8;  // Pin connected to the buzzer
const int led_Pin = 9;     // Pin connected to the LED
char sleep_status = 0;     // Variable to store sleep status

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  pinMode(buzzer_Pin, OUTPUT);  // Set the buzzer pin as output
  pinMode(led_Pin, OUTPUT);     // Set the LED pin as output
  lcd.begin(16, 2);             // Initialize the LCD screen with 16 columns and 2 rows
  lcd.backlight();              // Turn on the backlight for the LCD
  lcd.print("Driver Sleep ");   // Display "Driver Sleep"
  lcd.setCursor(0, 1);         // Move the cursor to the second row (index 1)
  lcd.print("Detection SYSTEM"); // Display "Detection SYSTEM"
  digitalWrite(buzzer_Pin, LOW);  // Ensure the buzzer is off
  digitalWrite(led_Pin, LOW);     // Ensure the LED is off
}

void loop() {
  // Check if data is available in the Serial Monitor
  if (Serial.available() > 0) {
    sleep_status = Serial.read();  // Read the incoming byte

    if (sleep_status == 'a') {  // If the incoming byte is 'a', driver is asleep
      lcd.clear();  // Clear the LCD
      lcd.print("Please wake up");  // Display message to wake up the driver
      digitalWrite(buzzer_Pin, HIGH);  // Turn on the buzzer
      digitalWrite(led_Pin, HIGH);     // Turn on the LED
      delay(2000);  // Wait for 2 seconds
      digitalWrite(buzzer_Pin, LOW);   // Turn off the buzzer
      digitalWrite(led_Pin, LOW);      // Turn off the LED
      delay(100);  // Small delay before checking again
    }
    else if (sleep_status == 'b') {  // If the incoming byte is 'b', driver is awake
      lcd.clear();  // Clear the LCD
      lcd.print("All Ok");  // Display message that everything is fine
      lcd.setCursor(0, 1);  // Move the cursor to the second row
      lcd.print("Drive Safe");  // Display "Drive Safe"
      digitalWrite(buzzer_Pin, LOW);  // Ensure the buzzer is off
      digitalWrite(led_Pin, LOW);     // Ensure the LED is off
      delay(2000);  // Wait for 2 seconds
    }
    else {
      // If any other data is received, do nothing
    }
  }
}
