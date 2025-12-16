# Projeto Hidroponia semi-autônomo



##### Contextualização do projeto, indicando suas aplicações e/ou motivação:



 	O intuito principal do projeto busca auxiliar cultivos de plantas no estilo hidropônico. A hidroponia é um estilo de plantação feita com as raízes da planta submersas em água nutrificada, o que o diferencia bastante do cultivo comum que geralmente requer solo geralmente fértil pra nutrição da planta pela raiz.



 	Nesse contexto, a arquitetura de hardware do projeto utiliza um microcontrolador Arduino Uno R3 como unidade central de processamento, responsável por gerenciar todas as leituras de sensores e as atuações automáticas do sistema.



Para a gestão da iluminação, o sistema emprega um sensor fotossensível LDR (Light Dependent Resistor) que monitora a incidência de luz em tempo real. Com base nesses dados, o Arduino aciona um micro servo motor acoplado mecanicamente ao eixo de um Dimmer de 2000W. Esta abordagem mecânica para o controle da intensidade da lâmpada foi adotada estrategicamente para garantir o isolamento entre o circuito de baixa tensão do microcontrolador e a alta tensão da rede elétrica, proporcionando maior segurança ao sistema enquanto assegura que a planta receba a iluminação adequada.



A aquisição de dados ambientais é realizada por sensores de alta precisão. Para a atmosfera do cultivo, utiliza-se um sensor DHT22, responsável por medir simultaneamente a temperatura e a umidade relativa do ar.



Já para o monitoramento da solução nutritiva, o projeto integra um sensor DS18B20, uma sonda digital impermeável ideal para medição submersa da temperatura da água.



Esses dados têm caráter informativo e são exibidos em uma interface homem-máquina composta por um display LCD 16x2, permitindo o acompanhamento instantâneo das condições vitais do cultivo.



Por fim, a estabilidade da nutrição é mantida por um sistema de reposição hídrica. Um sensor de nível monitora o reservatório e, ao detectar que o volume está abaixo do limiar predefinido, aciona uma bomba de água. Essa automação reabastece o sistema até que o nível se estabilize, evitando a exposição das raízes ou alterações drásticas na concentração de nutrientes.



##### Lista de materiais:

-Arduino Uno R3

-DS18B20(sensor de temperatura da água)

-fotoresistor LDR

-Micro Servo Motor 9g Sg90

-DHT22(sensor de temperatura e umidade)

-dimmer\_2000W(potenciomento da lâmpada fluorescente)

-lâmpada fluorescente

-FD10(sensor de nível de água)

AM2302-Sensor

DallasTemperature

ESP32_Thermistor

OneWire

Servo

GROVE - LCD RGB blacklight

DHT sensor library

##### Problemas encontrados no processo de montagem:

-Altas voltagem: para implementarmos a lâmpada fluorescente em nosso projeto temos o desafio de lidar com componenetes de alta voltagem (110 a 220V) o que pode causar eletrocutamento leve/moderado ao manusear componentes energizados sem o devido isolamento ou cuidado.

-O github não suporta armazenar as bibliotecas implementadas nos projetos devido ao grande número de arquivos(ele não carrega mais de 100 arquivos[pelo menos na interface de arrastar com o mouse no site, não]) o que tornou inviável salvar de forma segura as bibliotecas necessárias para o funcionamento do projeto. A alternativa que pensamos foi apenas salvar o nome das bibliotecas necessárias e, em caso de perda dessas bibliotecas de alguma forma, reinstalar uma por uma parar retomar os trabalhos.

-Tivemos muitos problemas para fazer o sensor de temperatura da água funcionar, pois não estávamos conseguindo configurar da forma correta. Devido a isso, tivemos que trocar o modelo e, após a troca, conseguimos resolver esse problema.

-Tivemos dificuldades para fazer o servo se mover na angulação correta. Além disso, foi necessário desenvolver um apoio para que o servo conseguisse aumentar e diminuir a intensidade da luz do dimmer, garantindo também a fixação adequada entre ambos.

-Outra dificuldade foi para fazer o servo funcionar junto com os outros sensores e atuadores, pois o 5V do Arduino não estava fornecendo energia suficiente para todos os componentes. Por isso, foi necessário utilizar o 5V do protoboard para garantir o funcionamento correto do sistema.

##### Diagrama da montagem:

##### Foto e vídeo do projeto:

##### Bibliotecas utilizadas:

##### 

##### Relatórios Diário

###### 

###### Dia 18/11
Querido diário, hoje buscamos pelos hardwares necessários para nosso projeto de medição de luminosidade, temperatura do ar e água, umidade, nível de água e regulador de luz e nível de água!

###### Dia 25/11
Querido diário, hoje eu e Lara criamos o código pro sensor de luminosidade, mais conhecido como LDR e pro sensor de temperatura e umidade do ar, menos conhecido como AOSONG AM2302. Também montamos ele no protoboard e depois no Arduíno, foi possível assistir a leitura tanto do nível de luminosidade do ambiente quanto o de umidade e temperatura

###### Dia 26/11
Querido diário, Lara está quebrando a cabeça pra saber como conectar o sensor de temperatura da água uma vez que ele tem uma entrada deveras estranha, ela conseguiu conectar as entradas de forma correta para lermos pelo Arduíno, eu compilei o código mas os testes foram meios decepcionantes, a temperatura da água que na teoria era pra ser ambiente teve leituras de valores menores que a água supostamente gelada, exemplo: quente:20 graus, gelada 33 graus. Enquanto eu tentava consertar de alguma forma esse empecilho, Lara achou sobre a montagem do nivelador de água mas saiu correndo com pressa pra não perder a carona e não iniciou a montar, e eu devo deixar pra tentar corrigir essa leitura depois também.

###### Dia 02/12
Querido diário, hoje ficamos por conta de fazer a prova de arduíno.

###### Dia 03/12
Querido dário, hoje implementamos separadamente os sensores de nível de água, o micro servo, o sensor de temperatura da água e o potenciômetro para controlar a intensidade da lâmpada. Inicialmente, tivemos problemas com o sensor de temperatura, que era um NTC 10k MF58, e não conseguimos fazê-lo funcionar corretamente, então resolvemos substituí-lo por um DS18B20. Após a troca, o sensor passou a funcionar da forma correta.

###### Dia 08/12
Querido diário, hoje conseguimos trocar o servo para que ele funcionasse por angulação, achamos um objeto 3d que grudamos nele para ele conseguir rodar o potenciometro do dimmer. Conseguimos também fazer o código base com todos os sensores funcionando. Além disso, conseguimos fazer o display começar a funcionar, porém com alguns problemas.

###### Dia 09/12
Querido diário, hoje conseguimos finalizar o código e apresentamos para a Milene. Conseguimos fazer a lógica do servo funcionar e também o relé da bomba funcionar. Colocamos o protótipo em uma caixa, posicionando a luz em um local adequado, próximo ao LDR, para que a lógica funcionasse corretamente. Além disso, posicionamos o dimmer e o servo de forma que o servo conseguisse girar o potenciômetro e, por último, arrumamos o display para mostrar os valores das variáveis obtidas por alguns sensores. Além disso, houve um grande avanço no README, com toda a contextualização feita, a listagem de componentes com suas respectivas imagens e um avanço no projeto em Fritzing.
