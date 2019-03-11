/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int pie;

#define DICTIONARY "large"

//prototype
bool unload(void);
typedef struct node //tries datastructure
    {
        bool is_word;
        struct node* child[27];
    }
    node;

node* newNode(void) //make a new node with initialized values of false and NULL
{
    node* temp = calloc(1, sizeof(node));
    //temp->is_word = false;
    /*for (int i = 0; i < 27; i++)
    {
        temp->child[i] = NULL;
    }*/
    return temp;
}
node* root; //root node

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    node* trav; //traversal node pointer
    
    int branch = tolower(word[0]) - 97; //turn 'a' into 0, 'b' into 1, etc..
    if (branch < 0) //that means that it must be the apostrophe
    {
        branch = 26; //assign apostrophe to the end of the array
    }
    
    trav = root->child[branch];
    if (trav == NULL)
    {
        return false;
    }
    
    for(int i = 1; i < strlen(word); i++)//iterate through every character in the given word
    {
        branch = tolower(word[i]) - 97; //turn 'a' into 0, 'b' into 1, etc..
        if (branch < 0) //that means that it must be the apostrophe
        {
            branch = 26; //assign apostrophe to the end of the array
        }
    
        trav = trav->child[branch];
        
        if (trav == NULL)
        {
            return false;
        }
    }
    
    if (trav->is_word){
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    root = newNode(); //root array node
    node* trav = NULL; //traversing pointer
    
    if (root == NULL)
    {
        free(root);
        return false;
    }
    
    FILE *fpd = fopen(dictionary, "r");//opens the dictionary
    if (fpd == NULL)
    {
        printf("why\n");
        fclose(fpd);
        return false;
    }
    
    bool beggining = true;
    
    for (int c; (c = fgetc(fpd)) != EOF;)
    {
        int vine = c - 97; //turn 'a' into 0, 'b' into 1, etc..
        if (vine < 0) //that means that it must be the apostrophe
        {
            vine = 26; //assign apostrophe to the end of the array
        }
        
        if(beggining) //beggining of a word
        {
            //printf("\n");
            if (root->child[vine] == NULL)
            {
    
                root->child[vine] = newNode();
                
                if (root->child[vine] == NULL)
                {
                    unload();
                    return false;
                }
            }
            trav = root->child[vine];
            //printf("%c", c);
        }
        
        else if(c == '\n') //end of line
        {
            beggining = true;
            trav->is_word = true;
            continue;
        }
        
        else //in the middle of a word
        {
            if (trav->child[vine] == NULL)
            {
                trav->child[vine] = newNode(); //creates a new node if at dead end
            }
            
            trav = trav->child[vine]; //continues down the vine
            
            if (trav == NULL)
            {
                unload();
                return false;
            }
            //printf("%c", c);
        }
        
        beggining = false;
        
    }
    fclose(fpd);
    return true;
}

void unloadhelp(node* current)
{
    if (current == NULL)
    {
        return;
    }
    
    else{
        for (int i = 0; i<27; i++)
        {
            if (current->child[i] != NULL){
                unloadhelp(current->child[i]);
            }
            
        }
        free(current);
    }
}

bool unload(void) //free up memory
{
    node* cursor = root;
    for (int i = 0; i<27; i++)
    {
        unloadhelp(cursor->child[i]);
    }
    free(cursor);
    return true;
}

int main(void)
{
    char* dictionary = DICTIONARY;
    load(dictionary);
    if(check("ENd"))
    {
        printf("yeet\n");   
    }
    unload();
    return 0;
}