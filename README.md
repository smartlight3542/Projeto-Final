# Projeto-Final
Projeto de IoT relacionado à automação domótica utilizando conceitos de conexão MQTT, gateway, smart hub, comando por voice

## Descrição
O projeto consistirá em uma automação de um sistema de iluminação. O sistema será um controle de iluminação de um cômodo de uma casa a partir da presença de uma pessoa no cômodo. O sistema identifica, por meio de um sensor de presença, se há alguém no cômodo, em caso positivo, a lâmpada será acesa, caso contrário, será apagada. A lâmpada será acionada por meio de um relé que receberá o comando de uma ESP32 que será um IoT device. As informações de presença e status da lâmpada, por sua vez, serão enviadas ao smart home iot hub que será desempenhada por uma raspberry pi. Da rasp, essas informações irão para a nuvem e serão visualizadas por um dashboard. O sistema ainda contará com um sensor de luminosidade, para que seja coletada essa informação e também apareça no dashboard, percorrendo o mesmo fluxo mencionado anteriormente. O sistema poderá ser automático, como descrito acima, ou por comando de voz (acender quando o usuário disser o comando). O usuário fará essa configuração também por comando de voz. Ao dizer “automático”, o sistema passa a operar a partir do sensoriamento, ao dizer “comando por voz”, o sistema só mudará o status da lâmpada após um comando do usuário. O modo de controle também aparecerá no dashboard. A Raspberry será a responsável por receber os comandos de voz e alternar entre os modos de controle.

## Tutoriais

### IoT Device
O sistema contém uma ESP32 agindo como dispositivo embarcado de IoT relacionado ao sensoriamento e atuação no sistema além de ser capaz de comunicar-se através do protocolo MQTT. Nela estão conectados um sensor de presença do tipo PIR, um sensor de luminosidade e um módulo relé agindo como atuador para ligar e desligar uma lâmpada LED a partir de comandos recebidos. A programação 

### IoT Hub
O sistema


## Vídeo de Apresentação e Demonstrações de Uso




