<H1> BLUE PILL </H1>
Está sección estará dedicada al MCU STM32F103C8, se subirán algunos ejemplos básico de guía para que los alumnos que cuentan con este MCU puedan guiarse y practicar.
 <img src="https://user-images.githubusercontent.com/47931397/125591860-b5998716-1427-42bc-9003-905e01b04ca0.png">
 
 <h3> RCC_STM32F103 </h3>
 En este proyecto se realiza la configuración del PLL a 64MHz, Adicionalmente se cofiguran el PB0 y el PC13 como entrada y salida de proposito general respectivamente.
 Se Configura la SysTick para generar una función en retardos en ms. Y finalmente se configura la linea EXTI0 para generar interrupciones externas por el pin PB0
 
 <h3> USART_STM32F103</h3>
 En este proyecto se muestra con configuración del USART1 para la recepción y la transmisión de datos. Se habilita interrupcion para la linea RX. De manera adicional se 
 realizan funciones de retarget para hacer uso de la fuciones stdio.
