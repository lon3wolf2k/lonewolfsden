#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 14 // DHT22 Datapin to D5-GPIO14
#define DHTTYPE DHT22
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// WiFi network info.
char ssid[] = "yourssid"; 
char wifiPassword[] = "wifipassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = ""; 
char password[] = ""; 
char clientID[] = "";

unsigned long lastMillis = 0;


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}



void loop() {
  Cayenne.loop();

  sensors_event_t event;

    float humidity = dht.readHumidity();

    float temp = dht.readTemperature();
    

    
    Cayenne.virtualWrite(1, temp, TYPE_TEMPERATURE, UNIT_CELSIUS);

    Cayenne.virtualWrite(2, humidity, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
    
     // clear display
  display.clearDisplay();
  
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(temp);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(humidity);
  display.print(" %"); 
  
  display.display(); 
  delay(10000);
  }

 
