#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define BUZZER 28
#define RED 6
#define GREEN 7
#define BLUE 8

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  Serial.begin(9600);
  dht.begin();
  Serial.println("test");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  float temperatureF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float heatIndexF = dht.computeHeatIndex(temperatureF, humidity);
  float heatIndexC = dht.computeHeatIndex(temperatureC, humidity, false);
  display.setCursor(0,0);
  display.println("Temperature: ");
  display.println(temperatureC);
  display.println("humidity: ");
  display.print(humidity);
  display.display();
  if(temperatureC >= 35){
    pinMode(BUZZER, HIGH);
    pinMode(RED, LOW);
    pinMode(GREEN, LOW);
    pinMode(BLUE, HIGH);
    delay(500);
    pinMode(BUZZER, LOW);
    pinMode(RED, LOW);
    pinMode(GREEN, LOW);
    pinMode(BLUE, LOW);
    delay(500);
  } else if (temperatureC >= 45) {
    pinMode(BUZZER, HIGH);
    pinMode(RED, HIGH);
    pinMode(GREEN, LOW);
    pinMode(BLUE, LOW);
    delay(500);
    pinMode(BUZZER, LOW);
    pinMode(RED, LOW);
    pinMode(GREEN, LOW);
    pinMode(BLUE, LOW);
    delay(500);
  } else {
    pinMode(BUZZER, LOW);
    pinMode(RED, LOW);
    pinMode(GREEN, HIGH);
    pinMode(BLUE, LOW);
    delay(500);
    pinMode(BUZZER, LOW);
    pinMode(RED, LOW);
    pinMode(GREEN, LOW);
    pinMode(BLUE, LOW);
    delay(500);
  }

  display.clearDisplay();
}