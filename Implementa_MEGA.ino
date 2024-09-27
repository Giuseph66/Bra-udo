
struct MotorData {
  int value_vel;   // Velocidade
  int value;       // Rotação
  String sentido;  // Sentido (Direita ou Esquerda)
};

// Lista de structs para armazenar os dados de até 5 motores
MotorData motorList[5];

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  Serial.println("Esperando dados JSON...");
}

void loop() {
  if (Serial.available()) {
    // Lê os dados da serial como uma string
    String jsonData = Serial.readStringUntil('\n');

    // Processa os dados lidos (filtra o JSON manualmente)
    processJsonData(jsonData);

    // Exibe os dados salvos na lista
    printMotorList();
  }
}

void processJsonData(String jsonData) {
  // Variáveis temporárias para armazenar dados de cada motor
  int motorNumber = 0;
  int value_vel = 0;
  int value = 0;
  String sentido = "";

  // Verifica se estamos lendo um motor específico
  bool insideMotor = false;

  // Percorre a string de dados JSON manualmente
  for (int i = 0; i < jsonData.length(); i++) {
    // Detecta o início de um objeto de motor
    if (jsonData.substring(i, i + 6) == "\"motor") {
      motorNumber = jsonData.charAt(i + 6) - '0'; // Extrai o número do motor
      insideMotor = true;
      i += 7; // Avança o índice
    }

    if (insideMotor) {
      // Extrai o valor de "value_vel"
      if (jsonData.substring(i, i + 10) == "\"value_vel") {
        int start = jsonData.indexOf(":", i) + 1;
        int end = jsonData.indexOf(",", start);
        value_vel = jsonData.substring(start, end).toInt();
        i = end; // Avança o índice
      }

      // Extrai o valor de "value"
      if (jsonData.substring(i, i + 7) == "\"value\"") {
        int start = jsonData.indexOf(":", i) + 1;
        int end = jsonData.indexOf(",", start);
        value = jsonData.substring(start, end).toInt();
        i = end; // Avança o índice
      }

      // Extrai o valor de "sentido"
      if (jsonData.substring(i, i + 9) == "\"sentido\"") {
        int start = jsonData.indexOf(":", i) + 2;
        int end = jsonData.indexOf("\"", start);
        sentido = jsonData.substring(start, end);
        i = end; // Avança o índice

        // Armazena os dados do motor na lista de structs
        motorList[motorNumber - 1].value_vel = value_vel;
        motorList[motorNumber - 1].value = value;
        motorList[motorNumber - 1].sentido = sentido;

        // Reset para o próximo motor
        insideMotor = false;
      }
    }
  }
  Serial.println("Processamento concluído.\n");
}

// Função para exibir os dados da lista de motores
void printMotorList() {
  Serial.println("Lista de Motores:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Motor ");
    Serial.print(i + 1);
    Serial.print(" - Velocidade: ");
    Serial.print(motorList[i].value_vel);
    Serial.print(", Rotacao: ");
    Serial.print(motorList[i].value);
    Serial.print(", Sentido: ");
    Serial.println(motorList[i].sentido);
  }
  Serial.println();
}
