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
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{   
    int m;
    char * str;
    if (argc == 2) {
        m = atoi(argv[1]);
    } else {
        fprintf(stderr, "Wrong number of arguments\nUse: ./program <m>\n");
        exit(EXIT_FAILURE);
    }

    while( gets(str) ) {
        //printf("Cadena: \"%s\", Longitud subcadena: %d\n", str, m);
        Result result = DyV(str, m);    
        //printf("Indice: %d, Repeticiones: %d\n", result.index_init, result.index_fin - result.index_init + 1);
        printf("%d, %d\n", result.index_init, result.index_fin - result.index_init + 1);
    }
  
    return 1;
}

