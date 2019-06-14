#include "divide_and_conquer.h"

#include <math.h>

int string_length(const char* p_string) {
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

int solution_size(const long p_multiplier, const int p_subsize, const int p_length)
{
    return (p_length/2 <= p_subsize) ? p_multiplier : solution_size(p_multiplier*2, p_subsize, p_length/2);
}

void copy_string(char* string_out, const char* string_in, const int p_index_init, const int p_index_fin)
{
    int i = p_index_init;
    while(*(string_in + i) != '\0' && i < p_index_fin)
    {
        *(string_out + i - p_index_init) = *(string_in + i);
        i++;
    }
    *(string_out + i) = '\0';
}

Result base_case(const char* p_problem, const int p_subsize, int p_limit, const int p_multiplier) {
    Result result = {p_multiplier, p_multiplier};
    int count = 1;

    p_limit = (p_limit < p_subsize) ? p_limit : p_subsize;
    for (int index = 1; index < p_limit; index++)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;
            if (count > (result.index_fin - result.index_init + 1)) {
                result.index_fin = index + p_multiplier;
                result.index_init = result.index_fin - count + 1;
            }
        }
        else
        {
            count = 1;
        }
    }
    return result;
}

Result final_result(const char* p_problem, Result* p_solutions, const int p_num_solutions, int length) {
    for(int i = 0; i < p_num_solutions; i++)
    {
        int index_init = (p_solutions + i)->index_init - 1;
        int index_fin = (p_solutions + i)->index_fin + 1;
        
        while(index_init > -1)
        {
            if(*(p_problem + index_init) == *(p_problem + (p_solutions + i)->index_init))
            {
                (p_solutions + i)->index_init--;
                index_init--;
            }
            else
            {
                index_init = -1;
            }
        }
        
        while(index_fin < length)
        {
            if(*(p_problem + index_fin) == *(p_problem + (p_solutions + i)->index_fin))
            {
                (p_solutions + i)->index_fin++;
                index_fin++;
            }
            else
            {
                index_fin = length;
            }
        }
    }
    
    Result solution = *p_solutions;
    
    for(int i = 1; i < p_num_solutions; i++)
    {
        if((solution.index_fin - solution.index_init) < ((p_solutions + i)->index_fin - (p_solutions + i)->index_init))
        {
            solution = *(p_solutions + i);
        }
    }
    
    return solution;
}

void recursive_case(Result* solutions, const char* p_problem, const int p_subsize, int* p_pappend, const int p_index_fin, int p_index) {
    if ((p_index_fin + 1) > p_subsize)
    {     
        recursive_case(solutions, p_problem, p_subsize, p_pappend, p_index_fin/2, p_index);
        recursive_case(solutions, (p_problem + p_index_fin/2 + 1), p_subsize, p_pappend, p_index_fin/2, p_index + p_index_fin/2 +1);
    }
    else
    {
        *(solutions + *p_pappend) = base_case(p_problem, p_subsize, p_index_fin + 1, p_index);
        *p_pappend = *p_pappend + 1;
    }
}

Result DyV(const char* p_problem, const int p_subsize)
{
    double subsize = (p_subsize < 1) ? 1.0 : (double)p_subsize;
    int length = string_length(p_problem);
    double aaaa = log2(subsize);
    double num_solutions = 5 - aaaa;
    Result* solutions = (Result*) malloc(num_solutions*sizeof(Result));
    int append = 0;
    int* pappend = &append;
    
    recursive_case(solutions, p_problem, subsize, pappend, length - 1, 0);
    Result result = final_result(p_problem, solutions, num_solutions, length);
    free(solutions);
    
    return result;
}

Result DyV_iter(const char* p_problem, const int p_subsize)
{
    Result result = {0, 0};
    int count = 1;
    int length = string_length(p_problem);

    for(int index = 1; index < length; index++)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;
            if (count > (result.index_fin - result.index_init + 1) && count <= p_subsize) {
                result.index_init = index - count + 1;
                result.index_fin = result.index_init + count - 1;
            }
        }
        else
        {
            count = 1;
        }
    }
    return result;
}