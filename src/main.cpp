#include <Arduino.h>
#include "M5StickCPlus.h"
#include <Wire.h> // I2C library
#include "7seg70.h"
#include "7seg20.h"
#include "M5UnitKmeterISO.h"

M5UnitKmeterISO kmeter;
uint8_t error_status = 0;
long delay_time      = 0;
float temp;
float inttemp;

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setSwapBytes(true);
    while (!kmeter.begin(&Wire, KMETER_DEFAULT_ADDR, 32, 33, 100000L)) {
      Serial.println("Unit KmeterISO not found");
    }
}

void loop() {
        error_status = kmeter.getReadyStatus();
        if (error_status == 0) {
          temp = (float)(kmeter.getCelsiusTempValue()) /100;
          inttemp = (float)(kmeter.getInternalCelsiusTempValue()) / 100;
              M5.Lcd.setFreeFont(&DSEG7_Classic_Regular_64);
              M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
              M5.Lcd.drawString(String(temp, 1),30,15);
              M5.Lcd.setFreeFont(&DSEG7_Classic_Bold_30);
              M5.Lcd.setTextColor(YELLOW, TFT_BLACK);
              M5.Lcd.drawString(String(inttemp, 1),140,100);
        } 
        else {
          Serial.printf("Error: %d", kmeter.getReadyStatus());
        }
        delay(500);
}
