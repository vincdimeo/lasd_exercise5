
#include "test.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"

default_random_engine randomGenList;

void populateIntList(lasd::List<int>& lst, ulong size);
void populateFloatList(lasd::List<double>& lst, ulong size);
void populateStringList(lasd::List<string>& lst, ulong size);
void intHTClsAdrOperations(lasd::HashTableClsAdr<int>& ht);
void floatHTClsAdrOperations(lasd::HashTableClsAdr<double>& ht);
void stringHTClsAdrOperations(lasd::HashTableClsAdr<string>& ht);

using namespace std;

/* ************************************************************************** */

// Populate list with random integers elements

void populateIntList(lasd::List<int>& lst, ulong size) {
  uniform_int_distribution<int> dis(1, 100);

  for(ulong i = 0; i < size; i++) {
    lst.InsertAtBack(dis(randomGenList));
  }
}

/* ************************************************************************** */

// Populate list with random floats elements

void populateFloatList(lasd::List<double>& lst, ulong size) {
  uniform_real_distribution<float> dis(1, 100);

  for(ulong i = 0; i < size; i++) {
    lst.InsertAtBack(round(dis(randomGenList) * 100.0) / 100.0); // two decimals places
  }
}

/* ************************************************************************** */

// Populate list with random strings

void populateStringList(lasd::List<string>& lst, ulong size) {
  uniform_int_distribution<int> dis(1, 3);

  for(ulong i = 0; i < size; i++) {
    lst.InsertAtBack(getRandomString(dis(randomGenList)));
  }
}


/* ************************************************************************** */

void initializeHTClsAdr() {
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
        lasd::List<int> lst;
        populateIntList(lst, size);
        lasd::HashTableClsAdr<int> ht(size, lst);
        intHTClsAdrOperations(ht);
        break;
      }

      case 2: {
        lasd::List<double> lst;
        populateFloatList(lst, size);
        lasd::HashTableClsAdr<double> ht(size, lst);
        floatHTClsAdrOperations(ht);
        break;
      }

      case 3: {
        lasd::List<string> lst;
        populateStringList(lst, size);
        lasd::HashTableClsAdr<string> ht(size, lst);
        stringHTClsAdrOperations(ht);
        break;
      }

      default:
        cout << "Scelta non disponibile!" << endl << endl;
    }
  } while((type < 1) || (type > 3));
}

/* ************************************************************************** */

// int HTClsAdr operations

void intHTClsAdrOperations(lasd::HashTableClsAdr<int>& ht) {
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

// float HTClsAdr operations

void floatHTClsAdrOperations(lasd::HashTableClsAdr<double>& ht) {
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

// string HTClsAdr operations

void stringHTClsAdrOperations(lasd::HashTableClsAdr<string>& ht) {
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
