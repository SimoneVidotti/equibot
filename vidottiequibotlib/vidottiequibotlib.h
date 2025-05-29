#ifndef VIDOTTIEQUIBOTLIB_H
#define VIDOTTIEQUIBOTLIB_H

// LIBS
#include <MPU6050_tockn.h>
#include <Wire.h>

// init giroscopio
MPU6050 mpu6050(Wire);

// oBjs
class equibot {
    private:
        int c = 0; // stampa remind debug solo 1 volta
        long timer; // Timer debug

    public:
        equibot(long t) : timer(t) { // Costruttore
            // Inizializzazione 
        }
        
        // --- logic ---
        void ebot_setup() {
            Serial.begin(9600); 
            Wire.begin();
            mpu6050.begin();
            mpu6050.calcGyroOffsets(true);
        }

        void mpu_loop_update() {
            mpu6050.update();
        }

        void debug_accxyz() {
            if (c == 0) {
                Serial.println("Controlla i pins in caso di lettura 0...");
                c++;
            }

            if(millis() - timer > 1000) {
                Serial.println("=======================================================");
                Serial.print("accX : "); Serial.print(mpu6050.getAccX());
                Serial.print("\taccY : "); Serial.print(mpu6050.getAccY());
                Serial.print("\taccZ : "); Serial.println(mpu6050.getAccZ());
                timer = millis(); // timer-update
            }
        }

        float read_AccX() {
            return mpu6050.getAccX();
        }

        float read_AccY() {
            return mpu6050.getAccY();
        }

        float read_AccZ() {
            return mpu6050.getAccZ();
        }

        float prevAngle = 0;
        float angle = 0;
        float accAngle = 0;
        float gyroAngle = 0;
        float dt = 0.005;  // 5ms

        float getAngle() {
            accAngle = atan2(mpu6050.getAccY(), mpu6050.getAccZ()) * 180 / PI;
            gyroAngle = mpu6050.getGyroX() * dt;
            angle = 0.98 * (prevAngle + gyroAngle) + 0.02 * accAngle;
            prevAngle = angle;
            return angle;
        }

        // --- fine ---
};

class tb6612fngM {
    private:
        int X01, X02, PWMX; // Motore X pins

        public:
            tb6612fngM(int X1, int X2, int PWm) : X01(X1), X02(X2), PWMX(PWm) {

            }

            void tb6612fngM_setup() {
                // Inizializzazione dei pin
                pinMode(PWMX, OUTPUT);
                pinMode(X01, OUTPUT);
                pinMode(X02, OUTPUT);
            }

            void Avanti(int v) {
                // Movimento in avanti
                digitalWrite(X01, HIGH);  // Direzione avanti
                digitalWrite(X02, LOW);
                analogWrite(PWMX, v);
                //analogWrite(PWMX, 255);    // Velocità massima
            }

            void Indietro(int v) {
                // Movimento indietro
                digitalWrite(X01, LOW);   // Direzione indietro
                digitalWrite(X02, HIGH);
                analogWrite(PWMX, v);
                //analogWrite(PWMX, 255);    // Velocità massima
            }

            void Fermo() {
                analogWrite(PWMX, 0);     // Spegnere il motore
            }
};

#endif
