/*
 Cinétique ~ V0.1
 
 componants
 4 x SN754410 H-bridge
 
 maurin.box@gmail.com
 
 // mapping
 
 OUT_0    -> pin 5
 OUT_1    -> pin 2
 OUT_2    -> pin 4
 OUT_3    -> pin 3
 
 OUT_4    -> pin 10
 OUT_5    -> pin 13 
 OUT_6    -> pin 9
 OUT_7    -> pin 8
 
 OUT_8    -> pin 11
 OUT_9    -> pin 7
 OUT_10   -> pin 12
 OUT_11   -> pin A2
 
 OUT_12   -> pin A1
 OUT_13   -> pin 6 
 OUT_14   -> pin A3
 OUT_15   -> pin A0
 */

 
////// Variables
const int POWER_PINS = 8;

unsigned long curentMillis = 0;

typedef struct cinetique {
  const int POWER_PIN_A;
  const int POWER_PIN_B;
  int motorDir;
  int time_on;
  int time_off;
  unsigned long lastMillis;
  boolean toggel;
};

cinetique strip[POWER_PINS] = {
  { 5,  2,   0, 1000, 4500, 0, true },     // strip 1
  { 4,  3,   1, 1300, 6000, 0, true },     // strip 2
  { 10, 13,  0, 570, 7000, 0, true },      // strip 3
  { 9,  8,   1, 2000, 9000, 0, true },     // strip 4
  { 11, 7,   0, 2500, 8500, 0, true },     // strip 5
  { 12, 16,  1, 1400, 9500, 0, true },     // strip 6
  { 15, 6,   0, 2000, 6000, 0, true },     // strip 5
  { 17, 14,  1, 1100, 5000, 0, true }      // strip 6
};

boolean DEBUG = false;

///////////////////////// initialisation
void setup(){
  if(DEBUG) Serial.begin(9600);
  for(int i=0; i<POWER_PINS; i++){
    pinMode(strip[i].POWER_PIN_A, OUTPUT);                // set all powerPin as OUTPUT
    pinMode(strip[i].POWER_PIN_B, OUTPUT);                // set all powerPin as OUTPUT
  }
}


////////////////////////////////////// boucle principale 
void loop(){

  for(int i=0; i<POWER_PINS; i++){
    curentMillis = millis();
    ///////////////// switch ON the strip
    if( (curentMillis - strip[i].lastMillis) >= strip[i].time_off && strip[i].toggel == true){
      
      if(DEBUG) Serial.print(strip[i].POWER_PIN_A), Serial.print(" "), Serial.print(strip[i].POWER_PIN_B), Serial.println(" ON");
      
      motorDriver(strip[i].POWER_PIN_A, strip[i].POWER_PIN_B, strip[i].motorDir);
      strip[i].toggel = false;
    }
    
    ///////////////// switch OFF the strip
    if( (curentMillis - strip[i].lastMillis) >= ( strip[i].time_off + strip[i].time_on) && strip[i].toggel == false){
      
      if(DEBUG) Serial.print(strip[i].POWER_PIN_A), Serial.print(" "), Serial.print(strip[i].POWER_PIN_B), Serial.println(" OFF");
      
      motorDriver(strip[i].POWER_PIN_A, strip[i].POWER_PIN_B, 2);
      strip[i].time_on = random(500, 1500);
      strip[i].time_off = random(1500, 2000);
      strip[i].motorDir = !strip[i].motorDir;
      strip[i].lastMillis = curentMillis;
      strip[i].toggel = true;
    }
  }
  delay(5);
}


////////////////////////////////////////////////////////////// fonction motorDriver
void motorDriver(int pin_motor_A, int pin_motor_B, int state){

  switch (state){
  case 0:
    digitalWrite(pin_motor_A, HIGH);     // set the LED off
    digitalWrite(pin_motor_B, LOW);      // set the LED on
    break;
  case 1:
    digitalWrite(pin_motor_A, LOW);      // set the LED off
    digitalWrite(pin_motor_B, HIGH);     // set the LED on
    break;
  case 2:
    digitalWrite(pin_motor_A, LOW);      // set the LED off
    digitalWrite(pin_motor_B, LOW);      // set the LED on
    break;
  }
}
