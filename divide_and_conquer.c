/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "divide_and_conquer.h"

Result Result_default = {-1, 1};

int string_length(const char* p_string)
{
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

void copy_string(char* string_out, char* string_in)
{
    int i = 0;
    while(*(string_in + i) != '\0')
    {
        *(string_out + i) = *(string_in + i);
        i++;
    }
    *(string_out + i) = '\0';
}

void problem_division(const char* p_string, const int p_subsize, char** p_sub_problems, int* num_solutions)
{
    int length = string_length(p_string);
    int i, j;
    char string_aux[p_subsize + 1];

    int tam = (length % p_subsize == 0) ? length / p_subsize : length / p_subsize + 1;
    *num_solutions = tam;
    p_sub_problems = (char**) realloc(p_sub_problems, tam * sizeof (char*));
    
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < p_subsize; j++)
        {
            if (*(p_string + i * p_subsize + j) == '\0')
            {
                break;
            }
            else
            {
                string_aux[j] = *(p_string + i * p_subsize + j);
            }
        }
        string_aux[j] = '\0';
        *(p_sub_problems + i) = (char*) malloc( (j + 1) * sizeof(char));
        copy_string(*(p_sub_problems + i), string_aux);
    }
}

Result DC_iterative(const char* p_problem, const int p_subsize)
{
    Result result = Result_default;
    int index = 1;
    int count = 1;
    int length = string_length(p_problem);

    while (index < length)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;

            if (count >= result.repetitions && count <= p_subsize)
            {
                result.repetitions = count;
                result.index = index - count + 1;
                result.character = *(p_problem + result.index);
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

Result final_result(const int p_subsize, const int num_solutions, char** sub_problems, Result* partial_solutions)
{
    Result solution = Result_default;
    Result final_solution;
    final_solution.index = p_subsize*num_solutions;

    for (int i = 0; i < num_solutions; i++)
    {        
        int anterior_index = 0;
        if (solution.repetitions <= (partial_solutions + i)->repetitions)
        {
            int j = 0;
            solution = *(partial_solutions + i);

            if (*(*(sub_problems + i) + solution.index + solution.repetitions) == '\0')
            {
                if ((i + 1) < num_solutions && j < p_subsize)
                {
                    while (*(*(sub_problems + i + 1) + j) == solution.character)
                    {
                        solution.repetitions++;
                        j++;
                    }
                }
            }

            j = p_subsize - 1;
            if (solution.index == 0)
            {
                if ((i - 1) > -1 && j > -1)
                {
                    while (*(*(sub_problems + i - 1) + j) == solution.character)
                    {
                        solution.repetitions++;
                        anterior_index++;
                        j--;
                    }
                }
            }

            solution.index = solution.index + i*p_subsize - anterior_index;
        }

        if(solution.index < final_solution.index)
            final_solution = solution;
    }

    return final_solution;
}

Result DC_recursive(const char* p_problem, const int p_subsize)
{
    if (string_length(p_problem) <= p_subsize)
    {
        return DC_iterative(p_problem, p_subsize);
    }
    else
    {
        int num_solutions;
        char** sub_problems = (char**) malloc(sizeof (char*));
        *sub_problems = (char *) NULL;

        problem_division(p_problem, p_subsize, sub_problems, &num_solutions);
        
        Result partial_solutions[num_solutions];
        
        for (int i = 0; i < num_solutions; i++)
        {
            Result solution = DC_recursive(*(sub_problems + i), p_subsize);
            partial_solutions[i] = solution;
        }
        Result result = final_result(p_subsize, num_solutions, sub_problems, partial_solutions);

        for (int i = 0; i < num_solutions; i++)
        {
            free(*(sub_problems + i));
        }
        free(sub_problems);

        return result;
    }
}