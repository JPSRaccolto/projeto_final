![image](https://github.com/user-attachments/assets/f2a5c9b8-6208-4723-8f46-1d74be421827)


# 🛠️ Projeto: PWM e I2C com RP2040

## 📑 Sumário
- [🎯 Objetivos](#-objetivos)
- [📋 Descrição do Projeto](#-descrição-do-projeto)
- [⚙️ Funcionalidades Implementadas](#%EF%B8%8F-funcionalidades-implementadas)
- [🛠️ Requisitos do Projeto](#%EF%B8%8F-requisitos-do-projeto)
- [📂 Estrutura do Repositório](#-estrutura-do-reposit%C3%A1rio)
- [🖥️ Como Compilar](#%EF%B8%8F-como-compilar)
- [🤝 Contribuições](#-contribui%C3%A7%C3%B5es)
- [📽️ Demonstração em Vídeo](#%EF%B8%8F-demonstra%C3%A7%C3%A3o-em-v%C3%ADdeo)
- [📜 Licença](#-licen%C3%A7a)
- [💡 Considerações Finais](#-considera%C3%A7%C3%B5es-finais)

## 🎯 Objetivos

• Utilizar o PWM para controlar a intensidade sonora dos buzzers.

• Representar mensagens de alerta no display ssd1306.

• Aplicar o protocolo de comunicação I2C na integração com o display.

• Aplicar Debouncing nos botões.

## 📋 Descrição do Projeto
Este projeto utiliza a placa BitDogLab com os seguintes componentes:
- JoyStick (GPIO 22)
- LED RGB (GPIO 13)
- Botão A (GPIO 5)
- Botão B (GPIO 6)
- Display SSD1306 via I2C (GPIO 14 e GPIO 15)

## ⚙️ Funcionalidades Implementadas
1. **Debouncing:**
   - Aplica debouncing no Botão A, Botão B e o botão do JoyStick.
     
2. **Modulação PWM dos buzzers:**
   - Alterna o volume sonoro dos buzzers utilizando modulação PWM.
     
3. **Acionamento de interrupção com o Botão A, Botão B e Botão do Joystick:**
   - Interrompe a funcionalidade de 2 botões por vez a depender de qual botão foi pressionado.

4. **Display ssd1306:**
   - Apresenta uma mensagem de alerta indicando o que está acontecendo e qual ação deve ser feita, o Botão A e o Botão B apresentam mensagem diferentes do display.

## 🛠️ Requisitos do Projeto
- **Uso de Interrupções:** Controlar os eventos dos botões.
- **Debouncing:** Implementação via software.
- **Controle de buzzers:** Utilização dos buzzes.
- **Uso do Display SSD1306:** Exibição de mensagens e bordas.
- **Organização do Código:** Código estruturado e comentado.

## 📂 Estrutura do Repositório
```
├── projeto_final_v2.c   # Código principal do projeto
└── ssd1306.c            # Configuração do controle do display
└── ssd1306.h            # Configura a .c como biblioteca
└── ...                  # Demais arquivos necessários
```

## 🖥️ Como Compilar
1. Clone o repositório:
   ```bash
   https://github.com/JPSRaccolto/projeto_final.git
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd projeto_final
   ```
3. Compile o projeto com seu ambiente de desenvolvimento configurado para o RP2040.
4. Carregue o código na placa BitDogLab.

## 🖥️ Metodo alternativo:
1. Baixe o repositório com arquivo zip.
2. Extraia para uma pasta de fácil acesso
3. Utilize a extensão raspberry pi pico dentro do VS Code para importar o projeto.
4. Aguarde ate criar o arquivo build
5. Utilize o ícone "_compile_" para compilar.
6. Utilize o "_RUN_" com a BitDogLab em modo boot seel para enviar o programa para a sua RP2040.
7. Agora, interaja com os botões e o teclado para mergulhar nas funcionalidades do projeto.

## 🧑‍💻 Autor
**João Pedro Soares Raccolto**

## 📝 Descrição
Tarefa apresentada ao Cepedi como parte dos critérios de avaliação do curso EmbarcaTech em Software e Sistemas Embarcados, com foco na aplicação prática de comunicação serial e integração de hardware com o microcontrolador RP2040.

## 🤝 Contribuições
Este projeto foi desenvolvido por **João Pedro Soares Raccolto**.
Contribuições são bem-vindas! Siga os passos abaixo para contribuir:

1. Fork este repositório.
2. Crie uma nova branch:
   ```bash
   git checkout -b minha-feature
   ```
3. Faça suas modificações e commit:
   ```bash
   git commit -m 'Minha nova feature'
   ```
4. Envie suas alterações:
   ```bash
   git push origin minha-feature
   ```
5. Abra um Pull Request.

## 📽️ Demonstração em Vídeo
- O vídeo de demonstração do projeto pode ser visualizado aqui: [Drive](https://youtu.be/nn0B_-Tjze4)

## 💡 Considerações Finais
Este projeto oferece uma ótima oportunidade para consolidar conhecimentos sobre manipulação de hardware,
I2C, PWM e desenvolvimento com microcontroladores. Certifique-se de seguir todos os requisitos e manter um código limpo e bem comentado.
