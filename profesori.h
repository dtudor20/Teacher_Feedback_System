#include <iostream>
using namespace std;

struct evaluare {
    string recenzie;
    int stele;

    evaluare() : stele(0) {}
};

class PROFESOR
{
private:
    string nume;
    int nr_evaluari;
    evaluare* new_evaluare; 
public:
    static int profesori; 
    static PROFESOR* a; 

    PROFESOR();
    PROFESOR(const PROFESOR& other); // Copy constructor
    PROFESOR& operator=(const PROFESOR& other); // Copy assignment operator
    ~PROFESOR();

    static void cautare_profesor();
};
