#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, CoolingLimits range) {
    return (value < range.lowerLimit) ? TOO_LOW : (value > range.upperLimit) ? TOO_HIGH : NORMAL;
}

CoolingLimits getTemperatureRange(CoolingType coolingType) {
    CoolingLimits ranges[] = {
    {0, 35}, /*PASSIVE_COOLING*/
    {0, 45}, /*HI_ACTIVE_COOLING*/
    {0, 40}  /*MED_ACTIVE_COOLING*/
  };
  return ranges[coolingType];
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  CoolingLimits range = getTemperatureRange(coolingType);
  return inferBreach(temperatureInC, range);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
