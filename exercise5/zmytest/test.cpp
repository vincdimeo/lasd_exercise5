
#include "test.hpp"

default_random_engine randomGenerator;

/* ************************************************************************** */

// Menu to choose the the structure and the type of the structure

void chooseStructureNType() {
  ulong str;

  do {
    cout << "SELEZIONA IL TIPO DI IMPLEMENTAZIONE" << endl
         << "1 - Open Addressing" << endl
         << "2 - Closed Addressing" << endl
         << "Scelta: ";
    cin >> str;
    cout << endl;

    switch (str) {
      case 1:
        initializeHTOpnAdr();
        break;
      case 2:
        initializeHTClsAdr();
        break;
      default:
        cout << "Scelta non disponibile!" << endl << endl;
    }
  } while((str != 1) && (str != 2));
}

/* ************************************************************************** */

// Method that generates a random string

string getRandomString(int n) {
  char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                      'o','p','q','r','s','t','u','v','w','x','y','z'};
  string ran = "";

  for (int i = 0; i < n; i++) {
    ran = ran + letters[rand() % 26];
  }

  return ran;
}

/* ************************************************************************** */

// Shared menu for HTOpnAdr and HTClsAdr

void sharedMenu() {
  cout << "DIGITA L'OPERAZIONE DA COMPIERE" << endl
       << "1 - Visualizzazione tutti gli elementi" << endl
       << "2 - Controlla l'esistenza di un valore" << endl;
}

/* ************************************************************************** */

// Shared menu for integers Hashtables

void intSharedMenu() {
  cout << "3 - Moltiplica gli interi minori di un determinato numero" << endl << endl;
}

/* ************************************************************************** */

// Shared menu for float Hashtables

void floatSharedMenu() {
  cout << "3 - Somma i float maggiori di un determinato numero" << endl << endl;
}

/* ************************************************************************** */

// Shared menu for strings Hashtables

void stringSharedMenu() {
  cout << "6 - Concatena le stringhe con lunghezza minore o uguale a un determinato numero" << endl << endl;
}

/* ************************************************************************** */

// Print an integer element

void printIntElement(int& element, void* b) {
  cout << element << " ";
}

/* ************************************************************************** */

// Print a float element

void printFloatElement(double& element, void* b) {
  cout << element << " ";
}

/* ************************************************************************** */

// Print a string

void printStringElement(string& element, void* b) {
  cout << element << " ";
}

/* ************************************************************************** */

// Multiply elements less than n

void multiplyIntLessThan(const int element, const void* n, void* prod) {
  if(element < *((int*)n)) {
    *((int*)prod) = (element) * (*((int*)prod));
  }
}

/* ************************************************************************** */

// Sum integers less than n

void sumFloatGreatherThan(const double element, const void* n, void* sum) {
  if(element > *((double*)n)) {
    *((double*)sum) = element + *((double*)sum);
  }
}

/* ************************************************************************** */

// Concatenate strings

void concatenateStrings(const string element, const void* length, void* conc) {
  if(element.length() <= *((int*)length)) {
    *((string*)conc) = *((string*)conc) + element;
  }
}

/* ************************************************************************** */
