# Medidor

Manual de operação
Neste excerto trataremos do funcionamento, materiais utilizados e o diagrama elétrico de um PoC utilizando a plataforma Arduíno UNO R3 com a finalidade de medir os valores médios de luminosidade, temperatura e umidade de um ambiente em questão tendo um prospecto de análise, controle, e previsão tanto de ambientes controlados como ambientes críticos.
Seu funcionamento é in loco podendo ser analisado e acessado a distância, via programa de captação dos dados inferidos pelo dispositivo, conectado a uma fonte de energia o sistema atua de forma autônoma exibindo os valores médios a cada minuto. Em caso de valores fora dos parâmetros estabelecidos o aparelho emite sinais sonoros e luminosos para sinalização, além de gravar os valores excepcionais obtidos

Materiais utilizados:
•	1 MCU (Atmega 328P) - Arduino Uno R3
Recebe e interpreta os dados vindos dos sensores e envia respostas ao display e aos sinalizadores.

•	1 LDR
Sensor de luminosidade

•	1 DHT-11
Sensor de umidade e temperatura

•	1 LCD 16x2
Visualização dos dados

•	1 Bateria de 9V
Proporciona energia elétrica ao sistema

•	1 RTC (Real Time Clock)
Mantém o controle do tempo real

•	1 protoboard
Placa de ensaio para o projeto

•	1 LED vermelho
Sinaliza quando a temperatura está acima da média desejada

•	1 LED azul
Sinaliza quando a temperatura está abaixo da média desejada

•	5 Resistores 10kΩ
Controla a corrente do circuito

•	1 Suporte para bateria
Conecta a bateria ao circuito

•	1 Buzzer
Sinalizador sonoro

•	Jumpers
Liga os componentes

Diagrama elétrico:

![Diagrama](https://github.com/ArturRossiJunior/Medidor/assets/85141892/9e66d876-829f-4ce6-8e74-8fe7f69feca3)
