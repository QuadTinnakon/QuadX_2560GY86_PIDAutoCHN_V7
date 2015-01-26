/*
project_QuadX_2560 GY86_PIDAuto_V1  
1. Automatic  Takeoff 
2. Landing
by: tinnakon kheowree  
tinnakon_za@hotmail.com
tinnakonza@gmail.com
http://quad3d-tin.lnwshop.com/
https://www.facebook.com/tinnakonza
*/
int CH_THR = 1000;
int CH_AIL = 1500;
int CH_ELE = 1500;
int CH_RUD = 1500;
float CH_AILf = 1500;
float CH_ELEf = 1500;
float CH_RUDf = 1500;
int CH_AIL_Cal = 1500;
int CH_ELE_Cal = 1500;
int CH_RUD_Cal = 1500;
int AUX_1 = 1500;
int AUX_2 = 1500;
int AUX_3 = 1500;
int AUX_4 = 1500;

int roll_mid = 1475;
int pitch_mid = 1479;
int yaw_mid = 1474;


//RX PIN assignment inside the port //for PORTK
#define THROTTLEPIN                1  //PIN 62 =  PIN A8
#define ROLLPIN                    2  //PIN 63 =  PIN A9
#define PITCHPIN                   0  //PIN 64 =  PIN A10
#define YAWPIN                     3  //PIN 65 =  PIN A11
#define AUX1PIN                    4  //PIN 66 =  PIN A12
#define AUX2PIN                    5  //PIN 67 =  PIN A13
#define AUX3PIN                    6  //PIN 68 =  PIN A14
#define AUX4PIN                    7  //PIN 69 =  PIN A15
#define PCINT_PIN_COUNT            8
#define PCINT_RX_BITS              (1<<2),(1<<4),(1<<5),(1<<6),(1<<7),(1<<0),(1<<1),(1<<3)
#define PCINT_RX_PORT              PORTK
#define PCINT_RX_MASK              PCMSK2
#define PCIR_PORT_BIT              (1<<2)
#define RX_PC_INTERRUPT            PCINT2_vect
#define RX_PCINT_PIN_PORT          PINK
#define RC_CHANS 8  //read Ch

static uint8_t PCInt_RX_Pins[PCINT_PIN_COUNT] = {PCINT_RX_BITS}; // if this slowes the PCINT readings we can switch to a define for each pcint bit
volatile uint16_t rcValue[RC_CHANS] = {1502, 1502, 1502, 1502, 1502, 1502, 1502, 1502}; // interval [1000;2000]
static int16_t rcData[RC_CHANS];    // interval [1000;2000]
static uint8_t rcChannel[RC_CHANS]  = {THROTTLEPIN, ROLLPIN, PITCHPIN, YAWPIN, AUX1PIN,AUX2PIN,AUX3PIN,AUX4PIN};//
  
/**************************************************************************************/
/***************                   RX Pin Setup                    ********************/
/**************************************************************************************/

void configureReceiver() {
  /******************    Configure each rc pin for PCINT    ***************************/
  DDRK = 0;  // defined PORTK as a digital port ([A8-A15] are consired as digital PINs and not analogical)
     // PCINT activation
    for(uint8_t i = 0; i < PCINT_PIN_COUNT; i++){ // i think a for loop is ok for the init.
      PCINT_RX_PORT |= PCInt_RX_Pins[i];
      PCINT_RX_MASK |= PCInt_RX_Pins[i];
    }
    PCICR = PCIR_PORT_BIT;
}

 // port change Interrupt
ISR(RX_PC_INTERRUPT) { //this ISR is common to every receiver channel, it is call everytime a change state occurs on a RX input pin
  uint8_t mask;
  uint8_t pin;
  uint16_t cTime,dTime;
  static uint16_t edgeTime[8];
  static uint8_t PCintLast;
  pin = RX_PCINT_PIN_PORT; // RX_PCINT_PIN_PORT indicates the state of each PIN for the arduino port dealing with Ports digital pins
  mask = pin ^ PCintLast;   // doing a ^ between the current interruption and the last one indicates wich pin changed
  cTime = micros();         // micros() return a uint32_t, but it is not usefull to keep the whole bits => we keep only 16 bits
  sei();                    // re enable other interrupts at this point, the rest of this interrupt is not so time critical and can be interrupted safely
  PCintLast = pin;          // we memorize the current state of all PINs [D0-D7]
  
 if (mask & 1<<2)           //indicates the bit 2 of the arduino port [D0-D7], that is to say digital pin 2, if 1 => this pin has just changed
  if (!(pin & 1<<2)) {     //indicates if the bit 2 of the arduino port [D0-D7] is not at a high state (so that we match here only descending PPM pulse)
    dTime = cTime-edgeTime[2]; if (900<dTime && dTime<2200) rcValue[2] = dTime; // just a verification: the value must be in the range [1000;2000] + some margin
  } else edgeTime[2] = cTime;    // if the bit 2 of the arduino port [D0-D7] is at a high state (ascending PPM pulse), we memorize the time
if (mask & 1<<4)   //same principle for other channels   // avoiding a for() is more than twice faster, and it's important to minimize execution time in ISR
  if (!(pin & 1<<4)) {
    dTime = cTime-edgeTime[4]; if (900<dTime && dTime<2200) rcValue[4] = dTime;
  } else edgeTime[4] = cTime;
if (mask & 1<<5)
  if (!(pin & 1<<5)) {
    dTime = cTime-edgeTime[5]; if (900<dTime && dTime<2200) rcValue[5] = dTime;
  } else edgeTime[5] = cTime;
if (mask & 1<<6)
  if (!(pin & 1<<6)) {
    dTime = cTime-edgeTime[6]; if (900<dTime && dTime<2200) rcValue[6] = dTime;
  } else edgeTime[6] = cTime;
if (mask & 1<<7)
  if (!(pin & 1<<7)) {
    dTime = cTime-edgeTime[7]; if (900<dTime && dTime<2200) rcValue[7] = dTime;
  } else edgeTime[7] = cTime;
 if (mask & 1<<0)
  if (!(pin & 1<<0)) {
    dTime = cTime-edgeTime[0]; if (900<dTime && dTime<2200) rcValue[0] = dTime;
  } else edgeTime[0] = cTime;
    if (mask & 1<<1)
  if (!(pin & 1<<1)) {
    dTime = cTime-edgeTime[1]; if (900<dTime && dTime<2200) rcValue[1] = dTime;
  } else edgeTime[1] = cTime;
    if (mask & 1<<3)
  if (!(pin & 1<<3)) {
    dTime = cTime-edgeTime[3]; if (900<dTime && dTime<2200) rcValue[3] = dTime;
  } else edgeTime[3] = cTime;
}


/**************************************************************************************/
/***************          compute and Filter the RX data           ********************/
/**************************************************************************************/
uint16_t readRawRC(uint8_t chan) {
  uint16_t data;

    uint8_t oldSREG;
    oldSREG = SREG; cli(); // Let's disable interrupts
    data = rcValue[rcChannel[chan]]; // Let's copy the data Atomically
    SREG = oldSREG;        // Let's restore interrupt state
  return data; // We return the value correctly copied when the IRQ's where disabled
}

void computeRC() {
  static uint16_t rcData4Values[RC_CHANS][4], rcDataMean[RC_CHANS];
  static uint8_t rc4ValuesIndex = 0;
  uint8_t chan,a;

    rc4ValuesIndex++;
    if (rc4ValuesIndex == 4) rc4ValuesIndex = 0;
    for (chan = 0; chan < RC_CHANS; chan++) {

      rcData4Values[chan][rc4ValuesIndex] = readRawRC(chan);
   
      rcDataMean[chan] = 0;
      for (a=0;a<4;a++) rcDataMean[chan] += rcData4Values[chan][a];
      rcDataMean[chan]= (rcDataMean[chan]+2)>>2;
      if ( rcDataMean[chan] < (uint16_t)rcData[chan] -3)  rcData[chan] = rcDataMean[chan]+2;//+2
      if ( rcDataMean[chan] > (uint16_t)rcData[chan] +3)  rcData[chan] = rcDataMean[chan]-2;
    }
    CH_THR = rcData[THROTTLEPIN];   // Throttle            
    CH_AIL = rcData[ROLLPIN];   // Aileron
    CH_ELE = rcData[PITCHPIN];   // Elevator
    CH_RUD = rcData[YAWPIN];   // Ruder
    AUX_1 = rcData[AUX1PIN];    // Aux   
    CH_AILf = CH_AILf + (CH_AIL - CH_AILf)*0.02/tarremote;
    CH_ELEf = CH_ELEf + (CH_ELE - CH_ELEf)*0.02/tarremote;
    CH_RUDf = CH_RUDf + (CH_RUD - CH_RUDf)*0.02/tarremote;
}
void RC_Calibrate(){
  Serial.print("RC_Calibrate");Serial.println("\t");
  for (int i = 0; i < 10; i++) {
    computeRC();
    delay(20);
  }
  CH_AIL_Cal = CH_AIL;
  CH_ELE_Cal = CH_ELE;
  CH_RUD_Cal = CH_RUD;
    Serial.print(CH_AIL_Cal);Serial.print("\t");//-0.13
    Serial.print(CH_ELE_Cal);Serial.print("\t");//-0.10
    Serial.print(CH_RUD_Cal);Serial.println("\t");//0.03 
}
