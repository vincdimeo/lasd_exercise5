
#include "test.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

default_random_engine randomGenVec;

void populateIntVector(lasd::Vector<int>& vec);
void populateFloatVector(lasd::Vector<double>& vec);
void populateStringVector(lasd::Vector<string>& vect);
void intHTOpnAdrOperations(lasd::HashTableOpnAdr<int>& ht);
void floatHTOpnAdrOperations(lasd::HashTableOpnAdr<double>& ht);
void stringHTOpnAdrOperations(lasd::HashTableOpnAdr<string>& ht);

using namespace std;

/* ************************************************************************** */

// Populate vector with random integers elements

void populateIntVector(lasd::Vector<int>& vec) {
  uniform_int_distribution<int> dis(1, 100);

  for(ulong i = 0; i < vec.Size(); i++) {
    vec[i] = dis(randomGenVec);
  }
}

/* ************************************************************************** */

// Populate vector with random floats elements

void populateFloatVector(lasd::Vector<double>& vec) {
  uniform_real_distribution<float> dis(1, 100);

  for(ulong i = 0; i < vec.Size(); i++) {
    vec[i] = round(dis(randomGenVec) * 100.0) / 100.0; // two decimals places
  }
}

/* ************************************************************************** */

// Populate vector with random strings

void populateStringVector(lasd::Vector<string>& vec) {
  uniform_int_distribution<int> dis(1, 3);

  for(ulong i = 0; i < vec.Size(); i++) {
    vec[i] = getRandomString(dis(randomGenVec));
  }
}


/* ************************************************************************** */

void initializeHTOpnAdr() {
  ulong type = 0, size = 0;

  do {
    cout << "DIGITA LA DIMENSIONE DELLA TUA HASHTABLE" << endl
         << "Scelta: ";
    cin >> size;
    cout << endl;

    if(size <= 0) {
      cout << "La dimensione deve essere maggiore di zero!" << endl << endl;
    }
  } while(size <= 0);

  do {
    cout << "SELEZIONA IL TIPO DI DATO" << endl
         << "1 - Int" << endl
         << "2 - Float" <<endl
         << "3 - String" << endl
         << "Scelta: ";
    cin >> type;
    cout << endl;

    switch (type) {
      case 1: {
        lasd::Vector<int> vec(size);
        populateIntVector(vec);
        lasd::HashTableOpnAdr<int> ht(size, vec);
        intHTOpnAdrOperations(ht);
        break;
      }

      case 2: {
        lasd::Vector<double> vec(size);
        populateFloatVector(vec);
        lasd::HashTableOpnAdr<double> ht(size, vec);
        floatHTOpnAdrOperations(ht);
        break;
      }

      case 3: {
        lasd::Vector<string> vec(size);
        populateStringVector(vec);
        lasd::HashTableOpnAdr<string> ht(size, vec);
        stringHTOpnAdrOperations(ht);
        break;
      }

      default:
        cout << "Scelta non disponibile!" << endl << endl;
    }
  } while((type < 1) || (type > 3));
}

/* ************************************************************************** */

// int HTOpnAdr operations

void intHTOpnAdrOperations(lasd::HashTableOpnAdr<int>& ht) {
  ulong choice = 0, again = 0;

  do {
    do {
      sharedMenu();
      intSharedMenu();
      cout << "Scelta: ";
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Elementi della hashtable: ";
          ht.Map(printIntElement, 0);
          cout << endl << endl;
          break;
        }

        case 2: {
          int find;
          cout << "Digita l'elemento da cercare: ";
          cin >> find;

          if (ht.Exists(find)) {
            cout << "L'elemento " << find << " esiste all'interno della hashtable" << endl << endl;
          }
          else {
            cout << "L'elemento " << find << " non esiste all'interno della hashtable" << endl << endl;
          }
          break;
        }

        case 3: {
          int n = 0, prod = 1;
          cout << "Digita un numero: ";
          cin >> n;
          ht.Fold(multiplyIntLessThan, &n, &prod);
          cout << "Il prodotto degli elementi minori di " << n << " e' pari a: " << prod << endl << endl;
          break;
        }

        default:
          cout << "Scelta non disponibile!" << endl << endl;
      }
    } while(choice < 1 || choice > 3);

    cout << "Continuare?" << endl
         << "1 - Si" << endl
         << "0 - No" << endl
         << "Scelta: ";
    cin >> again;
    cout << endl;
  } while(again);
}

/* ************************************************************************** */

// float HTOpnAdr operations

void floatHTOpnAdrOperations(lasd::HashTableOpnAdr<double>& ht) {
  ulong choice = 0, again = 0;

  do {
    do {
      sharedMenu();
      floatSharedMenu();
      cout << "Scelta: ";
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Elementi della hashtable: ";
          ht.Map(printFloatElement, 0);
          cout << endl << endl;
          break;
        }

        case 2: {
          double find;
          cout << "Digita l'elemento da cercare: ";
          cin >> find;

          if (ht.Exists(find)) {
            cout << "L'elemento " << find << " esiste all'interno della hashtable" << endl << endl;
          }
          else {
            cout << "L'elemento " << find << " non esiste all'interno della hashtable" << endl << endl;
          }
          break;
        }

        case 3: {
          double n, sum = 0;
          cout << "Digita un numero: ";
          cin >> n;
          ht.Fold(sumFloatGreatherThan, &n, &sum);
          cout << "La somma dei float maggiori di " << n << " e' pari a: " << sum << endl << endl;
          break;
        }

        default:
          cout << "Scelta non disponibile!" << endl << endl;
      }
    } while(choice < 1 || choice > 3);

    cout << "Continuare?" << endl
         << "1 - Si" << endl
         << "0 - No" << endl
         << "Scelta: ";
    cin >> again;
    cout << endl;
  } while(again);
}

/* ************************************************************************** */

// string HTOpnAdr operations

void stringHTOpnAdrOperations(lasd::HashTableOpnAdr<string>& ht) {
  ulong choice = 0, again = 0;

  do {
    do {
      sharedMenu();
      stringSharedMenu();
      cout << "Scelta: ";
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Elementi della hashtable: ";
          ht.Map(printStringElement, 0);
          cout << endl << endl;
          break;
        }

        case 2: {
          string find = "";
          cout << "Digita la stringa da cercare: ";
          cin >> find;

          if (ht.Exists(find)) {
            cout << "La stringa " << find << " esiste all'interno della hashtable" << endl << endl;
          }
          else {
            cout << "La stringa " << find << " non esiste all'interno della hashtable" << endl << endl;
          }
          break;
        }

        case 3: {
          int length;
          string conc = "";
          cout << "Digita la lunghezza delle stringhe da concatenare: ";
          cin >> length;
          ht.Fold(concatenateStrings, &length, &conc);
          cout << "Stringhe di lunghezza minore o uguale a " << length << " concatenate: " << conc << endl << endl;
          break;
        }

        default:
          cout << "Scelta non disponibile!" << endl << endl;
      }
    } while(choice < 1 || choice > 3);

    cout << "Continuare?" << endl
         << "1 - Si" << endl
         << "0 - No" << endl
         << "Scelta: ";
    cin >> again;
    cout << endl;
  } while(again);
}
