#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string(); //gets the user's name as input
    if (s[0] != ' ') //prints the first char if it is not a space
    {
        printf("%c", toupper(s[0]) );
    }
    for (int i = 1, n = strlen(s); i < n; i++) //prints a character in the string if it is not a space and there is a space before that char
    {
        if (s[i-1] == ' ' && s[i] != ' ')
        {
            printf("%c", toupper(s[i]) ); //makes char uppercase
        }
        
    }
    printf("\n");
}