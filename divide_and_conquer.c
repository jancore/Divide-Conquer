#include "divide_and_conquer.h"

int string_length(const char* p_string) {
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

Result base_case(const char* p_problem, const int p_subsize, int p_limit, const int p_multiplier) {
    Result result = {p_subsize*p_multiplier, p_subsize*p_multiplier};
    int count = 1;

    p_limit = (p_limit < p_subsize) ? p_limit : p_subsize;
    for (int index = 1; index < p_limit; index++)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;
            if (count > (result.index_fin - result.index_init + 1)) {
                result.index_init = index - count + 1 + p_multiplier*p_subsize;
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

Result final_result(const char* p_problem, Result* p_solutions, const int p_num_solutions, int length) {
    Result solution = *p_solutions;
    
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
    
    for(int i = 1; i < p_num_solutions; i++)
    {
        if((solution.index_fin - solution.index_init) < ((p_solutions + i)->index_fin - (p_solutions + i)->index_init))
        {
            solution = *(p_solutions + i);
        }
    }
    
    return solution;
}

void recursive_case(Result* solutions, const char* p_problem, const int p_subsize, const int p_index) {
    int subsize = (p_subsize < 1) ? 1 : p_subsize;
    int length = string_length(p_problem);

    if (length <= subsize)
    {
        *(solutions + p_index) = base_case(p_problem, subsize, length, p_index);
    }
    else
    {
        *(solutions + p_index) = base_case(p_problem, subsize, subsize, p_index);        
        recursive_case(solutions, (p_problem + subsize), subsize, p_index + 1);
    }
}

Result DyV(const char* p_problem, const int p_subsize)
{
    int length = string_length(p_problem);
    int num_solutions = (length % p_subsize == 0) ? length / p_subsize : length / p_subsize + 1;
    Result* solutions = (Result*) malloc(num_solutions*sizeof(Result));
    
    recursive_case(solutions, p_problem, p_subsize, 0);
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