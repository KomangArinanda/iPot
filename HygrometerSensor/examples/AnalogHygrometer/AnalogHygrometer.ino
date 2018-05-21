/*
 * \brief Get humidity information from Analog Rain drop sensor (or moisture sensor) every second
 *
 * \author Quentin Comte-Gaz <quentin@comte-gaz.com>
 * \date 19 July 2016
 * \license MIT License (contact me if too restrictive)
 * \copyright Copyright (c) 2016 Quentin Comte-Gaz
 * \version 2.0
 *
 * \history
 *  - v1.0 Base
 *  - v2.0 Adapt to new library
 */

#include <HygrometerSensor.h>
#define RELAY_ON 0
#define RELAY_OFF 1
#define RELAY_1 D2

// Create Analog rain drop sensor (or moisture sensor) instance on A1 pin
HygrometerSensor analog_rain_drop(HygrometerSensor::ANALOG, D4);
char auth[] = "816a10e8059742969a5a92ae138bc4ac";

char ssid[] = "satyadara-com";
char pass[] = "yeonhee-love";

void setup(void)
{
  Serial.begin(9600);
  //set pin as output
  pinMode(RELAY_1, OUTPUT);
  //initialize relay one as off
  digitalWrite(RELAY_1, RELAY_OFF);

  // Set analog parameters (min value, max value, value to switch from "dry" to "is raining") (optional call)
  if (!analog_rain_drop.setAnalogParameters(ANALOG_HUMIDITY_MIN, ANALOG_HUMIDITY_MAX, 800)) {
    Serial.print("Error while setting Analog parameters\n");
  }
  // Get analog parameters (optional call)
  int min, max, is_raining;
  analog_rain_drop.getAnalogParameters(min, max, is_raining);
  Serial.print("Minimum analog value: ");
  Serial.print(min, DEC);
  Serial.print("\nMaximum analog value: ");
  Serial.print(max, DEC);
  Serial.print("\nValue used as switch from 'dry' to 'is raining': ");
  Serial.print(is_raining, DEC);
  Serial.print("\n");
}

void loop()
{
  // Check rain state and value every sec

  Serial.print("Rain drop value: ");
  Serial.print(analog_rain_drop.readHumidityValue());
  Serial.print(" (");
  if (analog_rain_drop.isHumid()) {
    Serial.print("raining");
    digitalWrite(RELAY_1, RELAY_OFF);
  } else {
    Serial.print("dry");
    digitalWrite(RELAY_1, RELAY_ON);
    delay(2000);
    digitalWrite(RELAY_1, RELAY_OFF);
  }
  Serial.print(")\n");

  delay(3000);
}
