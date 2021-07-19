# NUCLEO-L412KB_Source
 CURSO DE ESPECIALIZACION EN MICROCONTROLADORES ARM

<img src="https://www.st.com/bin/ecommerce/api/image.PF266995.en.feature-description-include-personalized-no-cpn-medium.jpg">

<h2> 1. DOCUMENTOS NECESARIOS</h2>
<h4>1. Reference manual stm32l4</h4>
- https://www.st.com/resource/en/reference_manual/dm00151940-stm32l41xxx42xxx43xxx44xxx45xxx46xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
<h4>2. programming manual stm32l4</h4>
- https://www.st.com/resource/en/programming_manual/dm00046982-stm32-cortex-m4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf
<h4>3. Datasheet stm32l412</h4>
- https://www.st.com/resource/en/datasheet/stm32l412c8.pdf
 <h4>4. STM32 Nucleo-32 boards</h4>
 - https://www.st.com/resource/en/user_manual/dm00231744-stm32-nucleo32-boards-mb1180-stmicroelectronics.pdf
 <h2>2.ENTORNO DE DESARROLLO</h2>
 <h4>- ARM keil uVision</h4></h4>
 https://www.keil.com/demo/eval/arm.htm
 <h4>- ARM compiler 5 </h4>
 https://developer.arm.com/tools-and-software/embedded/arm-compiler/arm-compiler-5/downloads
 
 <h2>3. CLASE 3 - 4 - 6: MATERIALES NECESARIOS </h2>
 1. Pulsadores
 2. Leds
 3. Displays de 7 segmentos Cátodo comun
 4. Resistencias de 330, 1k OHM
 5. Transitor NPN

<h4>- CIRCUITO </h4>
 <img src="https://user-images.githubusercontent.com/47931397/124375187-75704900-dc66-11eb-9afd-b8750da774bd.png">

<h2>4. CLASE 7</h2>
<h4>CIRCUITO</h4>
 <img src="https://user-images.githubusercontent.com/47931397/125021030-7d056880-e03f-11eb-9870-b9896b35eb87.png">

<h2>5. CLASE 10: EJEMPLO 2</h2>
<img src="https://user-images.githubusercontent.com/47931397/126029874-b370ce7c-350e-427a-9ede-189923b650fd.png">
<h2>6. CLASE 10: EJEMPLO 3</h2>
<img src="https://user-images.githubusercontent.com/47931397/126029892-07ef774a-4021-46a3-aa97-f0112d74065d.png">

<h2>6. CLASE 13 </h2>
La correción del USART2 para el envío de datos por el printf es que en los pines ADC se seleciona tambien el pin PA2, que es el pin
USART2_TX, se cambia la configuración de función alternativa a modo analógico, para corregir ese error se hace cambia el PA2 al pin PA3, que en este caso 
sería el canal analógico IN8.
<img src="https://user-images.githubusercontent.com/47931397/126101929-a272fe96-4308-46fc-898e-28bd1c82c9e3.png">



<h2>AUTOR</h2>
- Quino B. Jeffry
