#include "divide_and_conquer.h"

int string_length(const char* p_string) {
    int size = 0;

    while (*(p_string + size) != '\0')
    {
        ++size;
    }

    return size;
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

Result base_case(const char* p_problem, const int p_subsize, int p_limit, const int p_offset) {
    Result result = {p_offset, p_offset, 1};

    p_limit = (p_limit < p_subsize) ? p_limit : p_subsize;
    for (int index = 0; index < p_subsize; index++)
    {
        int count = 1;
        for(int j = 1; j < p_limit; j++)
        {
            if (*(p_problem + index) == *(p_problem + index + j))
            {
                count++;
                if (count >= result.repetitions) {
                    result.repetitions = count;
                    result.index_init = p_offset + index;
                    result.index_fin = p_offset + index + j;
                }
            }
        }
    }
    return result;
}

Result final_result(const char* p_problem, const int p_subsize, Result* p_solutions, const int p_num_solutions, int length) {
    for(int i = 0; i < p_num_solutions; i++)
    {
        int index_solution_i = (p_solutions + i)->index_init;
        int index_init = index_solution_i - 1;
        
        while(index_solution_i < length && index_init > -1 && (index_solution_i - index_init) < p_subsize)
        {
            if(*(p_problem + index_init) == *(p_problem + index_solution_i))
            {
                (p_solutions + i)->index_init =  index_init;
                (p_solutions + i)->repetitions++;
                
                if(((p_solutions + i)->index_fin - index_init + 1) > p_subsize)
                {
                    (p_solutions + i)->index_fin--;
                    (p_solutions + i)->repetitions--;
                }
            }
            index_init--;
        }
    }
    
    Result solution = *p_solutions;
    
    for(int i = 1; i < p_num_solutions; i++)
    {
        if(solution.repetitions < (p_solutions + i)->repetitions)
        {
            solution = *(p_solutions + i);
        }
    }
    
    return solution;
}

void recursive_case(Result* solutions, int* p_num_solutions, const char* p_problem, const int p_subsize, int* p_pappend, const int p_index_fin, int p_index) {
    if ((p_index_fin + 1) > p_subsize)
    {     
        *p_num_solutions = *p_num_solutions + 1;
        solutions = (Result*) realloc(solutions, (*p_num_solutions)*sizeof(Result));
        
        recursive_case(solutions, p_num_solutions, p_problem, p_subsize, p_pappend, p_index_fin/2 - 1, p_index);
        recursive_case(solutions, p_num_solutions, (p_problem + p_index_fin/2), p_subsize, p_pappend, p_index_fin/2, p_index + p_index_fin/2);
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
    Result* solutions = (Result*) malloc(sizeof(Result));
    int num_solutions = 1;
    int append = 0;
    int* pappend = &append;
    
    recursive_case(solutions, &num_solutions, p_problem, subsize, pappend, length, 0);
    Result result = final_result(p_problem, subsize, solutions, num_solutions, length);
    free(solutions);
    
    return result;
}

Result DyV_iter(const char* p_problem, const int p_subsize)
{
    Result result = {0, 0};
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