#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float calibration_value = 21.34 - 0.7;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;

float ph_act;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Initialize the analog input pin for pH sensor
  pinMode(A0, INPUT);

  // Set up the OLED display
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("pH:");

  // Start the timer for periodic pH readings
  unsigned long previousMillis = 0;
  const unsigned long interval = 1000; // Interval in milliseconds (1 second)

  while (!Serial) {
    ; // Wait for serial port to connect (for debugging)
  }
}

void loop() {
  // Check if it's time to take a pH reading
  static unsigned long previousMillis = 0;
  const unsigned long interval = 1000; // Interval in milliseconds (1 second)

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read pH sensor
    for (int i = 0; i < 10; i++) {
      buffer_arr[i] = analogRead(A0);
      delay(30);
    }

    // Sort the readings in ascending order
    for (int i = 0; i < 9; i++) {
      for (int j = i + 1; j < 10; j++) {
        if (buffer_arr[i] > buffer_arr[j]) {
          temp = buffer_arr[i];
          buffer_arr[i] = buffer_arr[j];
          buffer_arr[j] = temp;
        }
      }
    }

    // Calculate the average value of the middle 6 readings
    avgval = 0;
    for (int i = 2; i < 8; i++)
      avgval += buffer_arr[i];
    float volt = (float)avgval * 5.0 / 1024 / 6;
    ph_act = -5.70 * volt + calibration_value;

    // Print pH value to the serial monitor
    Serial.print("pH Val: ");
    Serial.println(ph_act);

    // Update OLED display with pH value
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("pH:");
    display.setCursor(55, 0);
    display.print(ph_act);
    display.display();
  }
}
