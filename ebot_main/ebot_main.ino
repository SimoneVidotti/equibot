#include <vidottiequibotlib.h>

// Definizione dei pin motori
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

// PID
float targetAngle = 0.0;
float error, prevError = 0, integral = 0;
float Kp = 50;
float Ki = 0.5;
float Kd = 0.8;

void setup() {
  myEquibot.ebot_setup();
  motorDx.tb6612fngM_setup();
  motorSx.tb6612fngM_setup();
}

void setMotori(int velocita) {
  velocita = constrain(velocita, -255, 255);
  if (velocita > 0) {
    motorDx.Avanti(velocita);
    motorSx.Avanti(velocita);
  } else if (velocita < 0) {
    motorDx.Indietro(-velocita);
    motorSx.Indietro(-velocita);
  } else {
    motorDx.Fermo();
    motorSx.Fermo();
  }
}

void loop() {
  myEquibot.mpu_loop_update();
  float angolo = myEquibot.getAngle();

  // PID
  error = angolo - targetAngle;
  integral += error * myEquibot.dt;
  float derivative = (error - prevError) / myEquibot.dt;
  prevError = error;

  float output = Kp * error + Ki * integral + Kd * derivative;

  setMotori((int)output);
  delay(5); // campionamento 5ms
}
