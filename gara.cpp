/*

  Titolo:  Libreria per gara siemens
  Obbiettivo: Facilitare uso PTO, e la lavorazione delle stringhe
  Autore: Andrea Micheli 

*/


/*

  N.B. L'integrato lavora in logica negativa

*/

//Includo il file header gara.h dove inizializzo tutte le funzioni, e anche la libreria string per le stringhe
#include "gara.h"
#include <string.h>


static int _dir, _en, _cp;
static int a1, b1;
static int a2, b2;
static int lastEncoded = 0;
static long encoderValue = 0;
static long lastencoderValue = 0;

//Inizializzo tutta la classe
gara::gara() {

}


//Funzione per convertitre una stringa in intero

//Il puntatore denominato s sarà la variabile stringa che dovrà essere convertira
int gara::strToint(char *s) {
  //Variabile per la conversione
  int k = 0;
  int p = 1;
  int ref = 0;
  //Salvo il valore di locazioni volute da converitre della variabile s e lo metto in k, mi serve per fare il cilco
  k = strlen(s) - 2;
  while (k >= 0) {
    ref = ref + ((s[k] - 48) * p); //La variabile stessa viene aggiornata con il suo valore precedente con la locazione di s - 48 (per arrivare ad avere solo i caratteri numerici cfr Ascii table) e lo moltiplico con p, che mi va significare il valore dell'unità     
    k--;
    p *= 10;
  }
  k = 0;
  return ref; //Una volta eseeguita tutta la conversione ritorno il valore intero
}


//Funzione per impostare i pin per l'uso del pto

//Nella funzione prendo i numeri dei pin che devo usare
void gara::ptoSetup(int dir, int en, int cp) {  
  //Salvo questi pin nelle variabili statiche precedentemente dichiarate, poichè mi serviranno in altre funzioni
  _dir = dir;
  _en = en;
  _cp = cp;
  //Dichiaro questi pin come uscite
  pinMode(dir, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(cp, OUTPUT);
  //Mando un impulso al pin enable, deve stare basso perche lavora in logica negativa
  digitalWrite(_en, HIGH);
  delay(10);
  digitalWrite(_en, LOW);
}


//Funzione per la generazione del treno ad impulsi

//Nella funzione, la var n sta ad indicare il nuemro di impulsi, la var bool in che verso si intende ruotare, e la var d sta ad indicare il ritardo che c'è tra ogni impulso, quindi d è il periodo T
void gara::impGen(int n, boolean dir, int d) { 
  //Setto l'uscita della direzione indicando in che verso intendo ruotare
  digitalWrite(_dir,dir);
  //Eseguo questo ciclo fin quando non esaurisco il numero di impilsi deciso dall'utente
  while (n > 0) {
    digitalWrite(_cp,HIGH);
    Serial.println("alto");
    delayMicroseconds(d);
    digitalWrite(_cp,LOW);
    Serial.println("basso");
    delayMicroseconds(d);
    n--;
  }
  this->done = true;
}  

void gara::encSetup1(int pin_a, int pin_b) {
  pinMode(pin_a, INPUT);
  pinMode(pin_b, INPUT);
  a1 = pin_a;
  b1 = pin_b;
}

void gara::encSetup2(int pin_a, int pin_b) {
  pinMode(pin_a, INPUT);
  pinMode(pin_b, INPUT);
  a2 = pin_a;
  b2 = pin_b;
}


//Funzione per leggere l'encoder incrementale

//I due valori che prendo nella funzione sono i valori logici degli ingressi, li chiamo msb e lsb perche adesso li devo convertire in binario
int gara::encRead(int b) {
  //Salvo nella variabile encoded il valore msb shiftando i bit a sinistra di 1 e e facendo un or logico bit a bit con il valore di lsb
 /* int encoded = (MSB << 1) | LSB; 
  //Vado a fare la somma dei due valore convertiti
  int sum = (lastEncoded << 2) | encoded;
  //Codnizioni per cui gira solo in un senso
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue++;
  }
  //Condizioni per cui gira nell'altro senso
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue--;
  }  
  lastEncoded = encoded;*/
  if(b) {
    encoderValue--;
  } else {
    encoderValue++;
  }
  return encoderValue;
  return encoderValue;
}
