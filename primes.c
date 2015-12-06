#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Print n primes or nth prime. Knuth Version. */

void ex_err(char *msg);
size_t toSizet(char *str);

int main(int argc, char *argv[])
{
    size_t j = 0;
    int i, k, n, table = 0, pad;
    unsigned long long int *p;

    /* Parse the args. */
    if(argc < 2 || argc > 3)
        ex_err("To list n primes: primes n\nTo find nth prime: primes -f n");

    if(2 == argc){
        j = toSizet(argv[1]);
        table = 1;
    } else {
        if (!strcmp(argv[1], "-f")){
            j = toSizet(argv[2]);
            table = 0;
        }    
    }

    if (!j)
	    ex_err("Please pass me an integer argument.");


    /* Generate the list of primes. */
    p = malloc(sizeof(unsigned long long int) * j);
    p[0] = 2;

    for(k = 3, n = 1; n < j; k += 2){
        for (i = 0; k % p[i] ; i++){
            if ((k / p[i]) <= p[i]){
                p[n++] = k;
                break;
            }
        }
    }

    /* Print nth prime or whole table. */
    if (!table){
	    printf("nth prime is: %lld\n", p[n-1]);
    }else {
            /* Calculate amount of padding. */
	    pad = ceil(log10((double)p[n-1]));

	    /* Print the primes */
	    for (i=0; i < j; i++){
		    printf("%0*lld ", pad, p[i]);
		    if(!((i+1)%10))
			    printf("\n");
	    }
            if(i%10){
                printf("\n");
            }
    }
    free(p);
    return 0;
}

/* Check input is a valid integer and return as a size_t value. */
size_t toSizet(char *str)
{
    int i;
    for (i = 0; i != '\0'; i++){
        if(!isdigit(str[i]))
            return 0;
    }
    return (size_t)atoi(str);
}

    
void ex_err(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

