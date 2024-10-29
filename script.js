
// Função para atualizar o valor e a rotação a partir do slider
function updateValue(motor) {
    const slider = document.getElementById(motor + '-slider');
    const value = parseFloat(slider.value);
    const valueInput = document.getElementById(motor + '-value');
    valueInput.value = value;

    const min = parseFloat(slider.min);
    const max = parseFloat(slider.max);

    let rotation = 0;
    if (max !== min) {
        rotation = ((value - min) / (max - min)) * 180 - 90;
    }

    const line = document.getElementById(motor + '-line');
    line.style.transform = `rotate(${rotation}deg)`;
}

// Função para atualizar o slider e a rotação a partir do input
function updateFromInput(motor) {
    const valueInput = document.getElementById(motor + '-value');
    let value = parseFloat(valueInput.value);
    const slider = document.getElementById(motor + '-slider');

    const min = parseFloat(slider.min);
    const max = parseFloat(slider.max);

    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }

    valueInput.value = value;
    slider.value = value;

    let rotation = 0;
    if (max !== min) {
        rotation = ((value - min) / (max - min)) * 180 - 90;
    }

    const line = document.getElementById(motor + '-line');
    line.style.transform = `rotate(${rotation}deg)`;
}

function updateFromInput_vel(motor) {
    const valueInput = document.getElementById(motor + '-value_vel');
    let value = parseFloat(valueInput.value);

    if (value < 200) {
        value = 200;
    } else if (value > 2500) {
        value = 2500;
    }

    valueInput.value = value;
}

// Função para atualizar o intervalo do slider
function updateRange(motor) {
    const minInput = document.getElementById(motor + '-min');
    const maxInput = document.getElementById(motor + '-max');
    const slider = document.getElementById(motor + '-slider');
    const valueInput = document.getElementById(motor + '-value');

    slider.min = minInput.value;
    slider.max = maxInput.value;

    valueInput.min = minInput.value;
    valueInput.max = maxInput.value;

    let value = parseFloat(valueInput.value);
    const min = parseFloat(slider.min);
    const max = parseFloat(slider.max);

    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }

    valueInput.value = value;
    slider.value = value;

    updateValue(motor);
}

// Função para salvar a configuração atual
function saveConfiguration() {
    const configName = prompt('Digite um nome para a configuração:');
    if (!configName) {
        alert('Nome inválido. Configuração não salva.');
        return;
    }

    // Cria um objeto para armazenar as configurações
    const config = {};

    // Loop através dos 5 motores
    for (let i = 1; i <= 5; i++) {
        const motor = 'motor' + i;

        // Obtém os valores atuais, mínimos e máximos
        const value_vel = parseFloat(document.getElementById(motor + '-value_vel').value);
        const value = parseFloat(document.getElementById(motor + '-value').value);
        const min = parseFloat(document.getElementById(motor + '-min').value);
        const max = parseFloat(document.getElementById(motor + '-max').value);

        // Armazena os valores no objeto de configuração
        config[motor] = {
            value_vel: value_vel,
            value: value,
            min: min,
            max: max
        };
    }

    const inicio = document.getElementById('garra-inicio-select').value;
    const final = document.getElementById('garra-final-select').value;

    config['garra'] = {
        garra_ini: inicio,
        garra_final: final
    };

    // Recupera todas as configurações existentes ou inicia um novo objeto
    const allConfigs = JSON.parse(localStorage.getItem('allMotorConfigurations')) || {};

    // Adiciona a nova configuração
    allConfigs[configName] = config;

    // Salva todas as configurações atualizadas
    localStorage.setItem('allMotorConfigurations', JSON.stringify(allConfigs));

    // Atualiza o menu suspenso
    updateConfigurationsDropdown();

    alert('Configuração "' + configName + '" salva com sucesso!');
}

// Função para carregar a configuração selecionada
function loadSelectedConfiguration() {
    const dropdown = document.getElementById('configurations-dropdown');
    const configName = dropdown.value;

    if (!configName) {
        alert('Por favor, selecione uma configuração.');
        return;
    }

    const allConfigsString = localStorage.getItem('allMotorConfigurations');
    if (allConfigsString) {
        const allConfigs = JSON.parse(allConfigsString);

        if (allConfigs[configName]) {
            const config = allConfigs[configName];

            // Loop através dos motores e aplica os valores
            for (let i = 1; i <= 5; i++) {
                const motor = 'motor' + i;

                if (config[motor]) {
                    const value_vel = config[motor].value_vel;
                    const value = config[motor].value;
                    const min = config[motor].min;
                    const max = config[motor].max;

                    // Atualiza os campos de mínimo e máximo
                    document.getElementById(motor + '-min').value = min;
                    document.getElementById(motor + '-max').value = max;
                    updateRange(motor);

                    // Atualiza o valor atual
                    document.getElementById(motor + '-value_vel').value = value_vel;
                    document.getElementById(motor + '-value').value = value;
                    document.getElementById(motor + '-slider').value = value;
                    updateValue(motor);
                }
            }
            document.getElementById('garra-inicio-select').value = config.garra.garra_ini;
            document.getElementById('garra-final-select').value = config.garra.garra_final;

        } else {
            alert('Configuração não encontrada.');
        }
    } else {
        alert('Nenhuma configuração salva encontrada.');
    }
}

// Função para atualizar o menu suspenso com as configurações salvas
function updateConfigurationsDropdown() {
    const dropdown = document.getElementById('configurations-dropdown');
    dropdown.innerHTML = '<option value="">Selecione uma Configuração</option>';

    const allConfigsString = localStorage.getItem('allMotorConfigurations');
    if (allConfigsString) {
        const allConfigs = JSON.parse(allConfigsString);
        for (const configName in allConfigs) {
            const option = document.createElement('option');
            option.value = configName;
            option.textContent = configName;
            dropdown.appendChild(option);
        }
    }
}

function changeText(element, newText) {
    element.innerHTML = newText;
}

function inverterSinais() {
    for (let i = 1; i <= 5; i++) {
        const motor = 'motor' + i;
        const slider = document.getElementById(motor + '-slider');
        const valueInput = document.getElementById(motor + '-value');

        // Inverte o valor do slider e do campo de entrada
        const currentValue = parseFloat(slider.value);
        const invertedValue = -currentValue;

        slider.value = invertedValue;
        valueInput.value = invertedValue;

        // Atualiza a visualização da rotação
        updateValue(motor);
    }
}

function setGarraInicio() {
    const garraInicioSelect = document.getElementById('garra-inicio-select');
    const garraInicioInput = document.getElementById('garra-inicio');
    garraInicioInput.value = garraInicioSelect.value;
}

// Função para definir o estado de finalização da garra
function setGarraFinal() {
    const garraFinalSelect = document.getElementById('garra-final-select');
    const garraFinalInput = document.getElementById('garra-final');
    garraFinalInput.value = garraFinalSelect.value;
}

function testMotor(motor) {
    const value_vel = parseFloat(document.getElementById(motor + '-value_vel').value);
    const value = parseFloat(document.getElementById(motor + '-value').value);
    let sentido = "Direita";
    if (value < 0) {
        sentido = "Esquerda";
    } else if (value == 0) {
        sentido = "Nao meche";
    }
    const isConfirmed = confirm("Tem certeza que deseja testar o " + motor + "?\n" +
        "Velocidade: " + value_vel + "\n" +
        "Sentido: " + sentido + "\n" +
        "Qntd Rotação: " + Math.abs(value)
    );
    if (isConfirmed) {
        // Criar um objeto com os dados do motor
        let motorData = {};
        motorData[motor] = {
            value_vel: value_vel,
            value: Math.abs(value),
            sentido: sentido
        };

        // Converter o objeto em uma string JSON
        let motorDataString = JSON.stringify(motorData);

        // Enviar os dados para o ESP8266 usando fetch
        fetch('/testMotor', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: motorDataString
        })
            .then(response => response.text())
            .then(data => {
                alert("Comando de teste enviado com sucesso!");
            })
            .catch(error => {
                alert("Erro ao enviar comando de teste!");
                console.error(error);
            });
    } else {
        alert("Teste cancelado.");
    }
}

function testGarra() {
    // Obtém os valores de início e final da garra
    const garraInicioSelect = document.getElementById('garra-inicio-select').value;
    const garraFinalSelect = document.getElementById('garra-final-select').value;

    // Define os textos de estado para o início e final da garra
    let inicioEstado = garraInicioSelect === 'Fechada' ? 'Fechada' : 'Aberta';
    let finalEstado = garraFinalSelect === 'Fechada' ? 'Fechada' : 'Aberta';

    // Confirmação antes de enviar o comando de teste
    const isConfirmed = confirm("Tem certeza que deseja testar a Garra?\n" +
        "Início: " + inicioEstado + "\n" +
        "Final: " + finalEstado
    );

    if (isConfirmed) {
        // Criar um objeto com os dados da garra
        let garraData = {
            inicio: inicioEstado,
            final: finalEstado
        };

        // Converter o objeto em uma string JSON
        let garraDataString = JSON.stringify(garraData);

        // Enviar os dados para o ESP8266 usando fetch
        fetch('/testGarra', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: garraDataString
        })
            .then(response => response.text())
            .then(data => {
                alert("Comando de teste da garra enviado com sucesso!");
            })
            .catch(error => {
                alert("Erro ao enviar comando de teste da garra!");
                console.error(error);
            });
    } else {
        alert("Teste da garra cancelado.");
    }
}

// Declare as variáveis no escopo global
let config = {};
let configString = "";
function Subir_todos() {
    // Resetar as variáveis ao chamar a função
    config = {};
    configString = "";

    // Inicializa o objeto config para os motores
    for (let i = 1; i <= 5; i++) {
        const motor = 'motor' + i;
        const value_vel = parseFloat(document.getElementById(motor + '-value_vel').value);
        const value = parseFloat(document.getElementById(motor + '-value').value);

        let sentido = "Direita";
        if (value < 0) {
            sentido = "Esquerda";
        } else if (value == 0) {
            sentido = "Nao meche";
        }

        config[motor] = {
            value_vel: value_vel,
            value: Math.abs(value),
            sentido: sentido
        };
    }

    // Adicionar o estado da garra ao objeto config
    const garraInicio = document.getElementById('garra-inicio-select').value;
    const garraFinal = document.getElementById('garra-final-select').value;

    config["garra"] = {
        inicio: garraInicio,
        final: garraFinal
    };

    // Construir a string do conteúdo (como antes)
    for (let motor in config) {
        if (motor === "garra") {
            configString += "Garra:\n";
            configString += "  Estado de Início: " + config[motor].inicio + "\n";
            configString += "  Estado de Final: " + config[motor].final + "\n\n";
        } else {
            configString += motor + ":\n";
            configString += "  Velocidade: " + config[motor].value_vel + "\n";
            configString += "  Rotação: " + config[motor].value + "\n";
            configString += "  Sentido: " + config[motor].sentido + "\n\n";
        }
    }

    // Exibir o modal com o conteúdo para visualização
    document.getElementById('modal-text').innerText = configString;

    // Abrir o modal para confirmar o envio
    openModal();
}

// Função para abrir o modal
function openModal() {
    document.getElementById('confirmModal').style.display = 'block';
}

// Função para fechar o modal
function closeModal() {
    document.getElementById('confirmModal').style.display = 'none';
}

// Função para confirmar a ação
document.getElementById('confirmButton').onclick = function () {
    // Converter o objeto config em uma string JSON
    let configJSON = JSON.stringify(config);

    fetch('/setMotor', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: configJSON
    })
        .then(response => response.text())
        .then(data => {
            alert("Comandos enviados com sucesso!");
        })
        .catch(error => {
            alert("Erro ao enviar comandos!");
            console.error(error);
        });
    closeModal(); // Fecha o modal após a confirmação
};

// Chama a função para atualizar o menu suspenso ao carregar a página
window.onload = function () {
    updateConfigurationsDropdown();
};

const commandList = document.getElementById("command-list");
let isLooping = false;

// Função para adicionar um comando à lista
function addCommand() {
    const commandInput = document.getElementById("configurations-dropdown");
    const commandText = commandInput.value.trim();

    if (commandText === "") {
        alert("Digite um comando!");
        return;
    }

    // Cria um novo elemento de comando
    const li = document.createElement("li");
    li.textContent = commandText;

    // Botão para remover o comando da lista
    const removeBtn = document.createElement("button");
    removeBtn.textContent = "Remover";
    removeBtn.onclick = () => li.remove();
    li.appendChild(removeBtn);

    // Botões para mover para cima e para baixo
    const moveUpBtn = document.createElement("button");
    moveUpBtn.textContent = "↑";
    moveUpBtn.className = "move-up";
    moveUpBtn.onclick = () => moveCommand(li, "up");

    const moveDownBtn = document.createElement("button");
    moveDownBtn.textContent = "↓";
    moveDownBtn.className = "move-down";
    moveDownBtn.onclick = () => moveCommand(li, "down");

    li.appendChild(moveUpBtn);
    li.appendChild(moveDownBtn);

    // Adiciona o novo comando à lista
    commandList.appendChild(li);
    commandInput.value = ""; // Limpa o campo de entrada
}

// Função para mover comandos para cima ou para baixo
function moveCommand(commandElement, direction) {
    if (direction === "up" && commandElement.previousElementSibling) {
        commandList.insertBefore(commandElement, commandElement.previousElementSibling);
    } else if (direction === "down" && commandElement.nextElementSibling) {
        commandList.insertBefore(commandElement.nextElementSibling, commandElement);
    }
}

// Função para executar a sequência de comandos
// Função de espera assíncrona para criar uma pausa
function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function executeCommands() {
    const commands = [];
    const loopToggle = document.getElementById("loop-toggle").checked;

    // Coleta todos os comandos na lista
    commandList.querySelectorAll("li").forEach((li) => {
        commands.push(li.firstChild.textContent); // Adiciona o texto do comando
    });

    if (commands.length === 0) {
        alert("Nenhum comando para executar!");
        return;
    } else {
        isLooping = loopToggle;
        do {
            for (const command of commands) {
                console.log("Executando comando:", command);
                await delay(500); // Atraso de 500ms entre cada comando
            }

            // Pausa de 1 segundo entre cada loop da sequência completa
            await delay(1000);

        } while (isLooping && document.getElementById("loop-toggle").checked);
    }
}