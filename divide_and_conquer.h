/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   divide&conquer.h
 * Author: smarlogy
 *
 * Created on 31 de mayo de 2019, 13:41
 */

#ifndef DIVIDE_AND_CONQUER_H
#define DIVIDE_AND_CONQUER_H

#include <stdio.h>
#include <stdlib.h>

struct Result_s
{
    int index;
    int repetitions;
    char character;
};

typedef struct Result_s Result;

int string_length(const char* p_string);

void copy_string(char* string_out, char* string_in);

void problem_division(const char* p_string, const int p_subsize, char** p_sub_problems, int* num_solutions);

Result DC_iterative(const char* p_problem, const int p_subsize);

Result final_result(const int p_subsize, const int num_solutions, char** sub_problems, Result* partial_solutions);

Result DC_recursive(const char* p_problem, const int p_subsize);


#endif /* DIVIDE_AND_CONQUER_H */

