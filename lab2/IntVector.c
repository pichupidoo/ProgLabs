#include <stdio.h>
#include <stdlib.h>
#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity)
{
    IntVector *vector = malloc(sizeof(IntVector));

    if (vector == NULL)
        return NULL;

    vector->item = malloc(initial_capacity * sizeof(int));

    if (vector->item == NULL)
    {
        free(vector);
        return NULL;
    }

    vector->size = 0;
    vector->capacity = initial_capacity;

    return vector;
}

IntVector *int_vector_copy(const IntVector *v)
{
    int i;
    IntVector *vector = malloc(sizeof(IntVector));

    if (vector == NULL)
    {
        return NULL;
    }

    vector->item = malloc(v->capacity * sizeof(int));

    if (vector->item == NULL)
    {
        free(vector);
        return NULL;
    }

    vector->size = v->size;
    vector->capacity = v->capacity;

    for (i = 0; i < vector->size; i++)
    {
        vector->item[i] = v->item[i];
    }

    return vector;
}

void int_vector_free(IntVector *v)
{
    if(v != NULL) {
        free(v->item);
        free(v);
    }
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    return v->item[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
    v->item[index] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item) 
{
    if (v->size < v->capacity)
    {
        v->item[v->size] = item;
        v->size++;
        return 0;
    }
    else
    {   
        if(v->capacity == 0) {
            v->capacity = 2;
            int *temp = realloc(v->item, v->capacity * sizeof(int));
            if (temp == NULL) {
                return -1;
            }
            v->item = temp;
            v->item[v->size] = item;
            v->size++;
        }
        else {
        v->capacity = v->capacity * 2; 
        int *temp = realloc(v->item, v->capacity * sizeof(int));
        if (temp == NULL)
        {
            return -1;
        }
        v->item = temp;
        v->item[v->size] = item;
        v->size++;
        }
    }
    return 0;
}

void int_vector_pop_back(IntVector *v)
{
    if(v->size > 0){
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector *v)
{
    if(v->size == 0) {
        free(v->item);
        v->item = NULL;
        v->capacity = v->size;
        return 0;
    }
    int *temp = realloc(v->item, v->size*sizeof(int));
    
    if(temp == NULL) {
        return -1;
    }
    v->item = temp;
    v->capacity = v->size;

    return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
    if(v->size < new_size) {
        int *temp = realloc(v->item, new_size * sizeof(int));
        if(temp == NULL) {
            return -1;
        }
        v->item = temp;
        
        int i;
        for(i = v->size; i < new_size; i++) {  
            v->item[i] = 0;
        }
        v->size = new_size;
    }
    else {
        v->size = new_size;
        int_vector_shrink_to_fit(v);
    }
    if(new_size > v->capacity) {
        int_vector_reserve(v, new_size);
    }
    return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
    if(v->capacity < new_capacity) {
        int *temp = realloc(v->item, new_capacity * sizeof(int));
        if(temp == NULL) {
            return -1;
        }
        v->item = temp;
        v->capacity = new_capacity;
        return 0;
    }
    return -1;
}