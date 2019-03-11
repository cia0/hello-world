#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// default dictionary
#define DICTIONARY "small"

typedef struct node //tries datastructure
    {
        bool is_word;
        struct node* child[27];
    }
    node;

node* newNode(void)
{
    node* temp = malloc(sizeof(node));
    return temp;
}

int main(void)
{
    node* root = malloc(sizeof(node));
    root->child[0] = newNode();
    node* trav = root->child[0];
    
    for (int i = 0; i < 2; i++){
        trav->child[0] = newNode();
        trav = trav->child[0];
    }
    
    free(trav);
    free(root->child[0]->child[0]);
    free(root->child[0]);
    free(root);
}

