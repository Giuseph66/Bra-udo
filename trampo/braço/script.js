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

    // Loop através dos 6 motores
    for (let i = 1; i <= 5; i++) {
        const motor = 'motor' + i;

        // Obtém os valores atuais, mínimos e máximos
        const value = parseFloat(document.getElementById(motor + '-value').value);
        const min = parseFloat(document.getElementById(motor + '-min').value);
        const max = parseFloat(document.getElementById(motor + '-max').value);

        // Armazena os valores no objeto de configuração
        config[motor] = {
            value: value,
            min: min,
            max: max
        };
    }

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
            for (let i = 1; i <= 6; i++) {
                const motor = 'motor' + i;

                if (config[motor]) {
                    const value = config[motor].value;
                    const min = config[motor].min;
                    const max = config[motor].max;

                    // Atualiza os campos de mínimo e máximo
                    document.getElementById(motor + '-min').value = min;
                    document.getElementById(motor + '-max').value = max;
                    updateRange(motor);

                    // Atualiza o valor atual
                    document.getElementById(motor + '-value').value = value;
                    document.getElementById(motor + '-slider').value = value;
                    updateValue(motor);
                }
            }

            //alert('Configuração "' + configName + '" carregada com sucesso!');
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

// Chama a função para atualizar o menu suspenso ao carregar a página
window.onload = function() {
    updateConfigurationsDropdown();
};
