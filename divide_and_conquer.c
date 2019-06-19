#include "divide_and_conquer.h"

int string_length(const char* p_string) {
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
}

void base_case(const char* p_problem, const int p_subsize, int p_limit, const int p_offset, Result* p_solution) {
    p_limit = (p_limit < p_subsize) ? p_limit : p_subsize;
    
    for (int index = 0; index < p_limit; index++)
    {
        int count = 1;
        *(p_solution + index) = (Result) {p_offset + index, p_offset + index, count};
        for(int j = index + 1; j < p_limit; j++)
        {
            if (*(p_problem + index) == *(p_problem + j))
            {
                count++;
                (p_solution + index)->repetitions = count;
                (p_solution + index)->index_init = p_offset + index;
                (p_solution + index)->index_fin = p_offset + j;
            }
        }
    }
}

Result final_result(const char* p_problem, const int p_subsize, Result** p_solutions, const int p_num_solutions, const int p_length) {
    Result solution = *(*(p_solutions));
    
    for(int i = 0; i < p_num_solutions; i++)
    {
        for(int j = 0; j < p_subsize; j++)
        {
            int index_solution_i = (*(p_solutions + i) + j)->index_init;
            int index_init = index_solution_i - 1;
            
            while(index_init < p_length && index_init > -1 && (index_solution_i - index_init) < p_subsize)
            {
                if(*(p_problem + index_init) == *(p_problem + index_solution_i))
                {
                    (*(p_solutions + i) + j)->index_init = index_init;
                    (*(p_solutions + i) + j)->repetitions++;
                    
                    while(((*(p_solutions + i) + j)->index_fin - index_init + 1) > p_subsize)
                    {                        
                        if(*(p_problem + index_init) == *(p_problem + (*(p_solutions + i) + j)->index_fin))
                        {
                            (*(p_solutions + i) + j)->repetitions--;                            
                        }
                        (*(p_solutions + i) + j)->index_fin--;
                    }
                }
                index_init--;
            }
            
            if(solution.repetitions < (*(p_solutions + i) + j)->repetitions)
            {
                solution = *(*(p_solutions + i) + j);
            }    
            else if(solution.repetitions == (*(p_solutions + i) + j)->repetitions && solution.index_init > (*(p_solutions + i) + j)->index_init)
            {
                solution = *(*(p_solutions + i) + j);
            }
        }
    }
    
    return solution;
}

void recursive_case(Result** solutions, int* p_num_solutions, const char* p_problem, const int p_subsize, int* p_pappend, const int p_length, int p_index) {
    if (p_length > p_subsize)
    {     
        recursive_case(solutions, p_num_solutions, p_problem, p_subsize, p_pappend, p_subsize, p_index);
        recursive_case(solutions, p_num_solutions, (p_problem + p_subsize), p_subsize, p_pappend, p_length - p_subsize, p_index + p_subsize);
    }
    else
    {
        Result* solution = (Result*) malloc(p_length*sizeof(Result));
        base_case(p_problem, p_subsize, p_length, p_index, solution);
        
        for(int i = 0; i < p_subsize; i++)
        {
            *(*(solutions + *p_pappend) + i) = *(solution + i);
        }
        *p_pappend = *p_pappend + 1;
        free(solution);
    }
}

Result DyV(const char* p_problem, const int p_subsize)
{
    int subsize = (p_subsize < 1) ? 1 : p_subsize;    
    int append = 0;
    int* pappend = &append;
    int length = string_length(p_problem);
    
    int num_solutions = (length % subsize == 0) ? length/subsize : length/subsize + 1;
    Result** solutions = (Result**) malloc(num_solutions*sizeof(Result*));
    for(int i = 0; i < num_solutions; i++)
    {
        *(solutions + i) = (Result*) malloc(subsize*sizeof(Result));
    }
    
    recursive_case(solutions, &num_solutions, p_problem, subsize, pappend, length, 0);
    Result result = final_result(p_problem, subsize, solutions, num_solutions, length);
    
    for(int i = 0; i < num_solutions; i++)
    {
        free(*(solutions + i));
    }
    free(solutions);
    
    return result;
}

Result DyV_iter(const char* p_problem, const int p_subsize)
{
    Result result = {0, 0, 1};
    int length = string_length(p_problem);

    for(int index = 0; index < length - p_subsize; index++)
    {
        int count = 1;
        for(int j = 1; j < p_subsize; j++)
        {
            if (*(p_problem + index) == *(p_problem + index + j))
            {
                count++;
                if (count > result.repetitions)
                {
                    result.index_init = index;
                    result.repetitions = count;
                }
            }
        }
    }
    return result;
}