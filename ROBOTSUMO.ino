#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Motor A (Izquierdo)
const int PWMA = 21; 
const int AIN2 = 19; 
const int AIN1 = 18; 

// Motor B (Derecho)
const int PWMB = 3;  
const int BIN1 = 22; 
const int BIN2 = 23; 

const int STBY = 5;  

//Configuración de PWM del ESP32 
const int freq = 1000; 
const int pwmChannelA = 0;
const int pwmChannelB = 1;
const int resolution = 8; 

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  // Activar el driver de motores
  digitalWrite(STBY, HIGH);

  ledcSetup(pwmChannelA, freq, resolution);
  ledcSetup(pwmChannelB, freq, resolution);

  ledcAttachPin(PWMA, pwmChannelA);
  ledcAttachPin(PWMB, pwmChannelB);

  Dabble.begin("MiESP32_BT");
}

void loop() {
  Dabble.processInput(); 

  // Leer los ejes X y Y del Joystick 
  float x = GamePad.getXaxisData();
  float y = GamePad.getYaxisData();

  // Ignora movimientos accidentales pequeños para que vaya recto
  if (abs(x) < 1.5) x = 0;
  if (abs(y) < 1.5) y = 0;

  int steering = map(x, -7, 7, -200, 200); 
  
  // Acelerador normal
  int throttle = map(y, -7, 7, -200, 200); 

  //  Círculo y X 
  if (GamePad.isCirclePressed()) {
    throttle = 200;
    steering = 0;
  } else if (GamePad.isCrossPressed()) {
    throttle = -200;
    steering = 0;
  }

  // Tracción
  int leftMotor = throttle + steering;  
  int rightMotor = throttle - steering; 

  // Restringir para proteger el PWM y evitar que el ESP32 mande errores
  leftMotor = constrain(leftMotor, -200, 200);
  rightMotor = constrain(rightMotor, -200, 200);

  // Control Motor A 
  if (leftMotor > 10) { 
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    ledcWrite(pwmChannelA, leftMotor);
  } else if (leftMotor < -10) { 
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    ledcWrite(pwmChannelA, abs(leftMotor)); 
  } else { 
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    ledcWrite(pwmChannelA, 0);
  }

  // Control Motor B
  if (rightMotor > 10) { 
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(pwmChannelB, rightMotor);
  } else if (rightMotor < -10) { 
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(pwmChannelB, abs(rightMotor));
  } else { 
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    ledcWrite(pwmChannelB, 0);
  }
}