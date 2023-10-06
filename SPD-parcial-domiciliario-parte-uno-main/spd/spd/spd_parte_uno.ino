// C++ code
//
/*Funcionamiento de aplicación de millis(): 
	millis(): Función que devuelve el tiempo transcurrido (en milisegundos) desde que se prendío el dispositvo.
    Utilizamos millis de la siguiente forma para habilitar la lectura de tecla o el multiplexado.
    if( millis() - valor_referencial > valor_fijo_delay)*(1)
    {
    	valor_referencial = millis()*(2)
    }
  	(1)al tiempo actual transcurrido le resta el valor de tiempo capturado anteriormente, si esto es mayor
    que el valor fijo de espera se permite acceder al if
    (2) una vez accedí al contenido del if, se debe recargar eñ valor de tiempo capturado para que la espera 
     siga siendo funcioanl
*/
//Definimos los alias para los puertos entrada/salida usando constantes

//Digitos de display
int const A = 10; //segmento A
int const B = 11; //segmento B
int const C = 5;  //...
int const D = 6;
int const E = 7;
int const F = 9;
int const G = 8;
int const DU = A4;//Display unidad
int const DD = A5;//Display decena

int const unidad = 1; 
int const decena = 2;

//pulsadores
int reset = 4;
int b_suma = 3;
int b_resta = 2;

//variables
int contador = 0; //contador principal

int const delay_tecla = 150;//Valor de espera para tecla(evita que al presionarlo sumo mas de una unidad a la vez)
int const delay_display = 5;//Valor de espera para el multiplexado
int espera_tecla = millis();//Tiempo transcurrido para presionar tecla
int espera_display = millis();//Tiempo transcurrido para cambio en el multiplecado
int digitoAMostrar = unidad;//Variable que referencia si el multiplexado debe mostrar la unidad o la decena

void setup()
{
  //Defino los pines de segemento como salida
  pinMode(A,OUTPUT); //B
  pinMode(B,OUTPUT); //A
  pinMode(C,OUTPUT); //F
  pinMode(D,OUTPUT); //G
  pinMode(E,OUTPUT); //E
  pinMode(F,OUTPUT); //D
  pinMode(G,OUTPUT); //C
  pinMode(DU, OUTPUT); //Unidad
  pinMode(DD, OUTPUT); //Decena
  
  //Defino los pines de segemento como entrada
  //agregamos pullup para evitar ruido eléctrico en la entrada
  pinMode(reset, INPUT_PULLUP); //PuLSADOR a 0
  pinMode(b_suma, INPUT_PULLUP); //PULSADOR + 1
  pinMode(b_resta, INPUT_PULLUP); //PULSADOR - 1
  //Fin de la configuración de pines
  
  visualidarDigitos();//Inicio el dispositivo mostrando el valor del contador
}

void loop()
{
  //Si ya pasó el tiempo de espera para presionar tecla accede a la lectura
  if( millis()- espera_tecla > delay_tecla)
  {
    espera_tecla = millis(); //recargo el valor de referencia para la espera 
    if(digitalRead(reset) == LOW)contador = 0;//aplica reset al contador
    if(digitalRead(b_suma) == LOW && contador < 99) contador++;//suma si el contador no llegó a 99
    if(digitalRead(b_resta) == LOW && contador > 0)contador--;//resta si el contador no llegó a 0
  }
  visualidarDigitos();
}

void visualidarDigitos()
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
  {
    case 1:
    	digitalWrite(B, LOW);
  		digitalWrite(C, LOW);
    	break;
    case 2:
    	digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        
        digitalWrite(G, LOW);
    	break;
    case 3:
    	digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(G, LOW);
    	break;
    case 4:
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
    	break;
    case 5:
    	digitalWrite(A, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
    	break;
    case 6:
    	digitalWrite(A, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
    	break;
    case 7:
    	digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
    	break;
    case 8:
    	digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
    	break;
    case 9:
    	digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
    	break;
    case 0:
    	digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(9, LOW);
    	break;
  }
}
