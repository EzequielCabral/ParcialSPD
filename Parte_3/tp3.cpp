#define A 12
#define B 13
#define C 7
#define D 8
#define E 9
#define F 11
#define G 10
#define CONTADORNORMAL 5
#define AUMENTAR 4 
#define DISMINUIR 3
#define DISPLAYUNI 6
#define DISPLAYDEC 2
#define MOTOR A1
#define SENTEMP A0
#define VERDE A4
#define ROJO A5
#define FOTOR A3


int modo;
int modo_anterior;
int valor;


int contador = 0;
int contador_primo = 2;   

int lec_reset;
int lec_aumentar;
int lec_disminuir;

int decena;
int unidad;

int sube=1;
int subePrevia=1;
int baja = 1;
int bajaPrevia=1;

int numeros_primos[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int indice = 0;

int temperaturaReal;

bool hay_energia;


void setup()
{
    
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(MOTOR,OUTPUT);
  pinMode(CONTADORNORMAL,INPUT);
  pinMode(AUMENTAR,INPUT_PULLUP);
  pinMode(DISMINUIR,INPUT_PULLUP);
  pinMode(DISPLAYUNI,OUTPUT);
  pinMode(DISPLAYDEC,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(ROJO,OUTPUT);


  Serial.begin(9600);
  
}

void loop()
{
  hay_energia = funcionamiento_fotores();
  if(hay_energia)
  {
    modo = digitalRead(CONTADORNORMAL); 
  
    if(modo != modo_anterior)
    {
      contador = 0;
      indice = 0;
      contador_primo = numeros_primos[indice];    
    }
    else
    {
      contador_programa();   
    }
    
    if(modo == 0)
    {
      mostrar_numero(contador_primo);
    }
    else
    {
      mostrar_numero(contador);
    }

    modo_anterior = modo;
    funcionamiento_motor();    
    
  }
  else
  {
    digitalWrite(MOTOR,LOW);
    apagar_todos();
  }

    
  
}

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



void prender_numero(int numero)
{
  if(numero == 0)
  {
    cero();
  }
  else if(numero == 1)
  {
    uno();
  }
  else if(numero == 2)
  {
    dos();
  }
  else if(numero == 3)
  {
    tres();
  }
  else if(numero == 4)
  {
    cuatro();
  }
  else if(numero == 5)
  {
    cinco();
  }
  else if(numero == 6)
  {
    seis();
  }
  else if(numero == 7)
  {
    siete();
  }
  else if(numero == 8)
  {
    ocho();
  }
  else
  {
    nueve();
  }
}


int tecla_presionada()
{
  sube = digitalRead(AUMENTAR);
  baja = digitalRead(DISMINUIR);
  
  if(sube)
  {
	subePrevia=1;
  }
  if(baja)
  {
	bajaPrevia=1;
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
  
  
  return 0; 

}

void apagar_todos()
{
  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  digitalWrite(E,LOW);
  digitalWrite(F,LOW);
  digitalWrite(G,LOW);
}

void cero()
{    
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
}

void uno()
{
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);  
}

void dos()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(G,HIGH);
}

void tres()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(G,HIGH);
}

void cuatro()
{
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void cinco()
{
  digitalWrite(A,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(F,HIGH);  
}
void seis()
{
  digitalWrite(A,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);  
}

void siete()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
}

void ocho()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void nueve()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);  
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void contador_programa()
{
  int presionada = tecla_presionada(); 
  
  if(presionada == AUMENTAR)
  {
    if(modo == 0)
    {
      indice++;
      indice = indice % 25;
      contador_primo = numeros_primos[indice];       
    }
    else
    {
      contador++;
      contador = contador > 99 ? 0 : contador;
    }
    
  }
  if(presionada == DISMINUIR )
  {
    if(modo == 0)
    {
      indice--;
      indice = indice < 0 ? 24 : indice % 25;
      contador_primo = numeros_primos[indice];      
    }
    else
    {
      contador--;
      contador = contador < 0 ? 99 : contador;
    }    
  }      
}

void funcionamiento_motor()
{
  int temperaturaLeida = analogRead(SENTEMP);
  temperaturaReal = map(temperaturaLeida,20,358,-40,125);
  if(temperaturaReal > 0 && temperaturaReal < 31)
  {
    digitalWrite(MOTOR,HIGH); 
  }
  else
  {
    digitalWrite(MOTOR,LOW); 
  }
 
  
}

bool funcionamiento_fotores()
{
  valor = analogRead(FOTOR);
  hay_energia = true;
  if(valor >= 204)
  {
    digitalWrite(VERDE,HIGH);
    digitalWrite(ROJO,LOW);
  }
  else
  {
    apagar_todos();
    digitalWrite(VERDE,LOW);
    digitalWrite(ROJO,HIGH);
    hay_energia = false;
  }
  
  return hay_energia;
}