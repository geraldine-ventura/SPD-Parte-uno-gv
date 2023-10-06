# SPD-parcial-domiciliario-parte-uno
 Parcial parte uno
# Ejemplo Documentación 
![Tinkercad](./Img/ArduinoTinkercad.jpg)


## Integrantes 
- Rivero Leandro Adriel
- Geraldine Ventura Riveros
- Stadelman German Ariel


## Proyecto: Parte 1: Contador de 0 a 99 con Display 7 Segmentos y Multiplexación.
![Tinkercad](./Img/SPD_Parte_uno.png)


## Descripción
Nos permite sumar digitos uno a uno entre 0 a 99 o descontar, ofreciendo la oportunidad de resetear nuestro contador si es necesario.

## Función principal
Esta funcion se encarga de evaluar los tiempos entre pulsadores para evitar el ghosting, y permite cuando son pulsados sumar o restar o resetear nuestros digitos en los display de siete segmentos.

Definimos los alias para los puertos entrada/salida usando constantes
int const A = 10; //segmento A ,int const B = 11; //segmento B (...) asociandolo a pines de la placa arduino.

(Breve explicación de la función)

~~~ C (lenguaje en el que esta escrito)
!void visualidarDigitos()
{
  //Si ya pasó el tiempo de espera para realizar un cambio en el multiplexado, procede a hacerlo
  if((millis()- espera_display) >= delay_display )
  {
    
  	if(digitoAMostrar == unidad)//pregunto si debo mostrar la unidad
    {
    	digitalWrite(DU, LOW);
  		digitalWrite(DD, LOW);
  		printDigit(contador%10);//Para obtener la unidad del contador utilizo el resto de dividir por 10
  		digitalWrite(DU, HIGH);
    }
    
    if(digitoAMostrar == decena)//pregunto si debo mostrar la decena
    {
    	digitalWrite(DU, LOW);
  		digitalWrite(DD, LOW);
  		printDigit(contador/10);//para obtener la decena del contador simplemente lo divido por 10
  		digitalWrite(DD, HIGH);
    }
 	if(digitoAMostrar == unidad)digitoAMostrar = decena;//si mostró unidad, cambio la referencia para que muestre unidad
    else digitoAMostrar = unidad;// y vicerversa
      
    espera_display = millis();//recargo el valor de referencia para la espera para multiplexado
  }
}

//Función para convertir un número a la codificación del display
void printDigit(int digit)
{
  //apago todos los led
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  //con el swich encenderé solo los digitos necesarios para mostrar el número en cada caso
  switch (digit)
}
~~~
## :robot: Link al proyecto
- [proyecto]()
## :tv: Link al video del proceso
- [video]()

---
### Fuentes
