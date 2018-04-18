#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <EEPROM.h>
#include <fuzzy_table.h>
#include <PID_Beta6.h>
#include <MotorWheel.h>
#include <Omni4WD.h>
#include <fuzzy_table.h>
#include <PID_Beta6.h>
#include <Servo.h>

/*
   wheel1   \                    /   wheel4
   Left     \                    /   Right
                              power switch
   wheel2   /                    \   wheel3
   Right    /                    \   Left
 */

// Init OmniWheel (pas de doc explicite, code repris tel quel) :
irqISR(irq1,isr1);
MotorWheel wheel1(3,2,4,5,&irq1);
irqISR(irq2,isr2);
MotorWheel wheel2(11,12,14,15,&irq2);
irqISR(irq3,isr3);
MotorWheel wheel3(9,8,16,17,&irq3);
irqISR(irq4,isr4);
MotorWheel wheel4(10,7,18,19,&irq4);
Omni4WD Omni(&wheel1,&wheel2,&wheel3,&wheel4);

// Init vérin (un seul pour l'instant) :
Servo myVerin;
int posVerin = 0;
int incVerin = 1;
int pinVerin = 5; // Pin du vérin sur la carte : à changer pour le bon...

// Init Serial (Node.js <-> Arduino) :
String fromSerial0 = "";
int indexStart0;
int indexEnd0;
const float pi = 3.14159;

// Pas vraiment documenté, à changer pour régler le déplacement en cercle :
const int speedMMPS = 10;
const float omega = 1.0;

void setup() {
  // Setup OmniWheel :
  TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz
  Omni.PIDEnable(0.31,0.01,0,10);

  // Setup vérin :
  myVerin.attach(pinVerin);

  // Setup Serial :
  Serial.begin(115200);
  fromSerial0.reserve(512);
}

void loop() {
  if (Serial.available()) {
    fromSerial0.concat(char(Serial.read()));
    indexEnd0 = fromSerial0.indexOf("]");
    if (indexEnd0 != -1) {
      indexStart0 = fromSerial0.indexOf("[");
      if (indexStart0 != -1) {
        if (indexStart0 < indexEnd0) {
          fromSerial0 = fromSerial0.substring(indexStart0, indexEnd0 - indexStart0 + 1);
          if (fromSerial0.indexOf("wheel") != -1) {
            moveOmni();
            Serial.print("[ok]");
          } else if (fromSerial0.indexOf("verin") != -1) {
            moveVerin();
            Serial.print("[ok]");
          } else if (fromSerial0.indexOf("both") != -1) {
            moveVerin();
            moveOmni();
            Serial.print("[ok]");
          } else if (fromSerial0.indexOf("circle") != -1) {
            for (float rad = 0.0; rad < 2 * pi; rad += 0.01) {
              Omni.setCarMove(speedMMPS, rad, omega);
              delay(10);
            }
            Serial.print("[ok]");
          }
          fromSerial0 = "";
        } else {
          fromSerial0 = fromSerial0.substring(indexStart0);
        }
      } else {
        fromSerial0 = "";
      }
    }
  }

  delay(10);
}

void moveOmni() {
  // On bouge l'OmniWhel (code de démo, semble bloquant) :
  Omni.demoActions(200,5000,500,false);
}

void moveVerin() {
  // On bouge le vérin :
  myVerin.write(posVerin);

  // on incrémente/décrémente la position du vérin :
  posVerin += incVerin;
  if (posVerin > 180) {
    posVerin = 179;
    incVerin = -1;
  } else if (posVerin < 0) {
    posVerin = 1;
    incVerin = 1;
  }
}

