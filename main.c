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
#include <errno.h>

int main(int argc, char** argv)
{
    int m = 5;
    char* C = (char*) malloc(1000*sizeof(char));
    
    if (argc == 2)
    {
        m = atoi(argv[1]);
    }
    else
    {
        fprintf(stderr, "Wrong number of arguments\nUse: ./program <m>\n");
        exit(EXIT_FAILURE);
    }

    while(gets(C))
    {
        //printf("Cadena: \"%s\", Longitud subcadena: %d\n", C, m);
        
        Result result = DyV(C, m);    
        printf("RECURSIVO -> Indice: %d, Repeticiones: %d\n", result.index_init, result.repetitions);
        result = DyV_iter(C, m);
        printf("ITERATIVO -> Indice: %d, Repeticiones: %d\n\n", result.index_init, result.repetitions);
    }
    
    return 1;
}

