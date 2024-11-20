#include "profesori.h"
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int PROFESOR::profesori = 0;
PROFESOR* PROFESOR::a = nullptr;

PROFESOR::PROFESOR() : nume(""), new_evaluare(nullptr), nr_evaluari(0) {}

// Copy constructor
PROFESOR::PROFESOR(const PROFESOR& other) : nume(other.nume), nr_evaluari(other.nr_evaluari) {
    if (other.new_evaluare) {
        new_evaluare = new evaluare[nr_evaluari];
        for (int i = 0; i < nr_evaluari; ++i) {
            new_evaluare[i] = other.new_evaluare[i];
        }
    }
    else {
        new_evaluare = nullptr;
    }
}

// Copy assignment operator
PROFESOR& PROFESOR::operator=(const PROFESOR& other) {
    if (this == &other) {
        return *this;
    }

    delete[] new_evaluare;

    nume = other.nume;
    nr_evaluari = other.nr_evaluari;

    if (other.new_evaluare) {
        new_evaluare = new evaluare[nr_evaluari];
        for (int i = 0; i < nr_evaluari; ++i) {
            new_evaluare[i] = other.new_evaluare[i];
        }
    }
    else {
        new_evaluare = nullptr;
    }

    return *this;
}

void PROFESOR::cautare_profesor() {
    cout << "Introduceti numele si prenumele profesorului: ";
    string s;
    bool ok = false;
    getline(cin, s);

    for (int i = 0; i < profesori; i++) {
        if (s == a[i].nume) {
            ok = true;
            cout << "Profesor gasit. Cum doriti sa fie afisate evaluarile?\n";
            cout << "1. In ordine cronologica\n";
            cout << "2. Evaluarile proaste primele\n";
            cout << "3. Evaluarile bune primele\n";
            cout << "4. Doresc sa adaug o evaluare\n";

            int alegere;
            cin >> alegere;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character left by cin

            switch (alegere) {
            case 1:
                for (int n = 0; n < a[i].nr_evaluari; n++) {
                    cout << a[i].new_evaluare[n].recenzie << endl;
                    for (int stea = 1; stea <= 5; stea++) {
                        cout << (stea <= a[i].new_evaluare[n].stele ? "*" : "0");
                    }
                    cout << endl;
                }
                break;
            case 2:
                for (int m = 1; m <= 5; m++) {
                    for (int n = 0; n < a[i].nr_evaluari; n++) {
                        if (a[i].new_evaluare[n].stele == m) {
                            cout << a[i].new_evaluare[n].recenzie << endl;
                            for (int stea = 1; stea <= 5; stea++) {
                                cout << (stea <= a[i].new_evaluare[n].stele ? "*" : "0");
                            }
                            cout << endl;
                        }
                    }
                }
                break;
            case 3:
                for (int m = 5; m >= 1; m--) {
                    for (int n = 0; n < a[i].nr_evaluari; n++) {
                        if (a[i].new_evaluare[n].stele == m) {
                            cout << a[i].new_evaluare[n].recenzie << endl;
                            for (int stea = 1; stea <= 5; stea++) {
                                cout << (stea <= a[i].new_evaluare[n].stele ? "*" : "0");
                            }
                            cout << endl;
                        }
                    }
                }
                break;
            case 4: {
                evaluare* new_evaluare_array = new evaluare[a[i].nr_evaluari + 1];
                for (int j = 0; j < a[i].nr_evaluari; j++) {
                    new_evaluare_array[j] = a[i].new_evaluare[j];
                }
                delete[] a[i].new_evaluare;
                a[i].new_evaluare = new_evaluare_array;
                a[i].nr_evaluari++;
                cout << "Scrieti evaluarea dumneavoastra si apoi acordati un nr de stele de la 1 la 5\n";
                getline(cin, a[i].new_evaluare[a[i].nr_evaluari - 1].recenzie);
                int aux;
                cin >> aux;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character left by cin
                while (aux > 5 || aux < 1) {
                    cout << "Nr de stele trebuie sa fie intre 1 si 5. Alegeti din nou\n";
                    cin >> aux;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character left by cin
                }
                a[i].new_evaluare[a[i].nr_evaluari - 1].stele = aux;
            }
                  break;
            }
        }
    }

    if (!ok) {
        cout << "Profesorul nu are recenzii. Apasati 1 pentru a adauga una\n";
        int b;
        cin >> b;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character left by cin
        if (b == 1) {
            PROFESOR* new_a = new PROFESOR[profesori + 1];
            for (int i = 0; i < profesori; i++) {
                new_a[i] = a[i];
            }
            delete[] a;
            a = new_a;

            a[profesori].nume = s;
            a[profesori].new_evaluare = new evaluare[1];
            a[profesori].nr_evaluari = 1;

            cout << "Scrieti evaluarea dumneavoastra si apoi acordati un nr de stele de la 1 la 5\n";
            getline(cin, a[profesori].new_evaluare[0].recenzie);
            int aux;
            cin >> aux;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character left by cin
            while (aux > 5 || aux < 1) {
                cout << "Nr de stele trebuie sa fie intre 1 si 5. Alegeti din nou\n";
                cin >> aux;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character left by cin
            }
            a[profesori].new_evaluare[0].stele = aux;
            profesori++;
        }
    }
}

PROFESOR::~PROFESOR() {
    delete[] new_evaluare;
}
