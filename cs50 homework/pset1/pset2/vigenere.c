#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool is_alpha(string s);

int main(int argc, string argv[])
{
    string k = argv[1]; //puts the user's keyword into a string variable called k
    
    if (argc == 2 && is_alpha(k))
    {
       
        printf("plaintext: ");
        string plaintxt = get_string();
        
        /*while (is_alphaWspace(plaintxt) == false) //makes sure the user only enters letters
        {
            printf("PLEASE ONLY ENTER ALPHABETIC CHARATERS: ");
            plaintxt = get_string();
        }*/
        
        
        char ciphertxt[1000];// makes a muteable array of characters that we will return
        
        for (int i = 0, skipcount = 0, n = strlen(plaintxt); i < n; i++)
        {
            
            if (isalpha(plaintxt[i]) == false)
            {
                ciphertxt[i] = plaintxt[i];
                skipcount += 1; //makes sure no char from the key is skipped
            }
            
            else if (plaintxt[i] < 90)
            {
               ciphertxt[i] = ((plaintxt[i] - 65 + (toupper(k[ (i - skipcount) % strlen(k)]) - 65) ) % 26) + 65;
            }
            
            else
            {
                ciphertxt[i] = ((plaintxt[i] - 97 + (tolower(k[ (i - skipcount) % strlen(k)]) - 97)) % 26) + 97;
            }
            
            
            ciphertxt[i+1] = '\0'; //makes sure there is an end to the string in the array ciphertxt
        }
        
        
        printf("ciphertext: %s\n", ciphertxt);
        
        return 0;
    }
    printf("Usage: ./vigenere key\n");
    return 1;
    
}

bool is_alpha(string s) //returns true if input is alphabetic, else returns false
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]) == false)
        {
            return false;
        }
    }
    return true;
}
