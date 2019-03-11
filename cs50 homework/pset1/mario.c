#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Height: ");
    
    int height = get_int();
    
    while (height < 0 || height > 23)
    {
        printf("Height: ");
        height = get_int();
    }
    
    for (int i = 1; i < height+1; i++)
    {
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
     
}