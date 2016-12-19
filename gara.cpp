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

//Inizializzo tutta la classe
gara::gara() {

}

    static int _dir, _en, _cp;
    static int a1, b1;
    static int a2, b2;

//Funzione per convertitre una stringa in intero

//Il puntatore denominato s sarà la variabile stringa che dovrà essere convertira, mentre la variabile dif sarà il numero di caratteri
//da togliere alla fine della stringa
int gara::strToint(char *s, int dif) {
 //Se s, togliendo il numero di caratteri che non si vogliono convertire è pari a 0 significa che la stringa non contine altri caratteri e perciò ritorno il valore intero di NULL ed esco dalla funzione
 if ((sizeof(s) - dif) == 0) {
    return (int)NULL;
    exit;
  } else {
    //Variabile per la conversione
    int k = 0;
    int p = 1;
    int ref = 0;
    //Salvo il valore di locazioni volute da converitre della variabile s e lo metto in k, mi serve per fare il cilco
    k = sizeof(s) - dif;
    while (k >= 0) {
      ref = ref + ((s[k] - 48) * p); //La variabile stessa viene aggiornata con il suo valore precedente con la locazione di s - 48 (per arrivare ad avere solo i caratteri numerici cfr Ascii table) e lo moltiplico con p, che mi va significare il valore dell'unità     
      k--;
      p *= 10;
    }
    k = 0;
    return ref; //Una volta eseeguita tutta la conversione ritorno il valore intero
  }
}


//Funzione per impostare i pin per l'uso del pto

//Nella funzione prendo i numeri dei pin che devo usare
void gara::ptoSetup(int dir, int en, int cp) {
  if (dir != NULL && en != NULL && cp != NULL) {  
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
  } else {
    exit;
  }
}


//Funzione per la generazione del treno ad impulsi

//Nella funzione, la var n sta ad indicare il nuemro di impulsi, la var bool in che verso si intende ruotare, e la var d sta ad indicare il ritardo che c'è tra ogni impulso, quindi d è il periodo T
void gara::impGen(int n, boolean dir, int d) {
  if (n != NULL && d != NULL) { 
    //Setto l'uscita della direzione indicando in che verso intendo ruotare
    digitalWrite(_dir,dir);
    //Eseguo questo ciclo fin quando non esaurisco il numero di impilsi deciso dall'utente
    while (n > 0) {
      digitalWrite(_cp,HIGH);
      delay(d / 2);
      digitalWrite(_cp,LOW);
      delay(d / 2);
      n--;
    }
  } else {
    exit;
  }
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

int gara::encRead(int a, int b) {
  Serial.println(a);
  Serial.println(b);
}


char* gara::readSerial(char endL) {
  if (Serial.available() > 0) {
    int asci, i = 0;
    char *str;
    char s[100];
    do {
      asci = Serial.read();
      s[i] = asci;
      i++;
    } while (asci != endL);
    str = s;
    return str;
  } else {
    return NULL;
  }
}
