#include "divide_and_conquer.h"

int string_length(const char* p_string) {
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

Result DC_iterative(const char* p_problem, const int p_subsize, int p_limit, const int p_multiplier) {
    Result result = {p_subsize*p_multiplier, p_subsize*p_multiplier};
    int index = 1;
    int count = 1;

    p_limit = (p_limit < p_subsize) ? p_limit : p_subsize;
    while (index < p_limit)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;
            if (count >= (result.index_fin - result.index_init)) {
                result.index_init = index - count + 1 + p_multiplier*p_limit;
                result.index_fin = result.index_init + count - 1;
            }
        }
        else
        {
            count = 1;
        }
        index++;
    }
    return result;
}

Result final_result(const char* p_problem, Result* p_solutions, const int p_num_solutions, int p_subsize) {

    Result solution = *p_solutions;
    
    for(int i = 1; i < p_num_solutions - 1; i++)
    {
        if((*(p_problem + (p_solutions + i - 1)->index_fin)) == (*(p_problem + (p_solutions + i)->index_init)))
        {            
            if(((p_solutions + i - 1)->index_fin) == ((p_solutions + i)->index_init - 1))
            {
                (p_solutions + i)->index_init = (p_solutions + i - 1)->index_init;
            }
        }
        if((*(p_problem + (p_solutions + i + 1)->index_init)) == (*(p_problem + (p_solutions + i)->index_fin)))
        {
            if(((p_solutions + i + 1)->index_init) == ((p_solutions + i)->index_fin + 1))            
            {
                (p_solutions + i)->index_fin = (p_solutions + i + 1)->index_fin;                
            }
        }
        
        if((solution.index_fin - solution.index_init) < ((p_solutions + i)->index_fin - (p_solutions + i)->index_init))
        {
            solution = *(p_solutions + i);
        }
    }
    
    return solution;
}

void DC_recursive(Result* solutions, const char* p_problem, const int p_subsize, const int p_index) {
    int subsize = (p_subsize < 1) ? 1 : p_subsize;
    int length = string_length(p_problem);

    if (length <= subsize)
    {
        *(solutions + p_index) = DC_iterative(p_problem, subsize, length, p_index);
    }
    else
    {
        *(solutions + p_index) = DC_iterative(p_problem, subsize, subsize, p_index);        
        DC_recursive(solutions, (p_problem + subsize), subsize, p_index + 1);
    }
}