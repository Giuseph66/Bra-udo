//1 sentido D_E
int Pin_senti_46 = 46;
int Pin_control_44 = 44;
int enPin_42 = 42;

//2 duplo
int Pin_senti_53 = 53;
int Pin_control_51 = 51;
int enPin_49 = 49;

int Pin_senti_52 = 52;
int Pin_control_50 = 50;
int enPin_48 = 48;

// 2 motor
int Pin_senti_47 = 47;
int Pin_control_45 = 45;
int enPin_43 = 43;

// 3 motor
int Pin_senti_40 = 40;
int Pin_control_38 = 38;
int enPin_36 = 36;

// 4 motor
int Pin_senti_41 = 41;
int Pin_control_39 = 39;
int enPin_37 = 37;

// 5 motor
int Pin_senti_34 = 34;
int Pin_control_32 = 32;
int enPin_30 = 30;

int qnt = 500;              
int Velocidade = 200;         

void setup() {
  Serial.begin(9600);       // Comunicação com o Monitor Serial
  Serial1.begin(9600);     
  Serial.println("");
  Serial.print("Conectado >..");
  //1 conjunto
  pinMode(Pin_control_50, OUTPUT);
  pinMode(Pin_senti_52, OUTPUT);
  pinMode(enPin_48, OUTPUT);
  digitalWrite(enPin_48, LOW); 
  pinMode(Pin_control_51, OUTPUT);
  pinMode(Pin_senti_53, OUTPUT);
  pinMode(enPin_49, OUTPUT);
  digitalWrite(enPin_49, LOW); 
  
  //2 conjunto D_E
  pinMode(Pin_senti_46, OUTPUT);
  pinMode(Pin_control_44, OUTPUT);
  pinMode(enPin_42, OUTPUT);
  digitalWrite(enPin_42, LOW); 

  //2 motor
  pinMode(Pin_senti_47, OUTPUT);
  pinMode(Pin_control_45, OUTPUT);
  pinMode(enPin_43, OUTPUT);
  digitalWrite(enPin_43, LOW); 
  
  //3 motor
  pinMode(Pin_senti_40, OUTPUT);
  pinMode(Pin_control_38, OUTPUT);
  pinMode(enPin_36, OUTPUT);
  digitalWrite(enPin_36, LOW); 
  
  //4 motor
  pinMode(Pin_senti_41, OUTPUT);
  pinMode(Pin_control_39, OUTPUT);
  pinMode(enPin_37, OUTPUT);
  digitalWrite(enPin_37, LOW); 
  
  //5 motor
  pinMode(Pin_senti_34, OUTPUT);
  pinMode(Pin_control_32, OUTPUT);
  pinMode(enPin_30, OUTPUT);
  digitalWrite(enPin_30, LOW);
  Serial.println("Arduino Mega pronto para receber dados do ESP8266...");
}

void loop() {
  // Verifica se há dados disponíveis para leitura na Serial1 (comunicação com o ESP8266)
  if (Serial1.available()) {
  String data = Serial1.readStringUntil('\n');
  Serial.print("Dados lidos: ");
  Serial.println(data);

  if (data.length() > 1) { // Verifica se os dados lidos têm um comprimento mínimo esperado
    int firstComma = data.indexOf(',');
    if (firstComma != -1) {
      int pin_sentido = data.substring(0, firstComma).toInt();
      data = data.substring(firstComma + 1);
      
      int secondComma = data.indexOf(',');
      int pin_sentido_lado = data.substring(0, secondComma).toInt();
      data = data.substring(secondComma + 1);

      int thirdComma = data.indexOf(',');
      int pin_controle = data.substring(0, thirdComma).toInt();
      data = data.substring(thirdComma + 1);

      int fourthComma = data.indexOf(',');
      int vel_rotacao = data.substring(0, fourthComma).toInt();
      int qnt_rotacao = data.substring(fourthComma + 1).toInt();

      Serial.println("Valores recebidos do ESP8266:");
      Serial.print("Pin Sentido: ");
      Serial.println(pin_sentido);
      Serial.print("Sentido Lado: ");
      Serial.println(pin_sentido_lado);
      Serial.print("Pin Controle: ");
      Serial.println(pin_controle);
      Serial.print("Velocidade de Rotação: ");
      Serial.println(vel_rotacao);
      Serial.print("Quantidade de Rotações: ");
      Serial.println(qnt_rotacao);
    }
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