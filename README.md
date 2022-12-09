# Projeto-Final
Projeto de IoT relacionado à automação domótica utilizando conceitos de conexão MQTT, gateway, smart hub, comando por voz.

## Autores
Alcides Yoshimitsu Shimonishi
Danilo Silva Maia
Octavio Henrique Cerbara

## Descrição
O projeto consistirá em uma automação de um sistema de iluminação. O sistema será um controle de iluminação de um cômodo de uma casa a partir da presença de uma pessoa no cômodo. O sistema identifica, por meio de um sensor de presença, se há alguém no cômodo, em caso positivo, a lâmpada será acesa, caso contrário, será apagada. A lâmpada será acionada por meio de um relé que receberá o comando de uma ESP32 que será um IoT device. As informações de presença e status da lâmpada, por sua vez, serão enviadas ao smart home iot hub que será desempenhada por uma raspberry pi. Da rasp, essas informações irão para a nuvem e serão visualizadas por um dashboard. O sistema ainda contará com um sensor de luminosidade, para que seja coletada essa informação e também apareça no dashboard, percorrendo o mesmo fluxo mencionado anteriormente. O sistema poderá ser automático, como descrito acima, ou por comando de voz (acender quando o usuário disser o comando). O usuário fará essa configuração também por comando de voz. Ao dizer “automático”, o sistema passa a operar a partir do sensoriamento, ao dizer “comando por voz”, o sistema só mudará o status da lâmpada após um comando do usuário. O modo de controle também aparecerá no dashboard. A Raspberry será a responsável por receber os comandos de voz e alternar entre os modos de controle.

## Tutoriais

### IoT Device
O sistema contém uma ESP32 agindo como dispositivo embarcado de IoT relacionado ao sensoriamento e atuação no sistema além de ser capaz de comunicar-se através do protocolo MQTT. Nela estão conectados um sensor de presença do tipo PIR, um sensor de luminosidade do tipo LDR e um módulo relé agindo como atuador para ligar e desligar uma lâmpada LED a partir de comandos recebidos. A programação para este dispositivo foi realizada no ambiente do Arduino IDE e o código é disponibilizado na pasta *src* deste repositório com o nome *script_ESP32.ino*. Primeiramente, os sensores de presença e luminosidade são conectados às portas GPIO 33 e 35 da ESP32 respectivamente e o modulo relé à porta GPIO 32. No código, são feitas as configurações para conexão WiFi e MQTT; uma função de callback é utilizada para que seja possivel receber, do MQTT broker, informações referentes aos diferentes comandos e assim tornar possivel o controle do atuador. Foram configurados 3 tipos de mensagens MQTT que o device IoT pode receber (VON, VOFF e AUT) referentes à comandos por voz e comando automático; dentro do loop principal o programa faz a leitura dos sensores de LDR e PIR e logo em seguida verifica o tipo de controle recebido através da função callback para tomar a decisão de acionar ou não o atuador (acende ou apaga lâmpada) enviando ao broker as leituras realizadas pelos sensores bem como o status da lâmpada naquele momento.

### IoT Hub
O sistema contém uma placa Raspberry Pi atuando como MQTT broker do sistema, centralizando as informações enviadas e recebidas pelo IoT Device bem como pelo smatphone também conectado ao sistema via WiFi e protocolo MQTT. A topologia do sistema é mostrada a seguir.

### Smartphone com App Android
O sistema conta com integração de aplicativo mobile desenvolvido através da plataforma *MIT Inventor* que consegue conectar-se ao *MQTT broker* ao pressionar o botão "Press to Connect" e assim enviar comandos e receber informações relativas às leituras dos sensores. Ao iniciar a tela, o comando do tipo "Automático" é enviado por default fazendo com que o sistema de controle de iluminação seja gerido através das leituras dos sensores e dos valores pré-estipulados em código. Ao pressionar o botão "Press to Speak (command type)" o usuário consegue, através de comando por voz, pelo próprio app, escolher entre controle automático ou comando por voz ao pronunciar as palavras "automático" ou "comando por voz", respectivamente. Caso o comando por voz seja o escolhido, instantaneamente o tipo de controle é alterado pelo sistema e também registrado na tela do aplicativo e, a partir deste momento, ao pressionar o botão "Press to Speak (turn on/turn off)" o usuário consegue escolher entre acender ou apagar a luz no momento desejado, independente da leitura dos sensores ao pronunciar as palavras "acender" ou "apagar" respectivamente, enviando mensagem MQTT para o broker relativo ao comando e alterando o status da lâmpada através do atuador (módulo relé) conectado ao IoT Device (ESP32).   

## Conexões físicas do sistema
Abaixo é apresentada imagem que ilusta as conexões físicas do circuito utilizado feitas no ambiente do Frietzing




