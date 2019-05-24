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

#include <cstdlib>
#include <stdio.h>

struct Result
{
    int index = -1;
    int repetitions = 1;
    char character;
};

int string_length(const char* p_string)
{
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

void problem_division(char* p_string, int p_subsize, char* p_sub_problems)
{
    int length = string_length(p_string);
    
    if(length % p_subsize == 0)
    {
        int tam = length/p_subsize;
        free(p_sub_problems);
        //p_sub_problems = malloc(p_subsize*sizeof(char*));
        for(int i = 0; i < length; i++)
        {
        }
    }
}

Result DC_iterative(const char* p_problem, const int p_subsize)
{
    Result result;
    int index = 1;
    int count = 1;
    int length = string_length(p_problem);
    
    while (index < length)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;

            if (count > result.repetitions && count <= p_subsize)
            {
                result.repetitions = count;
                result.index = index - count + 1;
            }

            index++;
        }
        else
        {
            count = 1;
            index++;
        }
    }

    return result;
}

Result DC_recursive(const char* p_problem, const int p_subsize)
{
    Result result;
    result.index = 1;
    char* sub_problems;
    sub_problems = malloc(p_subsize * sizeof(char*));
    int length = string_length(p_problem);

    if (p_subsize == 0)
    {
        return result;
    }
    else
    {
        if (*(p_problem) == *(p_problem + 1))
        {
            Result aux = DC_recursive(p_problem + 1, p_subsize - 1);
            result.index += aux.index;
            result.repetitions += aux.repetitions;
            return result;
        }
        else
        {
            result.index = 0;
            result.repetitions = 0;
            return result;
        }
    }
}

int main(int argc, char** argv)
{
    char C[] = "abceeeeksrzzzyx";
    int m = 5;

    Result result = DC_recursive(C, m);
    printf("Indice: %d, Repeticiones: %d", result.index, result.repetitions);

    return 0;
}

