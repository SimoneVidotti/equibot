#include <vidottiequibotlib.h>

// Definizione dei pin
#define PWMA 3   // Pin PWM per il controllo della velocità
#define A01 5   // Pin di direzione 1
#define A02 4   // Pin di direzione 2
#define PWMB 9   // Pin PWM per il controllo della velocità
#define B01 7   // Pin di direzione 1
#define B02 6   // Pin di direzione 2

equibot Myequibot(0);
tb6612fngM MotorDx(A01, A02, PWMA);
tb6612fngM MotorSx(B01, B02, PWMB);

void setup() {
  MotorDx.tb6612fngM_setup();
  MotorSx.tb6612fngM_setup();
}

void loop() {
  MotorDx.Avanti();
  MotorSx.Avanti();
  delay(2000);
  MotorSx.Indietro();
  MotorDx.Indietro();
  delay(2000);
}
