#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <list>
#include <iterator>
#include <map>

using namespace std;

struct solucion {
    int indice;
    int repeticiones;

    solucion(int indice, int repeticiones) {
        this->indice = indice;
        this->repeticiones = repeticiones;
    }

    void imprimir() {
        cout << this->indice << ", " << this->repeticiones << endl;
    }
};

solucion * solucionBase(const char * cadena, int i, int j) {
    int k = i;
    map<char, int> ocurrencias;
    int maximo = 0;
    
    for(i; i < j+1; i++) {
        map<char, int>::iterator it = ocurrencias.find(cadena[i]);
        if(it != ocurrencias.end()) {
            it->second++;
        } else {
            ocurrencias.insert(pair<char, int>(cadena[i], 1));
        }
    }

    for(map<char, int>::iterator it = ocurrencias.begin(); it != ocurrencias.end(); it++) {
        if(it->second > maximo) maximo = it->second;
    }

    //sumamos uno porque la solucion empieza desde indice 1, no 0 (por cumplir con la especificación del problema)
    return new solucion(k+1, maximo); 

}

solucion * divideYVenceras(const char * cadena, int i, int j, int m) {
    solucion *solucionizda, *soluciondrcha;
    int cadenalen = j-i +1;
    bool mpar;

    //funcion esmejor(solucion, solucion)
    if((m-1) % 2 == 0)
        mpar = true;
    else
        mpar = false;

    //funcion espequeno()
    if(cadenalen <= m) {
        return solucionBase(cadena, i, j);
    }
    else {
        if(!mpar) {
            solucionizda = divideYVenceras(cadena, i, i+(cadenalen/2-1) + (m-1)/2+1, m);
            soluciondrcha = divideYVenceras(cadena, i+(cadenalen/2) - (m-1)/2, j, m);
        } 
        else {
            solucionizda = divideYVenceras(cadena, i,i+(cadenalen/2-1) + (m-1)/2, m);
            soluciondrcha = divideYVenceras(cadena, i+(cadenalen/2) - (m-1)/2, j, m);
        }

        //funcion esmejor
        if(solucionizda->repeticiones >= soluciondrcha->repeticiones) {
            delete(soluciondrcha);
            return solucionizda;
        }
        else {
            delete(solucionizda);
            return soluciondrcha;
        }
    }
}


int main(int argc, char const *argv[])
{
    string cadena;
    int m = atoi(argv[1]);

    while(cin>>cadena) 
    {

        const char * str = cadena.c_str();
        int cadenalen = strlen(str);

        solucion * solucion = divideYVenceras(str, 0, cadenalen-1, m);

        solucion->imprimir();
    
    }

    return 0;
}
