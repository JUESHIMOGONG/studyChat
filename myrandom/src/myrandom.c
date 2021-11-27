#include "../../includeser/book.h"

long myrandom()
{
    srandom(time(0));
    return random()%1000000000 + 1000000000;
}
