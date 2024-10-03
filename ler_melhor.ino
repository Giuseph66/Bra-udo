unsigned long lastMicrosJ12 = 0;
unsigned long lastMicros1 = 0;
unsigned long lastMicros2 = 0;
unsigned long lastMicros3 = 0;
unsigned long lastMicros4 = 0;

void mexe_todos(int pin_sentido_j_1, int pin_sentido_j_2, int pin_sentido_1, int pin_sentido_2, int pin_sentido_3, int pin_sentido_4,
                int pin_controle_j_1, int pin_controle_j_2, int pin_controle_1, int pin_controle_2, int pin_controle_3, int pin_controle_4,
                String pin_sentido_lado_j_1_2, String pin_sentido_lado_1, String pin_sentido_lado_2, String pin_sentido_lado_3, String pin_sentido_lado_4,
                int vel_rotacao_j_1_2, int vel_rotacao_1, int vel_rotacao_2, int vel_rotacao_3, int vel_rotacao_4,
                int qnt_rotacao_j_1_2, int qnt_rotacao_1, int qnt_rotacao_2, int qnt_rotacao_3, int qnt_rotacao_4, 
                bool garra_cmc, bool garra_fnl) {

    // Mover a garra para a posição inicial
    Serial.print("Garra - Estado inicial: ");
    Serial.println(garra_cmc);
    mover_garra(garra_cmc);

    // Definir o sentido dos motores
    if (pin_sentido_lado_j_1_2 != "3") {
        digitalWrite(pin_sentido_j_1, (pin_sentido_lado_j_1_2 == "1") ? HIGH : LOW);
        digitalWrite(pin_sentido_j_2, (pin_sentido_lado_j_1_2 == "1") ? LOW : HIGH); // Motor J2 em sentido inverso
    }
    if (pin_sentido_lado_1 != "3") digitalWrite(pin_sentido_1, (pin_sentido_lado_1 == "1") ? HIGH : LOW);
    if (pin_sentido_lado_2 != "3") digitalWrite(pin_sentido_2, (pin_sentido_lado_2 == "1") ? HIGH : LOW);
    if (pin_sentido_lado_3 != "3") digitalWrite(pin_sentido_3, (pin_sentido_lado_3 == "1") ? HIGH : LOW);
    if (pin_sentido_lado_4 != "3") digitalWrite(pin_sentido_4, (pin_sentido_lado_4 == "1") ? HIGH : LOW);

    int maior_qnt_rotacao = max(qnt_rotacao_j_1_2, max(qnt_rotacao_1, max(qnt_rotacao_2, max(qnt_rotacao_3, qnt_rotacao_4))));

    for (int i = 0; i < maior_qnt_rotacao; i++) {
        unsigned long currentMicros = micros();

        // Motor J1/J2
        if (pin_sentido_lado_j_1_2 != "3" && qnt_rotacao_j_1_2 > i && (currentMicros - lastMicrosJ12) >= vel_rotacao_j_1_2) {
            digitalWrite(pin_controle_j_1, HIGH);
            digitalWrite(pin_controle_j_2, HIGH);
            lastMicrosJ12 = currentMicros; // Atualiza o tempo para a próxima iteração
        } else {
            digitalWrite(pin_controle_j_1, LOW);
            digitalWrite(pin_controle_j_2, LOW);
        }

        // Motor 1
        if (pin_sentido_lado_1 != "3" && qnt_rotacao_1 > i && (currentMicros - lastMicros1) >= vel_rotacao_1) {
            digitalWrite(pin_controle_1, HIGH);
            lastMicros1 = currentMicros;
        } else {
            digitalWrite(pin_controle_1, LOW);
        }

        // Motor 2
        if (pin_sentido_lado_2 != "3" && qnt_rotacao_2 > i && (currentMicros - lastMicros2) >= vel_rotacao_2) {
            digitalWrite(pin_controle_2, HIGH);
            lastMicros2 = currentMicros;
        } else {
            digitalWrite(pin_controle_2, LOW);
        }

        // Motor 3
        if (pin_sentido_lado_3 != "3" && qnt_rotacao_3 > i && (currentMicros - lastMicros3) >= vel_rotacao_3) {
            digitalWrite(pin_controle_3, HIGH);
            lastMicros3 = currentMicros;
        } else {
            digitalWrite(pin_controle_3, LOW);
        }

        // Motor 4
        if (pin_sentido_lado_4 != "3" && qnt_rotacao_4 > i && (currentMicros - lastMicros4) >= vel_rotacao_4) {
            digitalWrite(pin_controle_4, HIGH);
            lastMicros4 = currentMicros;
        } else {
            digitalWrite(pin_controle_4, LOW);
        }
    }

    // Mover a garra para a posição final
    Serial.print("Garra - Estado final: ");
    Serial.println(garra_fnl);
    mover_garra(garra_fnl);
}

void mover_garra(bool depende){
  if(depende){
    servoMotor.write(120); 
  }else{
    servoMotor.write(0); 
  }             
}
