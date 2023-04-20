//Anna Del Negro 
//Lab assignment #10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    int flag;
    struct Trie *children[26];
}Trie;

//function prototypes
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure

    //initialize trie = use calloc
    Trie *trie = calloc(1, sizeof(Trie));
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    
    //inserting chars to trie
    for(int i = 0; i<5; i++){
        insert(&trie, pWords[i]);
    }

    //printing number of ocurrences 
    for (int i=0;i<5;i++){
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    //deallocating trie / freeing memory
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0; 
}

//insert function
void insert(struct Trie **ppTrie, char *word){
    if(*ppTrie == NULL){
        return;
    }
    Trie *temp = *ppTrie;
    int lenght = strlen(word);

    for(int i = 0; i < lenght; i++){
        int index = word[i] - 'a';
        if(temp->children[index] == NULL){
            temp->children[index] = calloc(1, sizeof(Trie));
        }
        temp = temp->children[index];
    }
    temp->flag++;
}

//number of occurances function
int numberOfOccurances(struct Trie *pTrie, char *word){
    if(pTrie == NULL){
        return 0;
    }
    Trie *temp = pTrie;
    int lenght = strlen(word);
    int i = 0;

    for(i; i < lenght; i++){
        int index = word[i] - 'a';
        if(temp->children[index] != NULL){
            temp = temp->children[index];
        }
        else{
            break;
        }
    }
    if(i == lenght){
        return temp->flag;
    }
    else{
        return 0;
    }
}

//deallocating trie function
struct Trie *deallocateTrie(struct Trie *pTrie){
    if(pTrie == NULL){
        return pTrie;
    }

    int i = 0;
    for(i; i < 26; i++){
        if(pTrie->children[i] != NULL){
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
}