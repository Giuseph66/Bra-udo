// Definindo uma estrutura para armazenar os pinos de cada motor
struct MotorPins {
  int pin_senti;   // Pino para controle de sentido
  int pin_senti_2; // Segundo pino de controle de sentido (apenas para Motor 2)
  int pin_control; // Pino para controle de velocidade (PWM)
  int pin_control_2; // Segundo pino de controle de velocidade (apenas para Motor 2)
  int enPin;       // Pino para enable do motor
};

// Criando um array de structs para armazenar os pinos dos motores
MotorPins motorPins[] = {
  {46, -1, 44, -1, 42},   // Motor 1 (Motor X_Y)
  {52, 53, 50, 51, 48},   // Motor 2 (Motor Duplo)
  {47, -1, 45, -1, 43},   // Motor 3 (Motor Redutor)
  {40, -1, 38, -1, 36},   // Motor 4 (Motor Garra)
  {41, -1, 39, -1, 37}    // Motor 5 (Motor 360)
};

void setup() {
  // Inicializa a comunicação serial para depuração
  Serial.begin(115200);

  // Configurar todos os pinos como saídas
  for (int i = 0; i < 5; i++) {
    pinMode(motorPins[i].pin_senti, OUTPUT);
    if (motorPins[i].pin_senti_2 != -1) pinMode(motorPins[i].pin_senti_2, OUTPUT);  // Para motores com segundo pino de sentido
    pinMode(motorPins[i].pin_control, OUTPUT);
    if (motorPins[i].pin_control_2 != -1) pinMode(motorPins[i].pin_control_2, OUTPUT);  // Para motores com segundo pino de controle
    pinMode(motorPins[i].enPin, OUTPUT);
  }

  Serial.println("Pinos configurados e prontos.");
}

void loop() {
  // Simulando a recepção de um comando para mover o motor 2
  int motorComando = 2; // Exemplo: Recebemos o comando para mover o Motor 2

  if (motorComando == 2) {
    // Usar a função especial para o Motor 2 (Motor Duplo)
    gira_2_motor_base(motorPins[1].pin_senti, motorPins[1].pin_senti_2, true, motorPins[1].pin_control, motorPins[1].pin_control_2, 500, 10);  // Exemplo de movimento
  } else {
    // Controlar os outros motores normalmente
    moverMotor(motorComando, HIGH, 200);  // Exemplo de movimento
    delay(2000); // Espera de 2 segundos
    moverMotor(motorComando, LOW, 0);    // Para o motor
    delay(1000); // Espera de 1 segundo
  }
}

// Função para mover o motor 1, 3, 4 ou 5 (controle simples)
void moverMotor(int motor, int sentido, int velocidade) {
  // Verifica se o número do motor está no intervalo permitido
  if (motor >= 1 && motor <= 5 && motor != 2) {
    int index = motor - 1; // Ajusta o índice do array (1 -> 0, 2 -> 1, ...)

    // Controla o sentido do motor
    digitalWrite(motorPins[index].pin_senti, sentido);

    // Define a velocidade do motor (usando PWM no pino de controle)
    analogWrite(motorPins[index].pin_control, velocidade);

    // Ativa o motor
    digitalWrite(motorPins[index].enPin, HIGH);

    // Exibe informações no serial para depuração
    Serial.print("Movendo Motor ");
    Serial.print(motor);
    Serial.print(" - Sentido: ");
    Serial.print(sentido == HIGH ? "Frente" : "Reverso");
    Serial.print(" - Velocidade: ");
    Serial.println(velocidade);
  } else {
    Serial.println("Erro: Número do motor inválido!");
  }
}

// Função para mover o Motor 2 (Motor Duplo)
void gira_2_motor_base(int pin_sentido, int pin_sentido_2, bool pin_sentido_lado, int pin_controle, int pin_controle_2, int vel_rotacao, int qnt_rotacao) {
  // Controla o sentido
  digitalWrite(pin_sentido, pin_sentido_lado);
  if (pin_sentido_lado == 1) {
    pin_sentido_lado = 0;
  } else {
    pin_sentido_lado = 1;
  }
  digitalWrite(pin_sentido_2, pin_sentido_lado);

  // Controla as rotações
  for (int i = 0; i < qnt_rotacao; i++) {
    digitalWrite(pin_controle, HIGH);
    digitalWrite(pin_controle_2, HIGH);
    delayMicroseconds(vel_rotacao);
    digitalWrite(pin_controle, LOW);
    digitalWrite(pin_controle_2, LOW);
    delayMicroseconds(vel_rotacao);
  }

  // Exibe informações no serial para depuração
  Serial.println("Movendo Motor 2 (Motor Duplo) com função especial.");
}
