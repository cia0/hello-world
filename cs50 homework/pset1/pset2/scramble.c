#include <stdio.h>
#include <cs50.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE
#include <crypt.h>

int main(int argc, string argv[])
{
    if (argc == 3)
    {
        string scramb = crypt(argv[1], argv[2]);
        printf("%s\n", scramb);
        return 0;
    }
    printf("try again\n");
    return 1;
}