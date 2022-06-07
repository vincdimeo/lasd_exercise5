
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
typedef unsigned long ulong;

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2022" << std::endl;

  ulong choice = 0;

  do {
    cout << "COSA VUOI ESEGUIRE?" << endl
         << "1 - Test docente" << endl
         << "2 - Test di esecuzione" << endl
         << "Scelta: ";
    cin >> choice;
    cout << endl;
    if (choice == 1) {
      lasdtest(); // To call in the menu of your library test!
    }
    else if (choice == 2){
      chooseStructureNType(); // User test
    }
    else {
      cout << "Scelta non disponibile!" << endl << endl;
    }
  } while((choice != 1) && (choice != 2));

  return 0;
}
