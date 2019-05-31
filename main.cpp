/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: smarlogy
 *
 * Created on 21 de mayo de 2019, 18:13
 */
#include "divide_and_conquer.h"

int main(int argc, char** argv)
{
    int m = 5;
    char C[] = "abceeeeksrzzzyx";
    
    if (argc > 2)
    {
        strcpy(C, argv[1]);
        m = atoi(argv[2]);
    }

    printf("Cadena: \"%s\", Longitud subcadena: %d\n", C, m);
    Result result = DC_recursive(C, m);
    printf("Indice: %d, Repeticiones: %d, Caracter: \"%c\"\n", result.index, result.repetitions, result.character);

    return 0;
}

