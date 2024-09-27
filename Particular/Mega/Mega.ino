
// Motor 1 (Motor X_Y)
const int Pin_senti_46 = 46;
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

void setup() {
  Serial.begin(9600);       // Comunicação com o Monitor Serial
  Serial1.begin(9600);      // Comunicação com o ESP8266
  Serial.println("Arduino Mega pronto para receber dados do ESP8266...");

  // Configuração dos pinos dos motores
  // Motor 1
  pinMode(Pin_senti_46, OUTPUT);
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
  digitalWrite(enPin_37, LOW);
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
      //processTestCommand(jsonData);
    } else if (data.startsWith("COMANDO:")) {
      // Comando geral
      String jsonData = data.substring(8); // Remove "COMANDO:"
      Serial.println(jsonData);

      //processGeneralCommand(jsonData);
    } else {
      Serial.println("Comando desconhecido.");
    }
  }
}

    //lado_d_e(pin_sentido,1,pin_controle,vel_rotacao,qnt_rotacao);
    //gira_motor(Pin_senti_52,1,Pin_control_50,1000,10000);
  //gira_2_motor_base(Pin_senti_52,Pin_senti_53,1,Pin_control_50,Pin_control_51,350,10000);


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
void lado_d_e(int pin_sentido, char direita_esquerda, int pin_controle, int vel_rotacao, int qnt_rotacao) {
  bool pin_sentido_lado = 0;
  if (direita_esquerda == 'd') {
    pin_sentido_lado = 0;
  } else if (direita_esquerda == 'e') { 
    pin_sentido_lado = 1;
  }
  digitalWrite(pin_sentido, pin_sentido_lado);
  
  for (int i = 0; i < qnt_rotacao; i++) {
    digitalWrite(pin_controle, HIGH);
    delayMicroseconds(vel_rotacao);
    digitalWrite(pin_controle, LOW);
    delayMicroseconds(vel_rotacao);
  }
}
void mexe_todos(int pin_sentido_j_1, int pin_sentido_j_2,int pin_sentido_1, int pin_sentido_2,int pin_sentido_3, int pin_sentido_4,int pin_sentido_5,
                int pin_controle_j_1, int pin_controle_j_2, int pin_controle_1, int pin_controle_2, int pin_controle_3, int pin_controle_4, int pin_controle_5,
                bool pin_sentido_lado_j_1_2,char pin_sentido_lado_1 ,bool pin_sentido_lado_2 ,bool pin_sentido_lado_3 ,bool pin_sentido_lado_4 ,bool pin_sentido_lado_5,
                int vel_rotacao_j_1_2 ,int vel_rotacao_1,int vel_rotacao_2,int vel_rotacao_3,int vel_rotacao_4,int vel_rotacao_5,
                int qnt_rotacao_j_1_2 ,int qnt_rotacao_1,int qnt_rotacao_2,int qnt_rotacao_3,int qnt_rotacao_4,int qnt_rotacao_5){
  digitalWrite(pin_sentido_j_1, pin_sentido_lado_j_1_2);
  if (pin_sentido_lado_j_1_2 == 1) {
    pin_sentido_lado_j_1_2 = 0;
  } else {
    pin_sentido_lado_j_1_2 = 1;
  }
  digitalWrite(pin_sentido_j_2, pin_sentido_lado_j_1_2);

  bool pin_sentido_lado_base = 0;
  if (pin_sentido_lado_1 == 'd') {
    pin_sentido_lado_base = 0;
  } else if (pin_sentido_lado_1 == 'e') { 
    pin_sentido_lado_base = 1;
  }
  digitalWrite(pin_sentido_1, pin_sentido_lado_base);
  
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