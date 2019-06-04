#include "divide_and_conquer.h"

int string_length(const char* p_string) {
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

Result DC_iterative(const char* p_problem, const int p_limit) {
    Result result = {0, 0};
    int index = 1;
    int count = 1;

    while (index < p_limit)
    {
        if (*(p_problem + index - 1) == *(p_problem + index))
        {
            count++;
            if (count >= (result.index_fin - result.index_init)) {
                result.index_init = index - count + 1;
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

Result final_result(const char* p_problem, const Result* p_solutions, const int p_num_solutions, int p_offset) {

    Result solution = *p_solutions;
    
    for(int i = 1; i < p_num_solutions - 1; i++)
    {
        char last_character_previous_solution = *(p_problem + (p_solutions + i - 1)->index_fin + i*p_offset - 1);
        char first_character_next_solution = *(p_problem + (p_solutions + i + 1)->index_fin + i*p_offset + 1);
        
        if(last_character_previous_solution == *(p_problem + (p_solutions + i)->index_fin + i*p_offset))
        {
            solution.index_init = (p_solutions + i - 1)->index_fin + i*p_offset - 1;
        }
        if((solution.index_fin - solution.index_init) < ((p_solutions + i)->index_fin - (p_solutions + i)->index_init))
        {
            solution = *(p_solutions + i);
        }
        if(first_character_next_solution == *(p_problem + (p_solutions + i)->index_fin + i*p_offset))
        {
            solution.index_init = (p_solutions + i + 1)->index_fin + i*p_offset + 1;
        }
    }
    
    return solution;
}

Result DC_recursive(const char* p_problem, const int p_subsize) {
    int subsize = (p_subsize < 1) ? 1 : p_subsize;
    int length = string_length(p_problem);

    if (length <= subsize)
    {
        return DC_iterative(p_problem, length);
    }
    else
    {
        int num_solutions = (length % p_subsize == 0) ? length / p_subsize : length / p_subsize + 1;
        Result* solutions = (Result*) malloc(num_solutions*sizeof(Result));
        
        for(int i = 0; i < num_solutions; i++)
        {
            *(solutions + i) = DC_iterative((p_problem + i*subsize), i*subsize);
        }
        
        return final_result(p_problem, solutions, num_solutions, subsize);
    }
}