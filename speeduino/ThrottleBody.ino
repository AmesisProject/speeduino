#include "pages.h"


//Amesis Project
void readPPS(bool useFilter)
{
  //PPS1
  PPS1last = currentStatus.PPS1; //currentStatus.PPS1
  PPS1last_time = PPS1_time;
  #if defined(ANALOG_ISR)
    byte tempPPS1 = fastMap1023toX(AnChannel[pinPPS1-A0], 255); //Get the current raw PPS ADC value and map it into a byte
  #else
    analogRead(pinPPS1);
    byte tempPPS1 = fastMap1023toX(analogRead(pinPPS1), 255); //Get the current raw PPS ADC value and map it into a byte
  #endif
  //The use of the filter can be overridden if required. This is used on startup to disable priming pulse if flood clear is wanted
  if(useFilter == true) { currentStatus.pps1ADC = ADC_FILTER(tempPPS1, configPage13.ADCFILTER_PPS1, currentStatus.pps1ADC); }
  else { currentStatus.pps1ADC = tempPPS1; }
  //currentStatus.pps1ADC = ADC_FILTER(tempPPS1, 128, currentStatus.pps1ADC);
  byte temp1ADC = currentStatus.pps1ADC; //The temp1ADC value is used in order to allow TunerStudio to recover and redo the PPS calibration if this somehow gets corrupted

  if(configPage13.pps1Max > configPage13.pps1Min) 
  {
    //Check that the ADC values fall within the min and max ranges (Should always be the case, but noise can cause these to fluctuate outside the defined range).
    if (currentStatus.pps1ADC < configPage13.pps1Min) { temp1ADC = configPage13.pps1Min; }
    else if(currentStatus.pps1ADC > configPage13.pps1Max) { temp1ADC = configPage13.pps1Max; }
    currentStatus.PPS1 = map(temp1ADC, configPage13.pps1Min, configPage13.pps1Max, 0, 100); //Take the raw PPS ADC value and convert it into a PPS% based on the calibrated values
  }
  else
  {
    //This case occurs when the PPS +5v and gnd are wired backwards, but the user wishes to retain this configuration.
    //In such a case, pps1Min will be greater then pps1Max and hence checks and mapping needs to be reversed

    temp1ADC = 255 - currentStatus.pps1ADC; //Reverse the ADC values
    uint16_t tempPPS1Max = 255 - configPage13.pps1Max;
    uint16_t tempPPS1Min = 255 - configPage13.pps1Min;

    //All checks below are reversed from the standard case above
    if (temp1ADC > tempPPS1Max) { temp1ADC = tempPPS1Max; }
    else if(temp1ADC < tempPPS1Min) { temp1ADC = tempPPS1Min; }
    currentStatus.PPS1 = map(temp1ADC, tempPPS1Min, tempPPS1Max, 0, 100);
  }

  /* //Check whether the closed throttle position sensor is active
  if(configPage13.CPPSEnabled == true)
  {
    if(configPage13.CTPSPolarity == 0) { currentStatus.CTPSActive = !digitalRead(pinCTPS); } //Normal mode (ground switched)
    else { currentStatus.CPPSActive = digitalRead(pinCTPS); } //Inverted mode (5v activates closed throttle position sensor)
  }
  else { currentStatus.CTPSActive = 0; }
  */
  PPS1_time = micros(); 
  


 // PPS2
  PPS2last = currentStatus.PPS2; //currentStatus.PPS2
  PPS2last_time = PPS2_time;
  #if defined(ANALOG_ISR)
    byte tempPPS2 = fastMap1023toX(AnChannel[pinPPS2-A0], 255); //Get the current raw PPS ADC value and map it into a byte
  #else
    analogRead(pinPPS2);
    byte tempPPS2 = fastMap1023toX(analogRead(pinPPS2), 255); //Get the current raw PPS ADC value and map it into a byte
  #endif
  //The use of the filter can be overridden if required. This is used on startup to disable priming pulse if flood clear is wanted
  if(useFilter == true) { currentStatus.pps2ADC = ADC_FILTER(tempPPS2, configPage13.ADCFILTER_PPS2, currentStatus.pps2ADC); }
  else { currentStatus.pps2ADC = tempPPS2; }
  //currentStatus.pps2ADC = ADC_FILTER(tempPPS2, 128, currentStatus.pps2ADC);
  byte temp2ADC = currentStatus.pps2ADC; //The temp2ADC value is used in order to allow TunerStudio to recover and redo the PPS calibration if this somehow gets corrupted

  if(configPage13.pps2Max > configPage13.pps2Min)
  {
    //Check that the ADC values fall within the min and max ranges (Should always be the case, but noise can cause these to fluctuate outside the defined range).
    if (currentStatus.pps2ADC < configPage13.pps2Min) { temp2ADC = configPage13.pps2Min; }
    else if(currentStatus.pps2ADC > configPage13.pps2Max) { temp2ADC = configPage13.pps2Max; }
    currentStatus.PPS2 = map(temp2ADC, configPage13.pps2Min, configPage13.pps2Max, 0, 100); //Take the raw PPS ADC value and convert it into a PPS% based on the calibrated values
  }
  else
  {
    //This case occurs when the PPS +5v and gnd are wired backwards, but the user wishes to retain this configuration.
    //In such a case, pps2Min will be greater then pps2Max and hence checks and mapping needs to be reversed

    temp2ADC = 255 - currentStatus.pps2ADC; //Reverse the ADC values
    uint16_t tempPPS2Max = 255 - configPage13.pps2Max;
    uint16_t tempPPS2Min = 255 - configPage13.pps2Min;

    //All checks below are reversed from the standard case above
    if (temp2ADC > tempPPS2Max) { temp2ADC = tempPPS2Max; }
    else if(temp2ADC < tempPPS2Min) { temp2ADC = tempPPS2Min; }
    currentStatus.PPS2 = map(temp2ADC, tempPPS2Min, tempPPS2Max, 0, 100);
  }

  /* //Check whether the closed throttle position sensor is active
  if(configPage13.APthrottleBodyEnable == true)
  {
    if(configPage13.CTPSPolarity == 0) { currentStatus.CTPSActive = !digitalRead(pinCTPS); } //Normal mode (ground switched)
    else { currentStatus.CTPSActive = digitalRead(pinCTPS); } //Inverted mode (5v activates closed throttle position sensor)
  }
  else { currentStatus.CTPSActive = 0; }
 */

  PPS2_time = micros(); 
  

  //PPS Total
currentStatus.PPSTotal = (currentStatus.PPS1+currentStatus.PPS2) / 2 ;

  if((currentStatus.PPS1+currentStatus.PPS2) / 2 > currentStatus.PPS1*1.1) && ((currentStatus.PPS1+currentStatus.PPS2) / 2 < currentStatus.PPS1*0.9) //si PPS1 ou PPS2 depasse la moyenne de PPS1+PPS2 alors defaut 
  { currentStatus.PPSTotal = 0 ; } //alors mettre la valeur PPSTotal a 0
   // erreur PPS1 
   
  else if ((currentStatus.PPS1+currentStatus.PPS2) / 2 > currentStatus.PPS2*1.1) && ((currentStatus.PPS1+currentStatus.PPS2) / 2 < currentStatus.PPS2*0.9) //si PPS1 ou PPS2 depasse la moyenne de PPS1+PPS2 alors defaut 
  { currentStatus.PPSTotal = 0 ; //alors mettre la valeur PPSTotal a 0
   // erreur PPS2
  
  



  //TBSensor
  TBSensorlast = currentStatus.TBSensor; //currentStatus.TBSensor
  TBSensorlast_time = TBSensor_time;
  #if defined(ANALOG_ISR)
    byte tempTBSensor = fastMap1023toX(AnChannel[pinTBSensor-A0], 255); //Get the current raw TBSensor ADC value and map it into a byte
  #else
    analogRead(pinTBSensor);
    byte tempTBSensor = fastMap1023toX(analogRead(pinTBSensor), 255); //Get the current raw TBSensor value and map it into a byte
  #endif
  //The use of the filter can be overridden if required. This is used on startup to disable priming pulse if flood clear is wanted
  if(useFilter == true) { currentStatus.TBSensorADC = ADC_FILTER(tempTBSensor, configPage13.ADCFILTER_TBS1, currentStatus.TBSensorADC); }
  else { currentStatus.TBSensorADC = tempTBSensor; }
  //currentStatus.TBSensorADC = ADC_FILTER(tempTBSensor, 128, currentStatus.TBSensorADC);
  byte temp3ADC = currentStatus.TBSensorADC; //The temp3ADC value is used in order to allow TunerStudio to recover and redo the TBSensor calibration if this somehow gets corrupted

  if(configPage13.tbs1Max > configPage13.tbs1Min) 
  {
    //Check that the ADC values fall within the min and max ranges (Should always be the case, but noise can cause these to fluctuate outside the defined range).
    if (currentStatus.TBSensorADC < configPage13.tbs1Min) { temp3ADC = configPage13.tbs1Min; }
    else if(currentStatus.TBSensorADC > configPage13.tbs1Max) { temp3ADC = configPage13.tbs1Max; }
    currentStatus.TBSensor = map(temp3ADC, configPage13.tbs1Min, configPage13.tbs1Max, 0, 100); //Take the raw TBSensor ADC value and convert it into a TBSensor% based on the calibrated values
  }
  else
  {
    //This case occurs when the TBSensor +5v and gnd are wired backwards, but the user wishes to retain this configuration.
    //In such a case, tbs1Min will be greater then tbs1Max and hence checks and mapping needs to be reversed

    temp3ADC = 255 - currentStatus.TBSensorADC; //Reverse the ADC values
    uint16_t tempTBS1Max = 255 - configPage13.tbs1Max;
    uint16_t tempTBS1Min = 255 - configPage13.tbs1Min;

    //All checks below are reversed from the standard case above
    if (temp3ADC > tempTBS1Max) { temp3ADC = tempTBS1Max; }
    else if(temp3ADC < tempTBS1Min) { temp3ADC = tempTBS1Min; }
    currentStatus.TBSensor = map(temp3ADC, tempTBS1Min, tempTBS1Max, 0, 100);
  }

  /* //Check whether the closed throttle position sensor is active
  if(configPage13.CPPSEnabled == true)
  {
    if(configPage13.CTPSPolarity == 0) { currentStatus.CTPSActive = !digitalRead(pinCTPS); } //Normal mode (ground switched)
    else { currentStatus.CPPSActive = digitalRead(pinCTPS); } //Inverted mode (5v activates closed throttle position sensor)
  }
  else { currentStatus.CTPSActive = 0; }
  */
  TBSensor_time = micros(); 
  
   //Amesis Project TESTE LED
  tbMotor1_pin_port = portOutputRegister(digitalPinToPort(pinTBMotor1));
  tbMotor1_pin_mask = digitalPinToBitMask(pinTBMotor1);
  tbMotor2_pin_port = portOutputRegister(digitalPinToPort(pinTBMotor2));
  tbMotor2_pin_mask = digitalPinToBitMask(pinTBMotor2);

 //if(currentStatus.TBSensor > 0) 
 if (currentStatus.PPS1 >= currentStatus.TBSensor) 
 {
   digitalWrite(pinTBMotor1, LOW);
   digitalWrite(pinTBMotor2, HIGH);
   //digitalWrite(pinTBMotorENA, HIGH);
   
   }
 else 
 {
   digitalWrite(pinTBMotor1, HIGH); 
   digitalWrite(pinTBMotor2, LOW);
   //digitalWrite(pinTBMotorENA, LOW);
   }
  
 
}