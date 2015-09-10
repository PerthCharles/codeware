#include <stdio.h>

#define STR1(n)         printf("STR1 = %s\n", str_##n)
#define STR2(n, m)      printf("STR2 = %s\n", str_##n##m)
#define STR3(n, op, m)  printf("STR3 = %s\n", str_##n##op##m)
#define STR4(n, m)      printf("STR4 = %s\n", str_##n_##m)

int main()
{
    char *str_a     = "str_a";
    char *str_ab    = "str_ab";
    char *str_a_b   = "str_a_b";
    char *str_n_b   = "str_n_b";
    STR1(a);
    STR2(a, b);
    STR3(a, _, b);
    /* since there is a irreplaceable char ('_') after '##n',
     * '##n' can not be replaced.
     * As a result, STR4(a, b) will result in str_n_b
     * */
    STR4(a, b); 
}
