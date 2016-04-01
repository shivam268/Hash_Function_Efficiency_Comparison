/*
Parikh Shivam
ICSI 402
Assignment 1
UNIX ID: sp191221
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>  
  
#define MAXLENGTH 16
#define ARRAYSIZE 10000
#define COMMANDENTRY 3

FILE *inputFile; 								     // pointer to input file
FILE *outputFile;                                    // pointer to output file

int size;//holds first line from input file
int numLine = 0;
int i; // for loop incrementer

int maxEntryTableOne;
int maxEntryTableTwo;

int minEntryTableOne;
int minEntryTableTwo;


int numNonEmptyOne = 0;
int numNonEmptyTwo = 0;

char line[MAXLENGTH]; //line will each line from inputfile
char lineCopy[MAXLENGTH]; // just a backup of line

int locationOne;
int locationTwo;


// node defination
struct node {
    char *text;
    struct node *next;
};


// define two arrays to size 10000
struct node* hashOne[ARRAYSIZE];
struct node* hashTwo[ARRAYSIZE];


struct node *current; // current pointer to go through the list



//////////// Prototypes ///////////
void setHashOne(int index);
void setHashTwo(int index);
void allFromHashTable();
void output();
void chekNonEmpty();
int listLengthTableOne(int dest);
int listLengthTableTwo(int dest);
void checkMaxLength();
void checkMinLength();
///////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///											   ///
///		        MAIN METHOD STARTS				   ///
///								     			   ///
///////////////////////////////////////////////////////////////


int main(int args, char *argv[])
{
    // number of commands must qual to 3 or print error and exit
    if(args != COMMANDENTRY){
        printf("ERROR: Number Command Entries Mismatch \n");
        exit(1);
    }
    
    else{
  

    ////// input File Open Check ////
    
  inputFile = fopen(argv[1], "r"); 						// this will open the given file for reading
  
  if((inputFile == NULL)){
      printf("ERROR: Input file cannot be opened \n"); 	// It will give error message about unsuccessful file open
    exit(1); 											// it the will exit the programm
    }
  else{
  }
  
    ///// output File Open Check ////
        
    outputFile = fopen(argv[2], "w");
    if((outputFile == NULL)){
        printf("ERROR: Output file cannot be opened for WRITING\n"); // print error
        exit(1); // exit the program
    }
    else{
    }
  
    
    
    
    
    //read the first line store that as a string
    // and then read line by line and call appropriate function to populate the arrays
    
        
    fscanf(inputFile, "%s", line); // stores size of array as a char
    
    size = atoi(line); // convert that char to int
    
    //read line until we reach to end and store eachline into line variable
        
    while(fscanf(inputFile, "%s", line) != EOF){
        
        numLine++; // number of lines only counts lines without including 
        
        strcpy(lineCopy, line); // backup copy
        
        locationOne = hash_example_one(line, size); // method call will return the hash value for that string
        
        setHashOne(locationOne); // calls function to populate array with location index
        
        locationTwo = hash_example_two(line, size); // method call will return the hash value for second hash function
        
        setHashTwo(locationTwo); // calls function to populate second hash table with location index
        
    }
    
    // close the file
      if (fclose(inputFile) == EOF) { /* Error in closing the file */
        printf("Error in closing file input file.\n");
      }
      
    chekNonEmpty(); // count non empty lists
    
    checkMaxLength(); // check max length of list
    
    checkMinLength(); // check min length of list
    
    output(); // print the stats on output file
    
    
    }
    return 0;
}
///////////////////////////////////////////////////////////////
///									     		   ///
///			     MAIN METHOD ENDS	                  ///
///								     			  ///
//////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
///									     		   ///
///			  setHashOne(int index)  starts             ///
///								     			   ///
///////////////////////////////////////////////////////////////
/*
 setHashOne takes index location which is hash key returnes by hash function as a parameter and it and copies the character 
 that it is dealing ith onto a variable called input it will check whether the index location on array is pointing to any 
 node or not and if its not then it creates a pointer to new node and copies the character as a one of the values on node
 also makes current pointer to point to it and next pointing to NULL
 
 If there is already a node there, it will reach at the end of linked list and then add a node to it, copies the character onto it
 */
void setHashOne(int index){
    char *input = (char *) malloc(sizeof(char)*MAXLENGTH); // create space for max character
    
    if(input == NULL){ // if malloc fails
        printf("Error Malloc Fail \n"); // print error
        exit(1); // exit the program
    }
    
    strcpy(input, line); // copy the character
    
    if(hashOne[index] == NULL){ // there is no node at all
        hashOne[index] = (struct node*) malloc(sizeof(struct node)); // make hashOne[index] pointer point to  new node
      
    if(hashOne[index] == NULL){ // if malloc fail
        printf("Error Malloc Fail \n"); // print error
        exit(1); // exit the program
      }
        current = hashOne[index]; // current will point to the same address as hashOne[index]
        current->text = input;    // node text will be assigned
        current->next = NULL;     // point next to NULL
    }
    else{ /*if there is at least a node in a linked list*/
        current = hashOne[index]; // make current pointer to point at given index
        while (!current->next == NULL) { // loop until it reaches to last node
            current = current->next;     // moves current pointer
        }
        
        // now the current pointer is pointing to last node
        current->next = (struct node*) malloc(sizeof(struct node)); // make next pointer point to new node
        if(current->next == NULL){ // if malloc fails
        printf("Error Malloc Fail \n"); // print error
        exit(1); // exit the program
      }
        current = current->next; // current pointer will move on to next-new node
        current->text = input;   // assign text to node
        current->next = NULL;    // make next point to NULL
    }
}
///////////////////////////////////////////////////////////////
///                                                         ///
///             setHashOne(int index)  ends                 ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///             setHashTwo(int index)  starts               ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 setHashOne takes index location which is hash key returnes by hash function as a parameter and it and copies the character
 that it is dealing ith onto a variable called input it will check whether the index location on array is pointing to any
 node or not and if its not then it creates a pointer to new node and copies the character as a one of the values on node
 also makes current pointer to point to it and next pointing to NULL
 If there is already a node there, it will reach at the end of linked list and then add a node to it, copies the character onto it
 */

void setHashTwo(int index){
  
    char *input = (char *) malloc(sizeof(char)*MAXLENGTH); // create space for char
    
    if(input == NULL){ // if malloc fails
        printf("Error Malloc Fail \n"); // print error
        exit(1); // exit the program
    }
    
    strcpy(input, line); // copy line onto input
  
    
    if(hashTwo[index] == NULL){ // if there is no node at all
      
       hashTwo[index] = (struct node*) malloc(sizeof(struct node)); // make hashOne[index] pointer point to  new node 
      if(hashTwo[index] == NULL){ // if malloc fails
        printf("Error Malloc Fail \n"); // print error message
        exit(1); // exit the program
      }
        
      current = hashTwo[index]; // make current pointer point to hashTwo
        current->text = input;  // assign text values
        current->next = NULL;   // make next point to NULL
    }
    else{ /*if there is at least a node in a linked list*/
        current = hashTwo[index]; // make current pointer to point at given index
        while (!current->next == NULL) { // loop until it reaches to last node
            current = current->next;  // moves current pointer
        }
        // now the current pointer is pointing to last node
        
        current->next = (struct node*) malloc(sizeof(struct node)); // make next pointer point to new node
      if(current->next == NULL){ // if malloc fails
        printf("Error Malloc Fail \n"); // print error
        exit(1); // exit the program
      }
        current = current->next; // current pointer will move on to next-new node
        current->text = input;   // assign text to node
        current->next = NULL;    // make next point to NULL
    }
  
}
///////////////////////////////////////////////////////////////
///                                                         ///
///             setHashTwo(int index)  ends                 ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///                 checkNonEmpty() starts                  ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 counts non empty lists.
 loops through and checks it is not pointing to NULL then
 increment counter
 */

void chekNonEmpty(){
    for(i = 0; i < size; i++){
        if(hashOne[i] != NULL){ // if hash table one's index location is not pointing to NULL
        numNonEmptyOne++;       // increment counter
        }
        if(hashTwo[i] != NULL){ // if hash table one's index location is not pointing to NULL
            numNonEmptyTwo++;   // increment counter
        }
    }
}
///////////////////////////////////////////////////////////////
///                                                         ///
///                 checkNonEmpty() ends                    ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///           listLengthTableOne(int dest) starts           ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 this function takes index location as a parameter and 
 returns the size of linked list
 */
int listLengthTableOne(int dest){
    int listSize = 0; // listSize is 0 to start with
    current = hashOne[dest]; // make current pointer point to given index on hash table one
    
    if(current == NULL){ //  if the list is empty
        return listSize; //  returns listSize which is ZERO
    }
    
    while(current != NULL){ // loops through the list until it reaches the last node
        listSize++;         // increment the listSize by one every time
        current = current->next; // move current pointer
    }
    
    return listSize; //return listSize
}
///////////////////////////////////////////////////////////////
///                                                         ///
///           listLengthTableOne(int dest) ends             ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///                 listLengthTableTwo() starts             ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 this function takes index location as a parameter and
 returns the size of linked list
 */
int listLengthTableTwo(int dest){
    int listSize = 0; // listSize is 0 to start with
    current = hashTwo[dest]; // make current pointer point to given index on hash table two
    
    if(current == NULL){ //  if the list is empty
        return listSize; //  returns listSize which is ZERO
    }
    
    while(current != NULL){ // loops through the list until it reaches the last node
        listSize++;         // increment the listSize by one every time
        current = current->next; // move current pointer
    }
    
    return listSize; // return listSize
}
///////////////////////////////////////////////////////////////
///                                                         ///
///                 listLengthTableTwo() ends               ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///                 checkMaxLength() starts                 ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 compares lengths and if finds greater length copies it over
 also calls listLengthOne(int) and listLengthTwo(int) functions to get size of linked list
 */
void checkMaxLength(){
    int tempSize = 0; // temp size to store size of linked list
    
    // following if for Hash Table One
    for(i = 0; i < size; i++){ // run through the array
        tempSize = listLengthTableOne(i); // find the size of each linked list
        if(maxEntryTableOne < tempSize){  // compare if find greater value then
            maxEntryTableOne = tempSize;  // replace it with greater value
        }
    }
    
    // following is for Hash Table Two
    for(i = 0; i < size; i++){ // run through the array
        tempSize = listLengthTableTwo(i); // find the size of each linked list
        if(maxEntryTableTwo < tempSize){  // compare if find greater value then
            maxEntryTableTwo = tempSize;  // replace it with greater value
        }
    }
    
}
///////////////////////////////////////////////////////////////
///                                                         ///
///                 checkMaxLength() ends                   ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///                 checkMinLength() starts                 ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 compares lengths and if finds lesser length copies it over
 also calls listLengthOne(int) and listLengthTwo(int) functions to get size of linked list
 */
void checkMinLength(){
    int tempSize = 0; // temp size to store size of linked list
    
    // copy over max length onto min length
    // can't make it ZERO, because ZERO will always be lesser than any size in this case since we are finding size of non empty list
    minEntryTableOne = maxEntryTableOne;
    minEntryTableTwo = maxEntryTableTwo;
    
    
    // following if for Hash Table One
    for(i = 0; i < size; i++){
        if(hashOne[i] == NULL){ // it is empty list so leave it
        }
        else{ // non empty list
            tempSize = listLengthTableOne(i); // find size of current list
            if(minEntryTableOne > tempSize){  // if its less than what we have as a min size
                minEntryTableOne = tempSize;  // then replace min size 
            }
            else{}
        }
    }
    
    // following if for Hash Table Two
    for(i = 0; i < size; i++){
        if(hashTwo[i] == NULL){ // it is empty list so leave it
        }
        else{ // non empty list
            tempSize = listLengthTableTwo(i); // find size of current list
            if(minEntryTableTwo > tempSize){  // if its less than what we have as a min size
                minEntryTableTwo = tempSize;  // then replace min size
            }
            else{}
        }
    }
}
///////////////////////////////////////////////////////////////
///                                                         ///
///                 checkMinLength() ends                   ///
///                                                         ///
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
///                                                         ///
///                 output() starts                         ///
///                                                         ///
///////////////////////////////////////////////////////////////
/*
 this method will write all the output on to output file given in a command line
 */
void output(){
    
    // find average and restrict the number to two decimals when it prints out
    float avgOne = (float)numLine/(float)numNonEmptyOne;
    float avgTwo = (float)numLine/(float)numNonEmptyTwo;
    
    
    // print out result for Hash table 1
    fprintf(outputFile, "Results for Hash Function I: \n\n");
    fprintf(outputFile, "Hash table size = %d\n", size);
    fprintf(outputFile, "Number of non-empty lists = %d\n", numNonEmptyOne);
    fprintf(outputFile, "Maximum number of entries in a list  = %d\n", maxEntryTableOne);
    fprintf(outputFile, "Minimum number of entries in a non-empty list = %d\n", minEntryTableOne);
    fprintf(outputFile, "Average number of entries in a non-empty list = %.02lf\n\n\n", avgOne);//restrict to two decimals
    
    // print out result for Hash table 2
    fprintf(outputFile, "Results for Hash Function II: \n\n");
    fprintf(outputFile, "Hash table size = %d\n", size);
    fprintf(outputFile, "Number of non-empty lists = %d\n", numNonEmptyTwo);
    fprintf(outputFile, "Maximum number of entries in a list  = %d\n", maxEntryTableTwo);
    fprintf(outputFile, "Minimum number of entries in a non-empty list = %d\n", minEntryTableTwo);
    fprintf(outputFile, "Average number of entries in a non-empty list = %.02lf\n", avgTwo);//restrict to two decimals
    
    
    // close output file
  if (fclose(outputFile) == EOF) { /* Error in closing the file */
    printf("Error in closing file output file.\n");
  }
    
}
///////////////////////////////////////////////////////////////
///                                                         ///
///                 output() ends                           ///
///                                                         ///
///////////////////////////////////////////////////////////////
        
        
        
        
        
        
        
        
