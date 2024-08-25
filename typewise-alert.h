#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef struct {
    int lowerLimit;
    int upperLimit;
}CoolingLimits;

BreachType inferBreach(double value, CoolingLimits range);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
CoolingLimits getTemperatureRange(CoolingType coolingType);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
