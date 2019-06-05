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
#include <string.h>

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
    Result result = DyV(C, m);    
    printf("Indice: %d, Repeticiones: %d\n", result.index_init, result.index_fin - result.index_init + 1);
    
    return 0;
}

