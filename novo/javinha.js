const commandList = document.getElementById("command-list");
let isLooping = false;

// Função para adicionar um comando à lista
function addCommand() {
    const commandInput = document.getElementById("command-input");
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
