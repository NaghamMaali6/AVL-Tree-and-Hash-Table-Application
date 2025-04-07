/*
  Name: Nagham Maali
  ID: 1212312
  Sec.: 2
*/

//libraries:
/*1*/#include <stdio.h>
/*2*/#include <stdlib.h>
/*3*/#include <string.h>

//constants:
/*(:)*/#define Max_NumberOf_words 1000
/*(:)*/#define Max_Word_Length 50
/*(:)*/#define HashTable_Size 13

struct word  //structure to store words and their frequency
{
    char W[Max_Word_Length] ;
    int frequency ;
};

struct AVL  //AVL Tree Node
{
    struct word Data ;
    struct AVL *Left ;
    struct AVL *Right ;
    int Height ;  //Balance
};

struct Node  //Linked List Node
{
    struct word Data ;
    struct Node *Next ;
};

struct Hash  //Hash Table structure
{
    struct Node *Hash_Table[HashTable_Size] ;
};

//function Definition:
/*1*/void displayMainMenu() ;
/*2*/void ToUpperCase(char *s) ;
/*3*/int IsExist(struct word words[] , int words_counter , char *t) ;
/*4*/struct AVL *Insert_toTree(struct AVL *Tree , struct word words) ;
/*5*/struct AVL *CreateTree(struct word words) ;
/*6*/int GetH(struct AVL *Tree) ;
/*7*/int Max(int H1 , int H2) ;
/*8*/int GetB(struct AVL *Tree) ;
/*9*/struct AVL *Right_R(struct AVL *Tree) ;
/*10*/struct AVL *Left_R(struct AVL *Tree) ;
/*11*/struct AVL *Add_Word(struct AVL *Tree , struct word newW) ;
/*14*/struct AVL *Delete_Word(struct AVL *Tree , char *RemW) ;
/*15*/struct AVL *MinN(struct AVL *Tree) ;
/*16*/void PrintT(struct AVL *Tree) ;
/*17*/struct Hash *createTable() ;
/*18*/void Insert_toTable(struct Hash *HT , struct word words) ;
/*19*/int Hashing(char *w) ;
///*20*/void printHT(struct Hash *HT) ;  //function to test only
/*21*/void Add_toTable(struct Hash *HT , struct word newW) ;
/*22*/void Delete_fromTable(struct Hash *HT , char *RemW) ;
/*23*/void Search_and_changeF(struct Hash *HT , char *WtochF) ;
/*24*/int find_unique(struct Hash *HT) ;
/*25*/struct word highestF(struct Hash *HT) ;

int main()
{
    printf("Hi!\n") ;

    int x ;  //user choice
    int condition = 1 ;

    FILE *input_file ;
    char Line[500] ;
    char *token ;
    int i ;
    struct word words[Max_NumberOf_words] ;
    int words_counter = 0 ;
    int k ;

    struct AVL *Tree ;
    Tree = NULL ;

    char newWord[Max_Word_Length] ;  //word to be added
    struct word newW ;

    char RemW[Max_Word_Length] ;  //word to be removed

    struct Hash *HT ;
    HT = NULL ;

    char WtochF[Max_Word_Length] ;  //word to find and update frequency

    int unique_counter ;  // total number of unique words
    struct word W_withHighrstF ;  //the word with the highest frequency

    while(condition == 1)
    {
        displayMainMenu() ;
        scanf("%d" , &x) ;

        if(x == 1)
        {
            input_file = fopen("input.txt" , "r") ;  //open input file

            if(input_file == NULL)  //check if the file exists and can be opened
            {
                printf("No file with such a name!\n") ;
                return NULL ;
            }

            printf("loading process started\n") ;
            printf("\n") ;

            while(fgets(Line , sizeof(Line) , input_file) != NULL)  //read each line from input file
            {
                /*printf("%s\n" , Line) ;  //to check the reading process*/
                token = strtok(Line , " \n") ;  //split the line into tokens using space and newline as delimiter
                if(token == NULL)
                {
                    printf("invalid input format!\n") ;
                    fclose(input_file) ;
                    return ;
                }

                while(token != NULL)
                {
                    ToUpperCase(token) ;  //convert to uppercase(capital letters)
                    i = IsExist(words , words_counter , token) ;  //check if the word exists in the the array
                    if(i == 0)
                    {
                        words[i].frequency++ ;  //increment the word's frequency if it exists
                    }
                    else  //if the word isn't already in the array
                    {
                        strcpy(words[words_counter].W , token) ;  //copy token to the array
                        words[words_counter].frequency = 1 ;  //set frequency to 1
                        words_counter++ ;  //increment words counter
                    }
                    token = strtok(NULL , " \n") ;
                }
            }
            fclose(input_file) ;  //close input file

            /*//print the array and number of words(without repetition) to check the loading process:
            for(k = 0 ; k < words_counter ; k++)
            {
                printf("%s(%d)\n" , words[k].W , words[k].frequency) ;
            }

            printf("number of words(without repetition) = %d\n" , words_counter) ;
            */

            printf("done loading.\n") ;
        }
        else if(x == 2)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                for(k = 0 ; k < words_counter ; k++)
                {
                    Tree = Insert_toTree(Tree, words[k]) ;
                }
                printf("AVL Tree is created and words are inserted.\n") ;
            }

            printf("\n") ;
        }
        else if(x == 3)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                printf("Enter the new word u wanna add.\n") ;
                scanf("%s", newWord) ;

                ToUpperCase(newWord) ;  //convert to uppercase(capital letters)

                strcpy(newW.W, newWord) ;
                newW.frequency = 1 ;  //set frequency of the new word to 1

                Tree = Add_Word(Tree, newW) ;
            }

            printf("\n") ;
        }
        else if(x == 4)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                printf("which word u wanna delete?\n") ;
                scanf("%s", RemW) ;

                ToUpperCase(RemW) ;  //convert to uppercase(capital letters)

                Tree = Delete_Word(Tree, RemW) ;
            }

            printf("\n") ;
        }
        else if(x == 5)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                printf("the AVL tree in-order traversal:\n") ;
                PrintT(Tree) ;
            }

            printf("\n") ;
        }
        else if(x == 6)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                //the collision handling is managed using separate chaining method with linked list.
                HT = createTable() ;
                for(k = 0 ; k < words_counter ; k++)
                {
                    Insert_toTable(HT, words[k]) ;
                }

                printf("Hash Table is created and words are inserted.\n") ;

                /*printHT(HT) ; to check the hash table creating and inserting the words*/
            }

            printf("\n") ;
        }
        else if(x == 7)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                printf("Enter the new word u wanna add.\n") ;
                scanf("%s", newWord) ;

                ToUpperCase(newWord) ;  //convert to uppercase(capital letters)

                strcpy(newW.W, newWord) ;
                newW.frequency = 1 ;  //set frequency of the new word to 1

                Add_toTable(HT, newW) ;

                /*printHT(HT) ;  //to check the adding process*/
            }

            printf("\n") ;
        }
        else if(x == 8)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                printf("which word u wanna delete?\n") ;
                scanf("%s", RemW) ;

                ToUpperCase(RemW) ;  //convert to uppercase(capital letters)

                Delete_fromTable(HT , RemW) ;

                /*printHT(HT) ;  //to check the removing process*/
            }

            printf("\n") ;
        }
        else if(x == 9)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                printf("which word u wanna change it's frequency?\n") ;
                scanf("%s" , WtochF) ;

                ToUpperCase(WtochF) ;  //convert to uppercase(capital letters)

                Search_and_changeF(HT , WtochF) ;

                /*printHT(HT) ;  //to check the frequency update process*/
            }

            printf("\n") ;
        }
        else if(x == 10)
        {
            if(words_counter == 0)
            {
                printf("No words!the input file must be read first.\n") ;
            }
            else
            {
                unique_counter = find_unique(HT) ;
                printf("total number of unique words = %d\n" , unique_counter) ;

                W_withHighrstF = highestF(HT) ;
                printf("the most frequent word(the word with the highest frequency) is '%s'with frequency = '%d'.\n" , W_withHighrstF.W , W_withHighrstF.frequency) ;
            }

            printf("\n") ;
        }
        else if(x == 11)
        {
            printf("Bye!\n") ;
            break ;
        }
        else
        {
            printf("invalid option!!!\n") ;
            printf("try again :)\n") ;
        }
    }

    return 0;
}

void displayMainMenu()
{
    printf("please select an option(1-11):\n") ;
    printf("1. Load data from the file.\n") ;
    printf("2. Create the AVL tree.\n") ;
    printf("3. Insert a word to the AVL tree.\n") ;
    printf("4. Delete a word from the AVL tree.\n") ;
    printf("5. Print the words as sorted in the AVL tree.\n") ;
    printf("6. Create the Hash Table.\n") ;
    printf("7. Insert a word to the Hash table.\n") ;
    printf("8. Delete a word from the hash table.\n") ;
    printf("9. Search for a word in the hash table and print its frequency and change it.\n") ;
    printf("10. Print words statistics.\n") ;
    printf("11. Exit the application.\n") ;
}

void ToUpperCase(char *s)
{
    int i ;
    for(i = 0 ; s[i] ; i++)
    {
        s[i] = toupper(s[i]) ;  //convert each character in the word to uppercase
    }
}

int IsExist(struct word words[] , int words_counter , char *t)
{
    int j ;
    for(j = 0 ; j < words_counter ; j++)
    {
        if(strcmp(words[j].W , t) == 0)  //if the word already exists
        {
            return j ;  //return the index
        }
    }
    return -1 ;  //return -1 if the word doesn't exist
}

struct AVL *Insert_toTree(struct AVL *Tree , struct word words)
{
    int Balance ;

    if(Tree == NULL)  //if the tree isn't created
    {
        Tree = CreateTree(words) ;  //create a new tree
    }

    if(strcmp(words.W , Tree -> Data.W) < 0)  //if word is smaller than the root, go left
    {
        Tree -> Left = Insert_toTree(Tree -> Left , words) ;  //recursively insert into the left subtree
    }
    else if(strcmp(words.W , Tree -> Data.W) > 0)  //if word is greater than the root, go right
    {
        Tree -> Right = Insert_toTree(Tree -> Right , words) ;  //recursively insert into the right subtree
    }
    else  //if the word already exists
    {
        return Tree ;  //return the tree unchanged
    }

    Tree -> Height = 1 + Max(GetH(Tree -> Left) , GetH(Tree -> Right)) ;  //update the height of the current node
    Balance = GetB(Tree) ;  //get the balance of the current node

    //Left-Left Rotation:
    if(Balance > 1 && strcmp(words.W , Tree -> Left -> Data.W) < 0)
    {
        return Right_R(Tree) ;  //perform right rotation
    }

    //Right-Right Rotation:
    if(Balance < -1 && strcmp(words.W , Tree -> Right -> Data.W) > 0)
    {
        return Left_R(Tree) ;  //perform left rotation
    }

    //Left-Right Rotation:
    if(Balance > 1 && strcmp(words.W , Tree -> Left -> Data.W) > 0)
    {
        Tree -> Left = Left_R(Tree -> Left) ;  //perform left rotation on the left subtree
        return Right_R(Tree) ;  //perform right rotation on the current node
    }

    //Right-Left Rotation:
    if(Balance < -1 && strcmp(words.W , Tree -> Right -> Data.W) < 0)
    {
        Tree -> Right = Right_R(Tree -> Right) ;  //perform right rotation on right subtree
        return Left_R(Tree) ;  //perform left rotation on current node
    }

    return Tree ;  //return the updated tree
}

struct AVL *CreateTree(struct word words)
{
    struct AVL *Node ;

    Node = (struct AVL *)malloc(sizeof(struct AVL)) ;  //allocate memory for AVL node

    Node -> Data = words ;  //initialize node data with the given word
    Node -> Left = NULL ;  //initialize left child as NULL
    Node -> Right = NULL ;  //initialize right child as NULL
    Node -> Height = 1 ;  //initialize height as 1

    return Node ;  //return the created node
}

int GetH(struct AVL *Tree)
{
    if(Tree == NULL)
    {
        return -1 ;  //return -1 if the tree is empty
    }
    else
    {
        return Tree -> Height ;  //return the height of the tree
    }
}

int Max(int H1 , int H2)  //function to return the greater height
{
    if(H1 > H2)
    {
        return H1 ;
    }
    else
    {
        return H2 ;
    }
}

int GetB(struct AVL *Tree)
{
    if(Tree == NULL)
    {
        return 0 ;  //return 0 if the tree is empty
    }
    else
    {
        return (GetH(Tree -> Left) - GetH(Tree -> Right)) ;  //calculate and return balance
    }
}

struct AVL *Right_R(struct AVL *Tree)
{
    struct AVL *T1 ;
    struct AVL *T2 ;

    T1 = Tree -> Left ;  //T1 is the left child
    T2 = T1 -> Right ;  //T2 is the right child of T1

    T1 -> Right = Tree ;  //rotate right
    Tree -> Left = T2 ;  //update left child of the rotated node

    Tree -> Height = Max(GetH(Tree -> Left) , GetH(Tree -> Right)) + 1 ;  //update height of the rotated node
    T1 -> Height = Max(GetH(T1 -> Left) , GetH(T1 -> Right)) + 1 ;  //update hight of the new root

    return T1 ;  //return the new root after rotation
}

struct AVL *Left_R(struct AVL *Tree)
{
    struct AVL *T1 ;
    struct AVL *T2 ;

    T1 = Tree -> Right ;  //T1 is the right child
    T2 = T1 -> Left ;  //T2 is the left child of T1

    T1 -> Left = Tree ;  //rotate left
    Tree -> Right = T2 ;  //update right child of the rotated node

    Tree -> Height = Max(GetH(Tree -> Left) , GetH(Tree -> Right)) + 1 ;  //update height of the rotated node
    T1 -> Height = Max(GetH(T1 -> Left) , GetH(T1 -> Right)) + 1 ;  //update height of the new root

    return T1 ;  //return the new root after rotation
}

struct AVL *Add_Word(struct AVL *Tree , struct word newW)
{
    int Balance ;

    if(Tree == NULL)
    {
        return CreateTree(newW) ;
    }

    int c ;
    c = strcmp(newW.W , Tree -> Data.W) ;  //compare the word with the current node's word

    if(c < 0)  //if the new word is less than the current node
    {
        Tree -> Left = Add_Word(Tree -> Left , newW) ;  //recursively add the word to the left subtree
    }
    else if(c > 0)  //if the new word is greater than the current node
    {
        Tree -> Right = Add_Word(Tree -> Right , newW) ;  //recursively add the word to the right
    }
    else  //if the word already exists
    {
        Tree -> Data.frequency++ ;  //increment the frequency of the word

        printf("the word '%s' is already in the AVL tree for '%d' times.\n" , newW.W , Tree -> Data.frequency) ;
        return Tree ;
    }

    Tree -> Height = 1 + Max(GetH(Tree -> Left) , GetH(Tree -> Right)) ;  //update the height of the node

    Balance = GetB(Tree) ;  //get the balance

    //Left-Left Rotation:
    if(Balance > 1 && strcmp(newW.W , Tree -> Left -> Data.W) < 0)
    {
        return Right_R(Tree) ;
    }

    //Right-Right Rotation:
    if(Balance < -1 && strcmp(newW.W , Tree -> Right -> Data.W) > 0)
    {
        return Left_R(Tree) ;
    }

    //Left-Right Rotation:
    if(Balance > 1 && strcmp(newW.W , Tree -> Left -> Data.W) > 0)
    {
        Tree -> Left = Left_R(Tree -> Left) ;  //perform left rotation on the left subtree
        return Right_R(Tree) ;  //perform right rotation on the current node
    }

    //Right-Left Rotation:
    if(Balance < -1 && strcmp(newW.W , Tree -> Right -> Data.W) < 0)
    {
        Tree -> Right = Right_R(Tree -> Right) ;  //perform right rotation on the right subtree
        return Left_R(Tree) ;  //perform left rotation on the current node
    }

    return Tree ;  //return the updated tree
}

struct AVL *Delete_Word(struct AVL *Tree , char *RemW)
{
    if(Tree == NULL)
    {
        printf("No words in the Tree!\n") ;
        return NULL ;
    }

    int c ;
    struct AVL *ptr ;
    struct AVL *temp ;
    int Balance ;

    c = strcmp(RemW , Tree -> Data.W) ;  //compare the word-to-be-removed with the current node's word

    if(c < 0)  //if it's less
    {
        Tree -> Left = Delete_Word(Tree -> Left , RemW) ;  //go left and recursively delete the word from the left subtree
    }
    else if(c > 0)  //if it's greater
    {
        Tree -> Right = Delete_Word(Tree -> Right , RemW) ;  //go right and recursively delete the word from the right subtree
    }
    else
    {
        if((Tree -> Left == NULL) || (Tree -> Right == NULL))
        {
            if(Tree -> Left)
            {
                ptr = Tree -> Left ;  //set ptr to the left child
            }
            else
            {
                ptr = Tree -> Right ;  //set ptr to the right child
            }

            if(ptr == NULL )
            {
                ptr = Tree ;
                Tree = NULL ;  //set tree to NULL if it has no children
            }
            else
            {
                *Tree = *ptr ;  //copy the contents of ptr to tree
            }
            free(ptr) ;  //free the memory of ptr
        }
        else
        {
            temp = MinN(Tree -> Right) ;  //find the minimum node in the right subtree
            Tree -> Data = temp -> Data ;  //copy data of the minimum node to the current node
            Tree -> Right = Delete_Word(Tree -> Right , temp -> Data.W) ;  //delete the minimum node from the right subtree
        }
    }

    if(Tree == NULL)  //if tree is empty after deletion
    {
        return Tree ;
    }

    Tree -> Height = 1 + Max(GetH(Tree -> Left) , GetH(Tree -> Right)) ;  //update the height of the node

    Balance = GetB(Tree) ;  //check the balance

    //Left-Left Rotation:
    if(Balance > 1 && GetB(Tree -> Left) >= 0)
    {
        return Right_R(Tree) ;  //perform right rotation
    }

    //Right-Right Rotation:
    if(Balance < -1 && GetB(Tree -> Right) <= 0)
    {
        return Left_R(Tree) ;  //perform left rotation
    }

    //Left-Right Rotation:
    if(Balance > 1 && GetB(Tree -> Left) < 0)
    {
        Tree -> Left = Left_R(Tree -> Left) ;  //perform left rotation on left subtree
        return Right_R(Tree) ;  //perform right rotation on the current node
    }

    //Right-Left Rotation:
    if(Balance < -1 && GetB(Tree -> Right) > 0)
    {
        Tree -> Height = Right_R(Tree -> Right) ;  ////perform right rotation on the right subtree
        return Left_R(Tree) ;  //perform left rotation on the current node
    }

    return Tree ;  //return the updated tree
}

struct AVL *MinN(struct AVL *Tree)
{
    if(Tree == NULL)
    {
        return NULL ;
    }

    struct AVL *c ;

    c = Tree ;
    while(c -> Left != NULL)
    {
        c = c -> Left ;  //traverse to the leftmost node
    }

    return c ;  //return the leftmost node (minimum node)
}

void PrintT(struct AVL *Tree)
{
    if(Tree != NULL)
    {
        PrintT(Tree -> Left) ;  //recursively print the left subtree
        printf("%s (%d) -> " , Tree -> Data.W , Tree -> Data.frequency) ;
        PrintT(Tree -> Right) ;  //recursively print the right subtree
    }
}

struct Hash *createTable()
{
    int i ;
    struct Hash *H ;

    H = (struct Hash *)malloc(sizeof(struct Hash)) ;  //allocate memory for the hash table
    if(H == NULL)
    {
        printf("Error!!!\n") ;
        return NULL ;
    }

    for(i = 0 ; i < HashTable_Size ; i++)
    {
        H -> Hash_Table[i] = NULL ;  //initialize all entries in the hash table to NULL
    }

    return H ;  //return the created hash table
}

void Insert_toTable(struct Hash *HT , struct word words)
{
    int index ;
    struct Node *N ;
    struct Node *C ;

    if(HT == NULL)
    {
        printf("Hash table isn't created yet!\n") ;
        return ;
    }

    index = Hashing(words.W) ;  //get the hash index for the word

    N = (struct Node *)malloc(sizeof(struct Node)) ;  //allocate memory for a new node
    N -> Data = words ;  //set the data of the node to the given word
    N -> Next = NULL ;  //initialize the next pointer to NULL

    if(HT -> Hash_Table[index] == NULL)
    {
        HT -> Hash_Table[index] = N ;  //insert the node if the index is empty
    }
    else  //if the index isn't empty
    {
        C = HT -> Hash_Table[index] ;  //traverse to the end of the linked list at the hashed index
        while(C -> Next != NULL)
        {
            C = C -> Next ;
        }

        C -> Next = N ;  //insert the node at the end of the linked list
    }
}

int Hashing(char *w)
{
    int hashValue = 0 ;

    while(*w != '\0')  //traverse the string until the NULL terminator
    {
        hashValue += *w++ ;  //sum the ASCII values of the character
    }

    return (hashValue % HashTable_Size) ;  //return hash value modulo hash table size(index)
}

/*
void printHT(struct Hash *HT)
{
    int i ;
    struct Node *C ;

    if(HT == NULL)
    {
        printf("Hash table isn't created!!!\n") ;
        return ;
    }

    printf("The Hash Table:\n") ;
    for(i = 0 ; i < HashTable_Size ; i++)
    {
        printf("index %d:" , i) ;
        C = HT -> Hash_Table[i] ;  //set C to the head of the linked list at the current index
        while(C != NULL)  //traverse the linked list at the current index
        {
            printf("%s (%d)" , C -> Data.W , C -> Data.frequency) ;
            C = C -> Next ;  //move to the next index
        }

        printf("\n") ;
    }
}
*/

void Add_toTable(struct Hash *HT , struct word newW)
{
    int index ;
    struct Node *C ;
    struct Node *N ;

    if(HT == NULL)
    {
        printf("Hash Table isn't created yet!!!\n") ;
        return ;
    }

    index = Hashing(newW.W) ;  //get the hash index for the new word

    C = HT -> Hash_Table[index] ;  //set C to the head of the linked list at the hashed index
    while(C != NULL)
    {
        if(strcmp(C -> Data.W , newW.W) == 0)  //if the word already exists in the Hash Table
        {
            C -> Data.frequency++ ;  //increment the frequency
            printf("the word '%s' already exists in the Hash Table for '%d' times.\n" , newW.W , C -> Data.frequency) ;
            return ;
        }

        C = C -> Next ;  //move to the next node in the linked list
    }

    N = (struct Node *)malloc(sizeof(struct Node)) ;  //allocate memory for a new node
    N -> Data = newW ;  //set the data of the node to the new word
    N -> Next = HT -> Hash_Table[index] ;  //insert the node at the beginning of the linked list
    HT -> Hash_Table[index] = N ;  //update the head of the linked list

    printf("the word '%s' is inserted into the hash table.\n" , newW.W) ;
}

void Delete_fromTable(struct Hash *HT , char *RemW)
{
    int index ;
    struct Node *C ;
    struct Node *P ;

    if(HT == NULL)
    {
        printf("No Table yet!!!\n") ;
        return ;
    }

    index = Hashing(RemW) ;  //get the hash index for the word to be removed

    C = HT -> Hash_Table[index] ;  //set C to the head of the linked list at the hashed index
    P = NULL ;  //initialize P as the previous node pointer

    while(C != NULL)
    {
        if(strcmp(C -> Data.W , RemW) == 0)  //if the current node contains the word to be removed
        {
            if(P == NULL)  //if it's in the first node of the linked list
            {
                HT -> Hash_Table[index] = C -> Next ;  //update the head of the linked list
            }
            else
            {
                P -> Next = C -> Next ;  //move to the next node (skip/bypass the current node)
            }
            free(C) ;  //free memory allocated for the node
            printf("the word '%s' is removed from the hash table.\n" , RemW) ;
            return ;
        }

        P = C ;  //move P to the current node
        C = C -> Next ;  //move C to the next node in the linked list
    }

    printf("the word '%s' isn't found in the hash table!\n" , RemW) ;
}

void Search_and_changeF(struct Hash *HT , char *WtochF)
{
    int index ;
    struct Node *C ;
    int newF ;

    if(HT == NULL)
    {
        printf("No Hash Table yet!\n") ;
        return ;
    }

    index = Hashing(WtochF) ;  //get the hash index for the word to be searched

    C = HT -> Hash_Table[index] ;  //set C to the head of the linked list at the hashed index
    while(C != NULL)
    {
        if(strcmp(C -> Data.W , WtochF) == 0)  //when the word is found
        {
            printf("the word '%s' is found in the table with current frequency '%d'.\n" , WtochF , C -> Data.frequency) ;
            printf("what is the new frequency of this word?\n") ;
            scanf("%d" , &newF) ;  //get the new frequency from the user
            C -> Data.frequency = newF ;  //update the frequency of the word in the hash table
            printf("the frequency is changed.\n") ;
            return ;
        }

        C = C -> Next ;  //move to the next node in the linked list
    }

    printf("the word '%s' isn't found in the hash table.\n" , WtochF) ;
}

int find_unique(struct Hash *HT)
{
    int Total_unique = 0 ;
    int i ;
    struct Node *C ;

    if(HT == NULL)
    {
        printf("No table yet!!!\n") ;
        return 0 ;
    }

    for(i = 0 ; i < HashTable_Size ; i++)  //iterate through each index of the hash table
    {
        C = HT -> Hash_Table[i] ;  //set C to the head of the linked list at the current index
        while(C != NULL)  //traverse the linked list at the current index
        {
            if(C -> Data.frequency == 1)  //if the word is unique(frequency = 1)
            {
                Total_unique++ ;  //increment the counter of the unique words
            }

            C = C -> Next ;  //move to the next node in the linked list
        }
    }

    return Total_unique ;
}

struct word highestF(struct Hash *HT)
{
    struct word most_frequent_word = {NULL , 1} ;  //initialize most frequent word to no word/NULL and frequency = 1;
    int i ;
    struct Node *C ;

    for(i = 0 ; i < HashTable_Size ; i++)  //iterate through each index of the hash table
    {
        C = HT -> Hash_Table[i] ;  //set C to the head of the linked list at the current index
        while(C != NULL)  //traverse the linked list at the current index
        {
            if(most_frequent_word.W == NULL || C -> Data.frequency > most_frequent_word.frequency)
            {
                //update the most frequent word if a word with higher frequency is found
                strcpy(most_frequent_word.W , C -> Data.W) ;
                most_frequent_word.frequency = C -> Data.frequency ;
            }

            C = C -> Next ;  //move to the next word in the linked list
        }
    }

    return most_frequent_word ;
}
