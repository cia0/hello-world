#include <stdio.h>
#include <cs50.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE
#include <crypt.h>

int main(int argc, string argv[]) //is there a way to avoid using the four for loops in a row and use one big loop instead?
{

    
    if (argc == 2)
    {
        string alphastring = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //all characters possibly in the password
        string hash = argv[1];
        char pass[5]; //array for guessing passwords
        char salt[3]; //stores the first to chars from the hash
        salt[0] = hash[0];
        salt[1] = hash[1];
        salt[2] = '\0';
        //printf("%s\n", salt);
        //printf("%s\n", hash);
        pass[1] = '\0';
        for (int i = 0, n = strlen(alphastring); i < n; i++) //checks all passwords of 1 char length
        {
            pass[0] = alphastring[i];
            //printf("%s\n", pass);
            //printf("%s\n", crypt(pass, salt) );
            if (strcmp(crypt(pass, salt), hash) == 0) //will end program and print cracked password if hash is cracked
            {
                printf("%s\n", pass);
                return 0;
            }
        }
        
        pass[2] = '\0';
        for (int i = 0, n = strlen(alphastring); i < n; i++) //checks all passwords of 2 char length
        {
            pass[0] = alphastring[i];
            
            for (int j = 0; j < n; j++)
            {
                pass[1] = alphastring[j];
                //printf("%s\n", pass);
                if (strcmp(crypt(pass, salt), hash) == 0) //will end program and print cracked password if hash is cracked
                {
                    printf("%s\n", pass);
                    return 0;
                }
            }
            
        }
        
        pass[3] = '\0';
        for (int i = 0, n = strlen(alphastring); i < n; i++) //checks all passwords of 3 char length
        {
            pass[0] = alphastring[i];
            
            for (int j = 0; j < n; j++)
            {
                pass[1] = alphastring[j];
                
                for (int k = 0; k < n; k++)
                {
                    pass[2] = alphastring[k];
                    //printf("%s\n", pass);
                    if (strcmp(crypt(pass, salt), hash) == 0) //will end program and print cracked password if hash is cracked
                    {
                        printf("%s\n", pass);
                        return 0;
                    }
                }
            }
            
        }
        
        pass[4] = '\0';
        for (int i = 0, n = strlen(alphastring); i < n; i++) //checks all passwords of 3 char length
        {
            pass[0] = alphastring[i];
            
            for (int j = 0; j < n; j++)
            {
                pass[1] = alphastring[j];
                
                for (int k = 0; k < n; k++)
                {
                    pass[2] = alphastring[k];
                    
                    for (int l = 0; l < n; l++)
                    {
                        pass[3] = alphastring[l];
                        //printf("%s\n", pass);
                        if (strcmp(crypt(pass, salt), hash) == 0) //will end program and print cracked password if hash is cracked
                        {
                            printf("%s\n", pass);
                            return 0;
                        }
                    }
                }
            }
            
        }
        
        printf("y'all are gonna need a different program to crack this tough nut\n");
        return 0;
    }
    
    printf("Usage: ./crack hash\n");
    return 1;
}