#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

// Defina as credenciais do Wi-Fi
const char* ssid = "Esp";
const char* password = "12345678";

// Comunicação Serial com o Arduino Mega
SoftwareSerial megaSerial(5, 4); // Pinos D5 e D6 (RX e TX do ESP)

// Inicialize o servidor na porta 80
ESP8266WebServer server(80);

// Função para servir o HTML
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controle de Motor</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #f4f4f4;
            margin: 0;
        }
        .container {
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
        }
        input[type="number"], select {
            width: 100%;
            padding: 8px;
            margin-bottom: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        button {
            padding: 10px 20px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background-color: #0056b3;
        }
    </style>
</head>
<body>

<div class="container">
    <h2>Controle de Motor</h2>
    <form id="motorControlForm">
        <label for="pin_sentido">Pin Sentido</label>
        <input type="number" id="pin_sentido" name="pin_sentido" min="0" required>

        <label for="pin_sentido_lado">Sentido (Lado)</label>
        <select id="pin_sentido_lado" name="pin_sentido_lado" required>
            <option value="1">Direita</option>
            <option value="0">Esquerda</option>
        </select>

        <label for="pin_controle">Pin Controle</label>
        <input type="number" id="pin_controle" name="pin_controle" min="0" required>

        <label for="vel_rotacao">Velocidade de Rotação (µs)</label>
        <input type="number" id="vel_rotacao" name="vel_rotacao" min="0" required>

        <label for="qnt_rotacao">Quantidade de Rotações</label>
        <input type="number" id="qnt_rotacao" name="qnt_rotacao" min="0" required>

        <button type="submit">Enviar</button>
    </form>

    <p id="status"></p>
</div>

<script>
    document.getElementById('motorControlForm').addEventListener('submit', function (e) {
        e.preventDefault();

        // Captura os valores do formulário
        const pin_sentido = document.getElementById('pin_sentido').value;
        const pin_sentido_lado = document.getElementById('pin_sentido_lado').value;
        const pin_controle = document.getElementById('pin_controle').value;
        const vel_rotacao = document.getElementById('vel_rotacao').value;
        const qnt_rotacao = document.getElementById('qnt_rotacao').value;

        // Monta a URL de solicitação para enviar ao ESP8266
        const url = `/setMotor?pin_sentido=${pin_sentido}&pin_sentido_lado=${pin_sentido_lado}&pin_controle=${pin_controle}&vel_rotacao=${vel_rotacao}&qnt_rotacao=${qnt_rotacao}`;

        // Envia os dados para o ESP8266
        fetch(url)
            .then(response => response.text())
            .then(data => {
                document.getElementById('status').textContent = "Comando enviado com sucesso!";
            })
            .catch(error => {
                document.getElementById('status').textContent = "Erro ao enviar comando!";
            });
    });
</script>

</body>
</html>
)rawliteral";

// Função para processar a requisição HTTP GET e repassar ao Mega// Função para processar a requisição HTTP GET e repassar ao Mega
void handleSetMotor() {
  if (server.hasArg("pin_sentido") && server.hasArg("pin_sentido_lado") && server.hasArg("pin_controle") && 
      server.hasArg("vel_rotacao") && server.hasArg("qnt_rotacao")) {
      
    String pin_sentido = server.arg("pin_sentido");
    String pin_sentido_lado = server.arg("pin_sentido_lado");
    String pin_controle = server.arg("pin_controle");
    String vel_rotacao = server.arg("vel_rotacao");
    String qnt_rotacao = server.arg("qnt_rotacao");

    // Imprimir os valores recebidos no terminal serial do ESP8266
    Serial.println("Valores recebidos do site:");
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

    // Envia os valores para o Mega via comunicação serial
    megaSerial.print(pin_sentido + ",");
    megaSerial.print(pin_sentido_lado + ",");
    megaSerial.print(pin_controle + ",");
    megaSerial.print(vel_rotacao + ",");
    megaSerial.println(qnt_rotacao);

    // Retorna uma resposta de sucesso para o navegador
    server.send(200, "text/plain", "Comandos enviados ao Mega!");
  } else {
    server.send(400, "text/plain", "Parâmetros faltando!");
  }
}

void setup() {
  Serial.begin(115200);          // Monitor Serial
  megaSerial.begin(9600);        // Comunicação com o Arduino Mega

  // Conecte-se ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Conectando ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado ao WiFi. IP: ");
  Serial.println(WiFi.localIP());

  // Inicia o servidor e define a rota
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });
  
  server.on("/setMotor", handleSetMotor);
  
  server.begin();
  Serial.println("Servidor iniciado.");
}

void loop() {
  server.handleClient();  // Processa solicitações do cliente
}
