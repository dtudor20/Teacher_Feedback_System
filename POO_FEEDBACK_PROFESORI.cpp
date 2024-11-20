#include "profesori.h"
/*Adaugare 2 - 3 modalitati de vedere ale feedbackului.
Intreb la inceput
Profesorul isi poate vedea evaluarile si eventual o medie ale stelelor

struct evaluare {
    string recenzie;
    int stele;

    evaluare() : stele(0) {} 
};

struct profesor {
    string nume;
    evaluare* b;
    int evaluari;

    profesor() : b(nullptr), evaluari(0) {} 
};
*/
int profesori;
int main() {
    int t = 1;
    PROFESOR* a = new PROFESOR[profesori];
    do {
        PROFESOR::cautare_profesor();
    } while (t);

    for (int i = 0; i < profesori; i++) {
        a[i].~PROFESOR();
    }
    
    delete[] a; 
    return 0;
}
