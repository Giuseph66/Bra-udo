#include <Stepper.h>

const int stepsPerRevolution = 2048;  // O motor 28BYJ-48 tem 2048 passos por rotação completa.

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Conexão com os pinos 8, 9, 10, 11 do Arduino

void setup() {
  myStepper.setSpeed(10);  // Define a velocidade do motor
  Serial.begin(9600);
}

void loop() {
  int maxSteps = 500;  // Definir o número máximo de passos antes de parar para checagem
  int currentSteps = 0;

  while (currentSteps < maxSteps) {
    myStepper.step(1);  // Movimenta o motor passo a passo
    currentSteps++;

    // Aqui você pode checar se alguma condição de travamento pode ter ocorrido
    // Por exemplo, um sensor, ou mesmo verificar se o sistema está travado de outra forma
  }

  Serial.println("Motor pausado para evitar sobrecarga");
  delay(2000);  // Pausa de 2 segundos antes de reiniciar
  currentSteps = 0;  // Reinicia a contagem de passos
}


#include <Stepper.h>

const int stepsPerRevolution = 2048;  // O motor 28BYJ-48 tem 2048 passos por rotação completa.

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Conecte os pinos 8, 9, 10, 11

void setup() {
  // Define a velocidade em RPM
  myStepper.setSpeed(10);  // 10 RPM
  Serial.begin(9600);
}

void loop() {
  // Gira uma volta completa no sentido horário
  Serial.println("Girando no sentido horário...");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Gira uma volta completa no sentido anti-horário
  Serial.println("Girando no sentido anti-horário...");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
