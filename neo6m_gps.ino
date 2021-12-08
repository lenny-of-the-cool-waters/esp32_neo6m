#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  //Begin serial communication Arduino IDE (Serial Monitor)

  //Begin serial communication Neo6mGPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (neogps.available()) {
      if (gps.encode(neogps.read())) {
        newData = true;
      }
    }
  }

  //If newData is true
  if (newData == true) {
    newData = false;
    Serial.print("Number of satellites: ");
    Serial.println(gps.satellites.value());
    print_speed();
  } else {
    Serial.println("No new data");
  }

}

void print_speed() {
  Serial.print("Location Valid: ");
  Serial.println(gps.location.isValid());
  if (gps.location.isValid() == 1) {
    //String gps_speed = String(gps.speed.kmph());
    Serial.print("Lat: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Lng: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("Speed: ");
    Serial.println(gps.speed.kmph());

    Serial.print("SAT:");
    Serial.println(gps.satellites.value());

    Serial.print("ALT:");
    Serial.print(gps.altitude.meters(), 0);
  } else {
    Serial.print("No Data \n");
  }

}
