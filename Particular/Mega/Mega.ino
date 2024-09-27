
// Motor 1 (Motor X_Y)
/*const int Pin_senti_46 = 46;
const int Pin_control_44 = 44;
const int enPin_42 = 42;

// Motor 2 (Motor Duplo)
const int Pin_senti_52 = 52;
const int Pin_control_50 = 50;
const int enPin_48 = 48;

const int Pin_senti_53 = 53;
const int Pin_control_51 = 51;
const int enPin_49 = 49;

// Motor 3 (Motor Redutor)
const int Pin_senti_47 = 47;
const int Pin_control_45 = 45;
const int enPin_43 = 43;

// Motor 4 (Motor Garra)
const int Pin_senti_40 = 40;
const int Pin_control_38 = 38;
const int enPin_36 = 36;

// Motor 5 (Motor 360)
const int Pin_senti_41 = 41;
const int Pin_control_39 = 39;
const int enPin_37 = 37; 
*/
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
struct MotorData {
  int motor ;
  int value_vel;   // Velocidade
  int value;       // Rotação
  String sentido;  // Sentido (Direita ou Esquerda)
};

// Lista de structs para armazenar os dados de até 5 motores
MotorData motorList[5];

void setup() {
  Serial.begin(9600);       // Comunicação com o Monitor Serial
  Serial1.begin(9600);      // Comunicação com o ESP8266
  Serial.println("Arduino Mega pronto para receber dados do ESP8266...");

  // Configuração dos pinos dos motores
  // Motor 1
  /*pinMode(Pin_senti_46, OUTPUT);
  pinMode(Pin_control_44, OUTPUT);
  pinMode(enPin_42, OUTPUT);
  digitalWrite(enPin_42, LOW);

  // Motor 2
  pinMode(Pin_senti_52, OUTPUT);
  pinMode(Pin_control_50, OUTPUT);
  pinMode(enPin_48, OUTPUT);
  digitalWrite(enPin_48, LOW);

  pinMode(Pin_senti_53, OUTPUT);
  pinMode(Pin_control_51, OUTPUT);
  pinMode(enPin_49, OUTPUT);
  digitalWrite(enPin_49, LOW);

  // Motor 3
  pinMode(Pin_senti_47, OUTPUT);
  pinMode(Pin_control_45, OUTPUT);
  pinMode(enPin_43, OUTPUT);
  digitalWrite(enPin_43, LOW);

  // Motor 4
  pinMode(Pin_senti_40, OUTPUT);
  pinMode(Pin_control_38, OUTPUT);
  pinMode(enPin_36, OUTPUT);
  digitalWrite(enPin_36, LOW);

  // Motor 5
  pinMode(Pin_senti_41, OUTPUT);
  pinMode(Pin_control_39, OUTPUT);
  pinMode(enPin_37, OUTPUT);
  digitalWrite(enPin_37, LOW);*/
  
  for (int i = 0; i < 5; i++) {
    pinMode(motorPins[i].pin_senti, OUTPUT);
    if (motorPins[i].pin_senti_2 != -1) pinMode(motorPins[i].pin_senti_2, OUTPUT);  // Para motores com segundo pino de sentido
    pinMode(motorPins[i].pin_control, OUTPUT);
    if (motorPins[i].pin_control_2 != -1) pinMode(motorPins[i].pin_control_2, OUTPUT);  // Para motores com segundo pino de controle
    pinMode(motorPins[i].enPin, OUTPUT);
    digitalWrite(motorPins[i].enPin, LOW);
  }
    pinMode(49, OUTPUT);
    digitalWrite(49, LOW);
}

void loop() {
  // Verifica se há dados disponíveis para leitura na Serial1 (comunicação com o ESP8266)
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    data.trim(); // Remove espaços em branco no início e no fim
    Serial.print("Dados lidos: ");
    Serial.println(data);

    if (data.startsWith("TESTE:")) {
      // Comando de teste
      String jsonData = data.substring(6); // Remove "TESTE:"
      Serial.println(jsonData);
      Serial.println("");
      
      processJsonData(jsonData);

      printMotorList();
      int atual_motor= motorList[0].motor;
      if (atual_motor==2){
          gira_2_motor_base(motorPins[1].pin_senti, motorPins[1].pin_senti_2, motorList[0].sentido, motorPins[1].pin_control, motorPins[1].pin_control_2,motorList[0].value_vel,motorList[0].value);  // Exemplo de movimento
  
      }else{
        gira_motor(motorPins[atual_motor].pin_senti,motorList[0].sentido,motorPins[atual_motor].pin_control,motorList[0].value_vel,motorList[0].value);
      }
    } else if (data.startsWith("COMANDO:")) {
      // Comando geral
      String jsonData = data.substring(8); 
      Serial.println(jsonData);
      Serial.println("");
      
      processJsonData(jsonData);

      printMotorList();
      mexe_todos(motorPins[1].pin_senti, motorPins[1].pin_senti_2,motorPins[0].pin_senti, motorPins[2].pin_senti,motorPins[3].pin_senti,motorPins[4].pin_senti,motorPins[5].pin_senti,
                 motorPins[1].pin_control, motorPins[1].pin_control_2, motorPins[0].pin_control, motorPins[2].pin_control,  motorPins[3].pin_control, motorPins[4].pin_control, motorPins[5].pin_control,
                motorList[1].sentido,motorList[0].sentido ,motorList[2].sentido ,motorList[3].sentido ,motorList[4].sentido ,motorList[5].sentido,
                motorList[1].value_vel,motorList[0].value_vel ,motorList[2].value_vel ,motorList[3].value_vel ,motorList[4].value_vel ,motorList[5].value_vel,
                motorList[1].value,motorList[0].value ,motorList[2].value ,motorList[3].value ,motorList[4].value ,motorList[5].value);
    } else {
      Serial.println("Comando desconhecido.");
    }
  }
}

  //gira_2_motor_base(Pin_senti_52,Pin_senti_53,1,Pin_control_50,Pin_control_51,350,10000);


void processJsonData(String jsonData) {
  // Variáveis temporárias para armazenar dados de cada motor
  int cont=0;
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
    int lado =0;  

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
        if (sentido[0]=="D"){
          lado=1;
        }
        i = end; // Avança o índice

        // Armazena os dados do motor na lista de structs
        motorList[cont].value_vel = value_vel;
        motorList[cont].value = value;
        motorList[cont].sentido = lado;
        motorList[cont].motor = motorNumber;
        cont=cont+1;
        // Reset para o próximo motor
        insideMotor = false;
      }
    }
  }
  Serial.println("Processamento concluído.\n");
}
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
void gira_motor(int pin_sentido, bool pin_sentido_lado , int pin_controle, int vel_rotacao, int qnt_rotacao){
  digitalWrite(pin_sentido, pin_sentido_lado);
  for (int i = 0; i < qnt_rotacao; i++) {
    digitalWrite(pin_controle, HIGH);
    delayMicroseconds(vel_rotacao);
    digitalWrite(pin_controle, LOW);
    delayMicroseconds(vel_rotacao);
  }
}
void gira_2_motor_base(int pin_sentido, int pin_sentido_2, bool pin_sentido_lado , int pin_controle, int pin_controle_2, int vel_rotacao, int qnt_rotacao){
  digitalWrite(pin_sentido, pin_sentido_lado);
  if (pin_sentido_lado == 1) {
    pin_sentido_lado = 0;
  } else {
    pin_sentido_lado = 1;
  }
  digitalWrite(pin_sentido_2, pin_sentido_lado);
  for (int i = 0; i < qnt_rotacao; i++) {
    digitalWrite(pin_controle, HIGH);
    digitalWrite(pin_controle_2, HIGH);
    delayMicroseconds(vel_rotacao);
    digitalWrite(pin_controle, LOW);
    digitalWrite(pin_controle_2, LOW);
    delayMicroseconds(vel_rotacao);
  }
}
void mexe_todos(int pin_sentido_j_1, int pin_sentido_j_2,int pin_sentido_1, int pin_sentido_2,int pin_sentido_3, int pin_sentido_4,int pin_sentido_5,
                int pin_controle_j_1, int pin_controle_j_2, int pin_controle_1, int pin_controle_2, int pin_controle_3, int pin_controle_4, int pin_controle_5,
                bool pin_sentido_lado_j_1_2,bool pin_sentido_lado_1 ,bool pin_sentido_lado_2 ,bool pin_sentido_lado_3 ,bool pin_sentido_lado_4 ,bool pin_sentido_lado_5,
                int vel_rotacao_j_1_2 ,int vel_rotacao_1,int vel_rotacao_2,int vel_rotacao_3,int vel_rotacao_4,int vel_rotacao_5,
                int qnt_rotacao_j_1_2 ,int qnt_rotacao_1,int qnt_rotacao_2,int qnt_rotacao_3,int qnt_rotacao_4,int qnt_rotacao_5){
  digitalWrite(pin_sentido_j_1, pin_sentido_lado_j_1_2);
  if (pin_sentido_lado_j_1_2 == 1) {
    pin_sentido_lado_j_1_2 = 0;
  } else {
    pin_sentido_lado_j_1_2 = 1;
  }
  digitalWrite(pin_sentido_j_2, pin_sentido_lado_j_1_2);

  digitalWrite(pin_sentido_1, pin_sentido_lado_1);
  digitalWrite(pin_sentido_2, pin_sentido_lado_2);
  digitalWrite(pin_sentido_3, pin_sentido_lado_3);
  digitalWrite(pin_sentido_4, pin_sentido_lado_4);
  digitalWrite(pin_sentido_5, pin_sentido_lado_5);
  int valores[] = {qnt_rotacao_j_1_2, qnt_rotacao_1, qnt_rotacao_2, qnt_rotacao_3, qnt_rotacao_4, qnt_rotacao_5};
  int maior_qnt_rotacao = valores[0];
  for(int i = 1; i < 6; i++) {if(valores[i] > maior_qnt_rotacao) {maior_qnt_rotacao = valores[i];}}
  for (int i = 0; i < maior_qnt_rotacao; i++) {
    if (qnt_rotacao_j_1_2>i){
      digitalWrite(pin_controle_j_1, HIGH);
      digitalWrite(pin_controle_j_2, HIGH);
      delayMicroseconds(vel_rotacao_j_1_2);
      digitalWrite(pin_controle_j_1, LOW);
      digitalWrite(pin_controle_j_2, LOW);
      delayMicroseconds(vel_rotacao_j_1_2);
    }

    if (qnt_rotacao_1>i){
      digitalWrite(pin_controle_1, HIGH);
      delayMicroseconds(vel_rotacao_1);
      digitalWrite(pin_controle_1, LOW);
      delayMicroseconds(vel_rotacao_1);
    }

    if (qnt_rotacao_2>i){
      digitalWrite(pin_controle_2, HIGH);
      delayMicroseconds(vel_rotacao_2);
      digitalWrite(pin_controle_2, LOW);
      delayMicroseconds(vel_rotacao_2);
    }

    if (qnt_rotacao_3>i){
      digitalWrite(pin_controle_3, HIGH);
      delayMicroseconds(vel_rotacao_3);
      digitalWrite(pin_controle_3, LOW);
      delayMicroseconds(vel_rotacao_3);
    }

    if (qnt_rotacao_4>i){
      digitalWrite(pin_controle_4, HIGH);
      delayMicroseconds(vel_rotacao_4);
      digitalWrite(pin_controle_4, LOW);
      delayMicroseconds(vel_rotacao_4);
    }
    
    if (qnt_rotacao_5>i){
      digitalWrite(pin_controle_5, HIGH);
      delayMicroseconds(vel_rotacao_5);
      digitalWrite(pin_controle_5, LOW);
      delayMicroseconds(vel_rotacao_5);
    }
  }
}