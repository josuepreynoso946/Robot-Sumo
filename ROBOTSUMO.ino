#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

const int Motor1Ade = 16;
const int Motor2Ade = 17;
const int Motor1Ret = 18;
const int Motor2Ret = 19;

void setup() {
  Serial.begin(115200);
  pinMode(Motor1Ade, OUTPUT);
  pinMode(Motor2Ade, OUTPUT);
  pinMode(Motor1Ret, OUTPUT);
  pinMode(Motor2Ret, OUTPUT);
  Dabble.begin("MiESP32_BT");

}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed())
  { 
    Serial.println("Comando: AVANZAR");
    digitalWrite(Motor1Ade, HIGH);
    digitalWrite(Motor2Ade, HIGH);
    digitalWrite(Motor1Ret, LOW);
    digitalWrite(Motor2Ret, LOW);
  }
  else if (GamePad.isDownPressed())
  { 
    Serial.println("Comando: RETROCESO");
    digitalWrite(Motor1Ade, LOW);
    digitalWrite(Motor2Ade, LOW);
    digitalWrite(Motor1Ret, HIGH);
    digitalWrite(Motor2Ret, HIGH);
  }
  else if (GamePad.isRightPressed())
  { 
    Serial.println("Comando: DERECHA");
    digitalWrite(Motor1Ade, LOW);
    digitalWrite(Motor2Ade, HIGH);
    digitalWrite(Motor1Ret, LOW);
    digitalWrite(Motor2Ret, LOW);
  }
  else if (GamePad.isLeftPressed())
  { 
    Serial.println("Comando: IZQUIERDA");
    digitalWrite(Motor1Ade, HIGH);
    digitalWrite(Motor2Ade, LOW);
    digitalWrite(Motor1Ret, LOW);
    digitalWrite(Motor2Ret, LOW);
  }
  else { 
    digitalWrite(Motor1Ade, LOW);
    digitalWrite(Motor2Ade, LOW);
    digitalWrite(Motor1Ret, LOW);
    digitalWrite(Motor2Ret, LOW);
  }
}
