#include <vidottiequibotlib.h>

// Lettura assi
float letturaY;
float letturaZ;

// Definizione dei pin
#define PWMA 3
#define A01 5
#define A02 4
#define PWMB 9
#define B01 7
#define B02 6

// Oggetti
equibot myEquibot(0);
tb6612fngM motorDx(A01, A02, PWMA);
tb6612fngM motorSx(B01, B02, PWMB);

void aggiornaSensori() {
  myEquibot.mpu_loop_update();
  letturaY = myEquibot.read_AccY();
  letturaZ = myEquibot.read_AccZ();
}

void debugSensori() {
  myEquibot.mpu_loop_update();
  myEquibot.debug_accxyz();
}

void muoviRobot(int velocita, bool avanti) {
  if (avanti) {
    motorDx.Avanti(velocita);
    motorSx.Avanti(velocita);
  } else {
    motorDx.Indietro(velocita);
    motorSx.Indietro(velocita);
  }
}

void controllaEquilibrio(int velocita, float sogliaPos, float sogliaNeg) {
  while (letturaY <= sogliaNeg && letturaZ != 1.0) {
    muoviRobot(velocita, true);
    aggiornaSensori();
  }

  while (letturaY >= sogliaPos && letturaZ != 1.0) {
    muoviRobot(velocita, false);
    aggiornaSensori();
  }
}

int calcolaVelocita(float y) {
  float absY = fabs(y);

  int k = 90;

  if (absY < 0.1) return 0;        // Niente movimento se in equilibrio
  else if (absY < 0.2) return (20 + k);
  else if (absY < 0.3) return (30 + k);
  else if (absY < 0.4) return (40 + k);
  else if (absY < 0.5) return (50 + k);
  else if (absY < 0.6) return (60 + k);
  else if (absY < 0.7) return (70 + k);
  else if (absY < 0.8) return (80 + k);
  else if (absY < 0.9) return (90 + k);
  else return (100 + k);
}

void controlloEquilibrioDinamico() {
  aggiornaSensori();

  if (letturaZ == 1.0) return;

  int velocita = calcolaVelocita(letturaY);

  if (letturaY <= -0.1) {
    muoviRobot(velocita, true);  // avanti
  } else if (letturaY >= 0.1) {
    muoviRobot(velocita, false); // indietro
  } else {
    muoviRobot(0, true); // fermo
  }
}

void setup() {
  myEquibot.ebot_setup();
  motorDx.tb6612fngM_setup();
  motorSx.tb6612fngM_setup();
}

void loop() {
  controlloEquilibrioDinamico();
}
