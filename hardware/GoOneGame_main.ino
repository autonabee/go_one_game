#include <XInput.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

// Joystick
#define JOY1_X A0
#define JOY1_Y A1

// Bouton pour reset la position du gyroscope
#define RESET_JOY 4 

// Boutons d'actions
// Config 1 en ligne
// #define BUTT_A 12
// #define BUTT_B 11
// #define BUTT_X 10
// #define BUTT_Y 9
// #define BUTT_RT 8 
// #define BUTT_LT 7
// #define BUTT_RB 6
// #define BUTT_LB 5 

// Config 2
#define BUTT_A 7
#define BUTT_B 8
#define BUTT_X 11
#define BUTT_Y 12
#define BUTT_RT 6
#define BUTT_LT 5
#define BUTT_RB 10
#define BUTT_LB 9


float joyZeroX=0;
float joyZeroY=0;

// limite inf et sup de l'angle (en degrés) détecté par le gyroscope
int upperLimit = 20; 
int lowerLimit = -20; 

void setup() {
  pinMode(BUTT_A, INPUT);
  pinMode(BUTT_B, INPUT);
  pinMode(BUTT_X, INPUT);
  pinMode(BUTT_Y, INPUT);
  pinMode(BUTT_LT, INPUT);
  pinMode(BUTT_RT, INPUT);
  pinMode(BUTT_LB, INPUT);
  pinMode(BUTT_RB, INPUT);

  pinMode(RESET_JOY, INPUT_PULLUP);

  Wire.begin();
  mpu6050.begin();

  //XInput.setAutoSend(false);  // Wait for all controls before sending
  XInput.begin();
}


void ResetMPU6050(float x, float y){
  // Définit l'origine du gyroscope à la position actuelle
  joyZeroX=x;
  joyZeroY=y;
}


void loop() {
  // JOYSTICK
  XInput.setJoystickY(JOY_RIGHT, map(analogRead(JOY1_X), 0, 1023, -32767, 32767)); // Modifier axes X/Y et mapping des valeurs pour adapter à l'orientation du joystick
  XInput.setJoystickX(JOY_RIGHT, map(analogRead(JOY1_Y), 0, 1023, -32767, 32767));

  // BOUTONS
  XInput.setButton(BUTTON_A, digitalRead(BUTT_A));
  XInput.setButton(BUTTON_B, digitalRead(BUTT_B));
  XInput.setButton(BUTTON_X, digitalRead(BUTT_X)); 
  XInput.setButton(BUTTON_Y, digitalRead(BUTT_Y));

  XInput.setButton(BUTTON_LB, digitalRead(BUTT_LB));
  XInput.setButton(BUTTON_RB, digitalRead(BUTT_RB));

  // GACHETTES
  XInput.setTrigger(TRIGGER_LEFT, map(digitalRead(BUTT_LT),0,1,0,255)); // Des boutons servent de gâchettes. Si le bouton est appuyé (1), la gâchette est entièrement appuyée (255)
  XInput.setTrigger(TRIGGER_RIGHT, map(digitalRead(BUTT_RT),0,1,0,255));


  // GYRO - JOYSTICK
  mpu6050.update();
  float joy2Y=mpu6050.getAngleX(); // float joy2Y=mpu6050.getAngleY(); // selon l'orientation du gyroscope dans la manette
  float joy2X=mpu6050.getAngleY(); // float joy2X=mpu6050.getAngleX();
  if (!digitalRead(RESET_JOY)) { // si le bouton RESET est appuyé
    ResetMPU6050(joy2X,joy2Y); // la position actuelle est définie comme origine du joystick
    }
  joy2X -= joyZeroX; // valeur par rapport à l'origine définie par l'utilisateur
  joy2Y -= joyZeroY;
  
  if (joy2X>upperLimit) joy2X=upperLimit; // angles bornés à la limite définie auparavant
  else if (joy2X<lowerLimit) joy2X=lowerLimit;
  if (joy2Y>upperLimit) joy2Y=upperLimit;
  else if (joy2Y<lowerLimit) joy2Y=lowerLimit;
 
  XInput.setJoystickX(JOY_LEFT, map(joy2X, lowerLimit,upperLimit, -32767, 32767)); // -32767, 32767 selon l'orientation du gyroscope dans la manette
  XInput.setJoystickY(JOY_LEFT, map(joy2Y, lowerLimit,upperLimit, 32767, -32767)); // idem

  XInput.send(); // envoi nouveau paquet à l'ordinateur
}
