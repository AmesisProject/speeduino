#include "Arduino.h"



//Amesis Project
void readPPS(bool=true);
byte PPS1last;               /**< The previous PPS1 reading */
unsigned long PPS1_time;     //The time the PPS1 sample was taken
unsigned long PPS1last_time; //The time the previous PPS sample was taken
byte PPS2last;               /**< The previous PPS2 reading */
unsigned long PPS2_time;     //The time the PPS2 sample was taken
unsigned long PPS2last_time; //The time the previous PPS sample was taken
byte TBSensorlast;           /**< The previous TBSensor reading */
unsigned long TBSensor_time;     //The time the PPS1 sample was taken
unsigned long TBSensorlast_time; //The time the previous PPS sample was taken

volatile PORT_TYPE *tbMotor1_pin_port;
volatile PINMASK_TYPE tbMotor1_pin_mask;
volatile PORT_TYPE *tbMotor2_pin_port;
volatile PINMASK_TYPE tbMotor2_pin_mask;