#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define size_t unsigned long

typedef struct BinaryInteger
{
    bool* number;
    size_t size;
} BinaryInteger;

BinaryInteger* start_binary_integer(const int value, const size_t size)
{
    BinaryInteger* new_int = malloc(sizeof(BinaryInteger));
    new_int->number = malloc(sizeof(bool) * size);
    new_int->size = size;

    for(int i = 0; i < size; i++)
        new_int->number[i] = value & (0b01 << i);
    
    return new_int;
}

int get_decimal_value(const BinaryInteger* const binary_integer)
{
    int sum = 0;

    for(size_t i = 0; i < binary_integer->size; i++)
        sum += binary_integer->number[i] * (0b01 << i);
    
    return sum;
}

void print_binary_integer(const BinaryInteger* const binary_integer)
{
    printf("Decimal: %d\nBinary: ", get_decimal_value(binary_integer));
    for(size_t i = 0; i < binary_integer->size; i++)
    {
        printf("%d", binary_integer->number[binary_integer->size - i - 1]);
    }
    printf("\n");
}


void free_binary_integer(BinaryInteger* binary_integer)
{
    free(binary_integer->number);
    free(binary_integer);
}

BinaryInteger* add_binary_integers(const BinaryInteger* const int_a, const BinaryInteger* const int_b)
{
    BinaryInteger* new_int = malloc(sizeof(BinaryInteger));
    new_int->size = int_a->size + 1;
    new_int->number = malloc(sizeof(bool) * new_int->size);

    bool carry_one = 0;
    int temp_sum;

    for(size_t i = 0; i < int_a->size; i++)
    {
        temp_sum = int_a->number[i] + int_b->number[i] + carry_one;
        new_int->number[i] = temp_sum % 2;
        carry_one = temp_sum / 2;
    }
    new_int->number[int_a->size] = carry_one;

    return new_int;
}


int main()
{
    int num_size;
    printf("Insirt number bit size: ");
    scanf("%d", &num_size);


    int input;
    printf("Insert decimal value for a: ");
    scanf("%d", &input);

    BinaryInteger* int_a = start_binary_integer(input, num_size);
    print_binary_integer(int_a);
    
    printf("Insert decimal value for r: ");
    scanf("%d", &input);

    BinaryInteger*  int_b = start_binary_integer(input, num_size);
    print_binary_integer(int_b);

    printf("\nResult: \n");
    BinaryInteger*  result = add_binary_integers(int_a, int_b);
    print_binary_integer(result);

    free_binary_integer(int_a);
    free_binary_integer(int_b);
    free_binary_integer(result);

}