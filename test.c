#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    char input[100];
    printf("Please enter stuff: ");
    fgets(input, 100, stdin);
    printf("input: %s\n", input);
    char in2[100];
    strcpy(in2, input);

    // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
    char* tk1;
    int c = 0;
    tk1 = strtok(input, " ");
    while (tk1 != NULL) {
        c++;
        printf("%s\n", tk1);
        tk1 = strtok(NULL, " ");
    }

    printf("c: %d\n", c);
    printf("input: %s\n", input);

    c = 0;
    tk1 = strtok(in2, " ");
    while (tk1 != NULL) {
        c++;
        printf("%s\n", tk1);
        tk1 = strtok(NULL, " ");
    }
    printf("c: %d\n", c);
    printf("input: %s\n", in2);

//    char* argument_list[c];
//    char* tk2;
//    tk2 = strtok(input, " ");
//    for (int i = 0; tk2 != NULL; i++) {
//        strcpy(argument_list[i], tk2);
//        printf("%s\n", tk2);
//        tk2 = strtok(NULL, " ");
//    }
//    for (int i = 0; i < c; i++) {
//        printf("%s", argument_list[i]);
//    }
    printf("done\n");
}
