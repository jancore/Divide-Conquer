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
    int index_init;
    int index_fin;
    int repetitions;
};

typedef struct Result_s Result;

int string_length(const char* p_string);

void base_case(const char* p_problem, const int p_subsize, int p_limit, const int p_offset, Result* p_solution);

Result final_result(const char* p_problem, const int p_subsize, Result** p_solutions, const int p_num_solutions, const int p_length);

void recursive_case(Result** solutions, int* p_num_solutions, const char* p_problem, const int p_subsize, int* p_pappend, const int p_length, int p_index);

Result DyV(const char* p_problem, const int p_subsize);

Result DyV_iter(const char* p_problem, const int p_subsize); 

#endif /* DIVIDE_AND_CONQUER_H */

