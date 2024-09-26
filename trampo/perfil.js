const sendButton = document.getElementById('send-button');
const messageInput = document.getElementById('message');
const chatMessages = document.getElementById('chat-messages');
const userSelect = document.getElementById('user-select');

function fetchMessages() {
    fetch('/chat/messages/')
        .then(response => response.json())
        .then(data => {
            chatMessages.innerHTML = '';
            data.messages.forEach(msg => {
                const messageElement = document.createElement('div');
                messageElement.classList.add('chat-message');
                if (msg.username === 'Usuário 1') {
                    messageElement.classList.add('user-message');
                }
                messageElement.innerHTML = `<strong>${msg.username}:</strong> ${msg.content} <small>${msg.timestamp}</small>`;
                chatMessages.appendChild(messageElement);
            });
            chatMessages.scrollTop = chatMessages.scrollHeight;
        });
}

sendButton.addEventListener('click', () => {
    const messageText = messageInput.value;
    const selectedUser = userSelect.value;

    if (messageText.trim() !== '') {
        fetch('/chat/', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'X-CSRFToken': '{{ csrf_token }}'
            },
            body: new URLSearchParams({
                username: selectedUser,
                content: messageText
            })
        }).then(response => {
            if (response.status === 201) {
                messageInput.value = '';
                fetchMessages();
            }
        });
    }
});
setInterval(fetchMessages, 3000);

messageInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') {
        sendButton.click();
    }
});

fetchMessages();