#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int dataSize;
    printf("Please enter the maximum size of the username field: ");
    scanf("%d", &dataSize);
    printf ("Please input username: ");
    char *data1;
    data1 = malloc (dataSize);
    scanf("%s", data1);
    printf ("You entered: [%s]\n", data1);
    free (data1);
    return 0;
}