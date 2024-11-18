#define redpin 11 // RED
#define greenpin 10 // GREEN
#define bluepin 6 // BLUE

void setup()
{
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
}

void loop()
{
  //RED
  analogWrite(redpin, 255);
  analogWrite(greenpin, 0);
  analogWrite(bluepin, 0);
  delay(2000);
  //GREEN
  analogWrite(redpin, 0);
  analogWrite(greenpin, 255);
  analogWrite(bluepin, 0);
  delay(2000);
  //BLUE
  analogWrite(redpin, 0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin, 255);
  delay(2000);
}

 // Read air quality data from MQ-135
    Serial.print("MQ-135 Sensor Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    // SDS011 - Read particulate matter (PM2.5 and PM10)
        Serial.print("PM2.5: ");
        Serial.print(pm25);
        Serial.println(" µg/m3");

        Serial.print("PM10: ");
        Serial.print(pm10);
        Serial.println(" µg/m3");
        Serial.println("Error reading SDS011 sensor");

int mq135Pin = A0;    // Analog pin connected to MQ-135 output


    Serial.begin(9600);      // Begin serial communication
    int sensorValue = analogRead(mq135Pin); // Read the analog value
    Serial.print("MQ-135 Sensor Value: ");
    Serial.println(sensorValue);






#include <Wire.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int mq7Pin = A1;    // MQ-7 for CO



void setup() {
    Serial.begin(9600);

    // Initialize display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    delay(2000);  
    display.clearDisplay();

    // Initialize SDS011 particulate matter sensor

    pinMode(mq135Pin, INPUT);
    pinMode(mq7Pin, INPUT);
}


// The code for displaying the types of air)

    // Read MQ-135 (CO2, NH3, alcohol, benzene, smoke)
    int mq135Value = analogRead(mq135Pin);
    float voltageMQ135 = mq135Value * (5.0 / 1023.0);  // Convert to voltage

    // Read MQ-7 (CO)
    int mq7Value = analogRead(mq7Pin);
    float voltageMQ7 = mq7Value * (5.0 / 1023.0);      // Convert to voltage

    // Read SDS011 for PM2.5 and PM10
    float pm25, pm10;

    // Display results on OLED

    display.setTextSize(1);

    // Display MQ-135 readings
    display.setCursor(0, 0);
    display.print("CO2/NH3 (MQ-135): ");
    display.print(voltageMQ135);
    display.println(" V");

    // Display MQ-7 readings
    display.setCursor(0, 10);
    display.print("CO (MQ-7): ");
    display.print(voltageMQ7);
    display.println(" V");

    // Display PM2.5 and PM10 from SDS011
    if (!error) {
        display.setCursor(0, 20);
        display.print("PM2.5: ");
        display.print(pm25);
        display.println(" ug/m3");

        display.setCursor(0, 30);
        display.print("PM10: ");
        display.print(pm10);
        display.println(" ug/m3");
    } else {
        display.setCursor(0, 20);
        display.println("Error reading SDS011");
    }

    display.display();
    delay(2000);  // Delay for readability
}


// To show if it is dangerouse to live or if it is ok to live)

#include <Wire.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int mq135Pin = A0;  // MQ-135 for CO2 and other gases
const int mq7Pin = A1;    // MQ-7 for CO
SDS011 my_sds;            // SDS011 for PM2.5 and PM10

// Thresholds for safe/dangerous air quality
const float CO2_THRESHOLD = 2.0;      // Approximate voltage for 1000 ppm CO2
const float CO_THRESHOLD = 1.2;       // Approximate voltage for 50 ppm CO
const float PM25_THRESHOLD = 55.0;    // PM2.5 threshold in µg/m³
const float PM10_THRESHOLD = 100.0;   // PM10 threshold in µg/m³

void setup() {
    Serial.begin(9600);

    // Initialize the display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.display();
    delay(2000);
    display.clearDisplay();

    // Initialize SDS011 particulate sensor
    my_sds.begin(10, 11);  // RX, TX for SDS011
    pinMode(mq135Pin, INPUT);
    pinMode(mq7Pin, INPUT);
}

void loop() {
    // Read MQ-135 (CO2, NH3, alcohol, benzene, smoke)
    int mq135Value = analogRead(mq135Pin);
    float voltageMQ135 = mq135Value * (5.0 / 1023.0);

    // Read MQ-7 (CO)
    int mq7Value = analogRead(mq7Pin);
    float voltageMQ7 = mq7Value * (5.0 / 1023.0);

    // Read SDS011 for PM2.5 and PM10
    float pm25, pm10;
    int error = my_sds.read(&pm25, &pm10);

    // Determine if air quality is OK or DANGEROUS
    bool airSafe = true;

    if (voltageMQ135 > CO2_THRESHOLD) {
        airSafe = false;
    }
    if (voltageMQ7 > CO_THRESHOLD) {
        airSafe = false;
    }
    if (!error) {
        if (pm25 > PM25_THRESHOLD || pm10 > PM10_THRESHOLD) {
            airSafe = false;
        }
    }

    // Display status on OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    if (airSafe) {
        display.print("Air Quality: OK");
    } else {
        display.print("Air Quality: DANGEROUS");
    }

    // Display individual sensor readings
    display.setCursor(0, 20);
    display.print("CO2 (MQ-135): ");
    display.print(voltageMQ135);
    display.println(" V");

    display.setCursor(0, 30);
    display.print("CO (MQ-7): ");
    display.print(voltageMQ7);
    display.println(" V");

    if (!error) {
        display.setCursor(0, 40);
        display.print("PM2.5: ");
        display.print(pm25);
        display.println(" ug/m3");

        display.setCursor(0, 50);
        display.print("PM10: ");
        display.print(pm10);
        display.println(" ug/m3");
    } else {
        display.setCursor(0, 40);
        display.println("Error reading PM sensor");
    }

    display.display();
    delay(2000);  // Delay for readability
}




// The code for the alert if the air is dangerouse 
#include <Wire.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int mq135Pin = A0;    // MQ-135 for CO2, etc.
const int mq7Pin = A1;      // MQ-7 for CO
const int buzzerPin = 9;    // Buzzer pin
const int ledPin = 8;       // LED pin
SDS011 my_sds;

// Thresholds for safe/dangerous air quality
const float CO2_THRESHOLD = 2.0;      // Approximate voltage for 1000 ppm CO2
const float CO_THRESHOLD = 1.2;       // Approximate voltage for 50 ppm CO
const float PM25_THRESHOLD = 55.0;    // PM2.5 threshold in µg/m³
const float PM10_THRESHOLD = 100.0;   // PM10 threshold in µg/m³

void setup() {
    Serial.begin(9600);

    // Initialize display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.display();
    delay(2000);
    display.clearDisplay();

    // Initialize SDS011 particulate sensor
    my_sds.begin(10, 11);   // RX, TX for SDS011
    pinMode(mq135Pin, INPUT);
    pinMode(mq7Pin, INPUT);
    
    // Initialize alert devices
    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // Read MQ-135 (CO2, NH3, etc.)
    int mq135Value = analogRead(mq135Pin);
    float voltageMQ135 = mq135Value * (5.0 / 1023.0);

    // Read MQ-7 (CO)
    int mq7Value = analogRead(mq7Pin);
    float voltageMQ7 = mq7Value * (5.0 / 1023.0);

    // Read SDS011 for PM2.5 and PM10
    float pm25, pm10;
    int error = my_sds.read(&pm25, &pm10);

    // Determine if air quality is OK or DANGEROUS
    bool airSafe = true;

    if (voltageMQ135 > CO2_THRESHOLD) {
        airSafe = false;
    }
    if (voltageMQ7 > CO_THRESHOLD) {
        airSafe = false;
    }
    if (!error) {
        if (pm25 > PM25_THRESHOLD || pm10 > PM10_THRESHOLD) {
            airSafe = false;
        }
    }

    // Display status on OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    if (airSafe) {
        display.print("Air Quality: OK");
        digitalWrite(buzzerPin, LOW);   // Turn off buzzer
        digitalWrite(ledPin, LOW);      // Turn off LED
    } else {
        display.print("Air Quality: DANGEROUS");
        
        // Activate alarm if air is dangerous
        digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
        digitalWrite(ledPin, HIGH);     // Turn on LED
        
        // Send notification (optional)
        sendAlertNotification();
    }

    // Display individual sensor readings
    display.setCursor(0, 20);
    display.print("CO2 (MQ-135): ");
    display.print(voltageMQ135);
    display.println(" V");

    display.setCursor(0, 30);
    display.print("CO (MQ-7): ");
    display.print(voltageMQ7);
    display.println(" V");

    if (!error) {
        display.setCursor(0, 40);
        display.print("PM2.5: ");
        display.print(pm25);
        display.println(" ug/m3");

        display.setCursor(0, 50);
        display.print("PM10: ");
        display.print(pm10);
        display.println(" ug/m3");
    } else {
        display.setCursor(0, 40);
        display.println("Error reading PM sensor");
    }

    display.display();
    delay(2000);  // Delay for readability
}

// Optional: Send an alert notification using Wi-Fi or GSM module
void sendAlertNotification() {
    // Example code for Wi-Fi Module to trigger IFTTT or other services
    // Requires an ESP8266 or GSM module setup with appropriate AT commands
    
    // Uncomment and replace with appropriate code to send notification
    /*
    Serial.println("Sending alert notification...");
    // Code to trigger IFTTT or another notification service
    */
}


// The coe for blinking when data is found
const int mq135Pin = A0;    // MQ-135 for CO2, etc.
const int mq7Pin = A1;      // MQ-7 for CO
const int ledPin = 8;       // LED pin

// Thresholds for safe/dangerous air quality
const float CO2_THRESHOLD = 2.0;      // Approximate voltage for 1000 ppm CO2
const float CO_THRESHOLD = 1.2;       // Approximate voltage for 50 ppm CO

void setup() {
    Serial.begin(9600);
    pinMode(mq135Pin, INPUT);
    pinMode(mq7Pin, INPUT);
    pinMode(ledPin, OUTPUT);    // Set LED pin as output
}

void loop() {
    // Read MQ-135 (CO2, NH3, etc.)
    int mq135Value = analogRead(mq135Pin);
    float voltageMQ135 = mq135Value * (5.0 / 1023.0);

    // Read MQ-7 (CO)
    int mq7Value = analogRead(mq7Pin);
    float voltageMQ7 = mq7Value * (5.0 / 1023.0);

    // Determine if air quality is dangerous
    bool airDangerous = false;

    if (voltageMQ135 > CO2_THRESHOLD || voltageMQ7 > CO_THRESHOLD) {
        airDangerous = true;
    }

    // Blink LED if air quality is dangerous
    if (airDangerous) {
        digitalWrite(ledPin, HIGH);   // Turn LED on
        delay(500);                   // Wait 500 milliseconds
        digitalWrite(ledPin, LOW);    // Turn LED off
        delay(500);                   // Wait another 500 milliseconds
    } else {
        digitalWrite(ledPin, LOW);    // Keep LED off if air is safe
    }

    delay(1000);  // Additional delay for the next reading
}




// The code for sending an alert to the fire station


const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* iftttKey = "YOUR_IFTTT_KEY";  // Replace with your IFTTT key
const char* iftttEventName = "air_alert";

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    // Air quality check (replace with your actual logic)
    bool airDangerous = checkAirQuality();

    if (airDangerous) {
        sendAlertNotification();
    }

    delay(60000);  // Check every minute
}

bool checkAirQuality() {
    // Replace with your actual air quality check code
    // Return true if air quality is dangerous, false otherwise
    return true;  // For testing purposes, always returns true
}

void sendAlertNotification() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        const int httpPort = 80;

        if (!client.connect("maker.ifttt.com", httpPort)) {
            Serial.println("Connection failed");
            return;
        }

        // Construct the URL for the HTTP request
        String url = "/trigger/";
        url += iftttEventName;
        url += "/with/key/";
        url += iftttKey;

        // Send the HTTP request
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: maker.ifttt.com\r\n" +
                     "Connection: close\r\n\r\n");

        Serial.println("Alert sent to IFTTT");
    }
}


// The code for an thank you screen



#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int mq135Pin = A0;    // MQ-135 for CO2, etc.
const int mq7Pin = A1;      // MQ-7 for CO

// Thresholds for safe/dangerous air quality
const float CO2_THRESHOLD = 2.0;      // Approximate voltage for 1000 ppm CO2
const float CO_THRESHOLD = 1.2;       // Approximate voltage for 50 ppm CO

void setup() {
    Serial.begin(9600);

    // Initialize the OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);  // Stay in a loop if the display allocation fails
    }
    display.display();
    delay(2000);  // Display startup screen
    display.clearDisplay();

    pinMode(mq135Pin, INPUT);
    pinMode(mq7Pin, INPUT);
}

void loop() {
    // Read MQ-135 (CO2, NH3, etc.)
    int mq135Value = analogRead(mq135Pin);
    float voltageMQ135 = mq135Value * (5.0 / 1023.0);

    // Read MQ-7 (CO)
    int mq7Value = analogRead(mq7Pin);
    float voltageMQ7 = mq7Value * (5.0 / 1023.0);

    // Check if the air quality is dangerous
    bool airDangerous = false;

    if (voltageMQ135 > CO2_THRESHOLD || voltageMQ7 > CO_THRESHOLD) {
        airDangerous = true;
    }

    // Clear the display and show readings
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("CO2 Voltage: ");
    display.print(voltageMQ135);
    display.println(" V");
    display.print("CO Voltage: ");
    display.print(voltageMQ7);
    display.println(" V");

    if (airDangerous) {
        display.println("Air Quality: DANGEROUS");
    } else {
        display.println("Air Quality: OK");
    }
    display.display();

    // Display "Thank You" message after showing data
    delay(2000);  // Wait 2 seconds to display data readings

    display.clearDisplay();
    display.setTextSize(2);     // Set text size for larger font
    display.setCursor(20, 25);  // Position text in the center
    display.print("Thank You!");
    display.display();

    delay(3000);  // Show "Thank You" message for 3 seconds

    display.clearDisplay();  // Clear the display for the next loop
}

