#include "../../includeser/book.h"

long chartolong(char *str)
{
    long sum = 0;
    int i = 0;

    while(*(str + i) != '\0')
    {
        sum = sum * 10 + (*(str + i) - '0');

	i++;
    }
    return sum;

}
