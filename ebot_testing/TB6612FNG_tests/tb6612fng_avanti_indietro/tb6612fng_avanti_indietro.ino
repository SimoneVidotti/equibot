// Definizione dei pin
#define PWMA 3   // Pin PWM per il controllo della velocità
#define A01 5   // Pin di direzione 1
#define A02 4   // Pin di direzione 2
#define STBY 6   // Pin standby per attivare il motore11111
void setup() {
  // Inizializzazione dei pin
  pinMode(PWMA, OUTPUT);
  pinMode(A01, OUTPUT);
  pinMode(A02, OUTPUT);
  pinMode(STBY, OUTPUT);

  // Impostiamo STBY a HIGH per attivare il motore
  digitalWrite(STBY, HIGH);
}

void loop() {
  // Movimento in avanti
  digitalWrite(A01, HIGH);  // Direzione avanti
  digitalWrite(A02, LOW);
  analogWrite(PWMA, 255);    // Velocità massima

  delay(2000);  // Motore in avanti per 2 secondi

  // Fermare il motore
  analogWrite(PWMA, 0);     // Spegnere il motore
  delay(1000);  // Pausa di 1 secondo

  // Movimento indietro
  digitalWrite(A01, LOW);   // Direzione indietro
  digitalWrite(A02, HIGH);
  analogWrite(PWMA, 255);    // Velocità massima

  delay(2000);  // Motore indietro per 2 secondi

  // Fermare il motore
  analogWrite(PWMA, 0);     // Spegnere il motore
  delay(1000);  // Pausa di 1 secondo
}
