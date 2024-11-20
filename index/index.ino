//to  make the MQ-135 read the air quaility


const int mq135Pin = A0;  // Analog pin connected to MQ-135
int airQuality = 0;       // Variable to store sensor reading

void setup() {
    Serial.begin(9600); // Start serial communication
    pinMode(mq135Pin, INPUT);
    Serial.println("MQ-135 Air Quality Monitoring");
}

void loop() {
    airQuality = analogRead(mq135Pin); // Read analog value from MQ-135

    // Convert analog value to a range (optional)
    float voltage = (airQuality / 1023.0) * 5.0; // Assuming 5V reference
    Serial.print("Raw Value: ");
    Serial.print(airQuality);
    Serial.print(" | Voltage: ");
    Serial.print(voltage);
    
    // Determine air quality status
    if (airQuality < 200) {
        Serial.println(" - Air Quality: Good");
    } else if (airQuality < 400) {
        Serial.println(" - Air Quality: Moderate");
    } else if (airQuality < 600) {
        Serial.println(" - Air Quality: Unhealthy");
    } else {
        Serial.println(" - Air Quality: Hazardous");
    }

    delay(1000); // Wait for 1 second before reading again
}




//Display the Data on the computar


const int mq135Pin = A0;  // Analog pin connected to MQ-135
int airQuality = 0;       // Variable to store sensor reading

void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud
    pinMode(mq135Pin, INPUT);
    Serial.println("Air Quality Monitoring Started");
}

void loop() {
    airQuality = analogRead(mq135Pin);  // Read analog value from MQ-135
    Serial.print("Air Quality Value: ");
    Serial.println(airQuality);  // Send the value to the Serial Monitor
    delay(1000);  // Wait for 1 second
}



//For displaying the data in bar graphs

const int mq135Pin = A0;  // Analog pin connected to MQ-135
int airQuality = 0;       // Variable to store sensor reading

void setup() {
    Serial.begin(9600);  // Start serial communication
    pinMode(mq135Pin, INPUT);
    Serial.println("time,CO2,NH3,NOx"); // Labels for plot
}

void loop() {
    airQuality = analogRead(mq135Pin); // Read analog value

    // Simulated values for different gases (calibration required)
    int CO2 = airQuality;        // Simulated CO2 level
    int NH3 = airQuality * 0.8;  // Simulated NH3 level
    int NOx = airQuality * 0.6;  // Simulated NOx level

    // Print values in CSV format
    Serial.print(millis() / 1000);  // Time in seconds
    Serial.print(",");
    Serial.print(CO2);
    Serial.print(",");
    Serial.print(NH3);
    Serial.print(",");
    Serial.println(NOx);

    delay(1000);  // Wait 1 second
}
