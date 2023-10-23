![tinkercard](./img/tinkercard.jpg)
## DOCUMENTACION DEL TRABAJO PRACTICO DE SPD

- **Alumno**: Matias Emanuel Briceño Castillo

 - **Legajo**: 115466

### INTEGRANTES

- Almonacid, Emir Leandro

- Cabral, Ezequiel Matias


![Placa_arduino](./img/placa_arduino.png) 

### Desarrollo del proyecto


El proyecto consta de 3 partes evolutivas donde se enmpieza mostrando un contador y finaliza con la integracion de un sensor de temperatura, un motor de aficionado, una foto resistencia, leds, un interruptor y se agrego la capacidad de contar y mostrar tambien los numeros primos que se encuentran entre 0 y 97.
El proceso de integracion sera explicado en las siguientes lineas 

* ### Parte 1

![proyecto_inicial](./img/tp_1.png)

La primera PARTE inicia con 2 display de 7 segmentos que mostraran los numeros del 0 al 99 estando conectados en serie desde el pine 13 hasta el 7 inclusive, todos ellos configurados con la modalidad OUTPUT los cuales se encargaran de brindar la entrada de corriente.
Como salida de la corriente, los display, estan conectados a los pines analogicos A4 Y A5, tambien con la modalidad OUTPUT.

~~~ C++
  // como configurar un pin como OUTPUT dentro de la funcion setup.
  pinMode(13,OUTPUT);
~~~

El funcionamiento del display es el siguiente, cada display contiene 7 leds y estos se encienden  si la corriente circula a traves de ellos. Para que circule la corriente, el pin al que estan conectado cada led les tiene que entregar corriente y esta ultima debe circular a traves de ellos donde la salida es el pin A4 para el display que muestra la unidad y el pin A5 para el que muestra la decena.
Entonces para que circule la corriente la configuracion el pin que entrega corriente debe ser 1 y se escribe en el codigo de la siguiente manera:

~~~ C++
  //PASARLE COMO PARAMETRO HIGH O 1 ES LO MISMO
  digitalWrite(A4,1);
  //ASI TAMBIEN FUNCIONA
  digitalWrite(A4,HIGH);
~~~

Como el pin A4 O A5 tambien estan configurado para entregar corriente solamente la corriente podra fluir si el estado de ellos es 0 o LOW.

~~~ C++
  //PASARLE COMO PARAMETRO LOW O 0 ES LO MISMO
  digitalWrite(A4,0);
  //ASI TAMBIEN FUNCIONA
  digitalWrite(A4,LOW);
~~~

Adjuntamos ejemplo y su explicacion
Si todos los pines que entregan corrientes estan configurados como HIGH y los pines A4 Y A5 estan configurados como low, el codigo y lo que se vera en los display sera lo siguiente

~~~ C++

  // permitimos la entrega de corriente de todos los pines
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);

  //impedimos la entrega de corriente de los pines A4 y A5

  digitalWrite(DISPLAYUNI,LOW);
  digitalWrite(DISPLAYDEC,LOW);

~~~
![displays encendidos](./img/displays_encendidos.png) 



Por ultimo tambien contamos con 3 pulsadores, uno para reinicar el contador, otro para avanzar al siguiente numero y el ultime para retroceder un numero. En este caso la corriente solamente fluye cuando el pulsador es presionado.
Cada pulsador esta conectado a un pin que es capaz de entregar y recibir energia con la configuracion INPUT_PULLUP

~~~ C++

  // configuramos el pulsador que resetea el contador con un pin input_pullup dentro de la funcion setup.
  // RESET = pin 5;
  pinMode(RESET,INPUT_PULLUP);

~~~

Para saber si el pulsador esta siendo presionado debemos leer el estado del pin RESET. Si el estado es 1 o HIGH entonces la corriente no esta circulando pero si el estado es 0 o LOW resulta si lo hace.
La lectura de pin podemos hacerla con la siguiente funcion:

~~~ C++

  int estado_del_pin = digitalRead(RESET);

~~~

La dificultad de este proyecto se encontraba en como mostrar 2 numeros distintos en simultaneo porque si mostraba un numero este se visualizaba en ambos display, es decir, si mostrabas el numero 81 se visualizaba 88.
Esta complicacion se soluciono mostrando un numero pero en un solo display, es decir dejando fluir la corriente sobre uno y sobre el otro no. Luego cargar un delay minimo para que llegue a visualizarse correctamente y por ultimo apagando todos los leds. Despues de este procedimiento hacemos lo mismo pero invirtiendo los displays que prendimos o apagamos. Si en el caso anterior prendimos el display de las unidades en este sera el display que se apagara por lo tanto el que se mostrara sera el de la decena.
Adjunto el codigo del algoritmo:

~~~ C++

  void mostrar_numero(int numero)
{
  decena = numero / 10;
  unidad = numero % 10; 
 
  
  
  digitalWrite(DISPLAYDEC,LOW);
  digitalWrite(DISPLAYUNI,HIGH);
  prender_numero(decena);
  delay(10);
  apagar_todos();
  
  digitalWrite(DISPLAYDEC,HIGH);
  digitalWrite(DISPLAYUNI,LOW);
  prender_numero(unidad);
  delay(10);
  apagar_todos();
  	
}

~~~

Con toda esta logica explicada anteriormente se pudo realizar la parte 1

Tambien anexo la explicacion de la necesidad y la logica de la funcion keypressed(). Esta surge debido a que si se mantenia apretado el pulsador el contador avanzaba o retrocedia con mayor o menor velocidad dependiendo del delay que se utilizaba para mostrar el numero en los displays. Si el delay era mayor bajaba la visibilidad de los numeros en el display pero si el delay era menor sucedia lo contrario. Si bien la logica nos conduce a un delay bajo el problema era que al presionar el pulsador el contador aumentaba varios numeros.
Ante esta problematica se recurre a la funcion "keypressed" la cual guarda el estado previo del pulsador y lo compara con el actual. Si estos son distintos se realizara la accion correspondiente al pulsador, ya sea resetear, avanzar o retroceder.
Esta funcion fue extraida de lo videos subidos al classroom.

~~~ C++

int keypressed()
{
  sube = digitalRead(AUMENTAR);
  baja = digitalRead(DISMINUIR);
  reset = digitalRead(RESET);
  
  if(sube)
  {
	subePrevia=1;
  }
  if(baja)
  {
	bajaPrevia=1;
  }
  if(reset)
  {
	resetPrevia=1;
  }
  
  if(sube == 0 && sube!= subePrevia)
  {
    subePrevia = sube;
    return AUMENTAR;
  }
  if(baja == 0 && baja != bajaPrevia)
  {
    bajaPrevia = baja;
    return DISMINUIR;
  }
  if(reset == 0 && reset != resetPrevia)
  {
    resetPrevia = reset;
    return RESET;
  }
  
  return 0; 
~~~

Haga click **[aqui](https://www.tinkercad.com/things/kh0pY6c2NwD?sharecode=sBIrmK2LLrWdw0dRooUUQgn2emfkoky24-wjMsacfnU)** para ir al proyecto en tinkercard.



* ### Proyecto final

![proyecto_inicial](./img/tp_3.png)


  


