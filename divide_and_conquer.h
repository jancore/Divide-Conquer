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
    int repetitions;
};

typedef struct Result_s Result;

int string_length(const char* p_string);

int solution_size(const long p_multiplier, const int p_subsize, const int p_length);

void copy_string(char* string_out, const char* string_in, const int p_index_init, const int p_index_fin);

Result base_case(const char* p_problem, const int p_subsize, int p_limit, const int p_multiplier);

Result final_result(const char* p_problem, const int p_subsize, Result* p_solutions, const int p_num_solutions, int length);

void recursive_case(Result* solutions, int* p_num_solutions, const char* p_problem, const int p_subsize, int* p_pappend, const int p_index_fin, int p_index);

Result DyV(const char* p_problem, const int p_subsize);

Result DyV_iter(const char* p_problem, const int p_subsize); 

#endif /* DIVIDE_AND_CONQUER_H */

