#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define max_name 256
#define tablesize 10

typedef struct
    {

        char name [max_name];
    }person;
//making a hash table its an array of pointers to people struct , pointers because for pointers i don't need space for tables means i directly fill the table
// 2nd reason to use the pointers that it makes easy for me to tell when a spot in the table is empty because i can just set the pointer to null
//making a function to setup the table
person * hash_table[tablesize];
void init_hashtable()
{
    //initially i want all the entries to be empty so :
    for(int i = 0; i <tablesize ; i ++)
    {
        hash_table [i] = NULL;
    }
    //table is empty
}

// i am declaring hash func which takes a input name and map it to a location in a table  which is an unsigned int:
unsigned int hash (char *name )
{
    int length = strlen(name ); //it woudl calculate the length of the string
    //now i would go through the string at one character at a time and add the  ASCII values of char
    unsigned int hash_value = 0;
    for(int i =0 ;i <length ; i++)
    {
        hash_value += name [i]; //we would add each char ascii value to the sum
        hash_value =  ( hash_value * name[i] ) ; //for getting more random number
        hash_value =  hash_value % tablesize ; //keeping the num bewtween 0 and table size


    }
    return hash_value ; //we can return the sum when we are done
}
//making a function that would insert something in the table
//this func would return a boolean true if we successfully inserted otherwise false
bool hash_table_insert(person *p)
{
    if( p == NULL) //if it is null value
    {
        return false ;
    }
    int index = hash(p->name); //index or location where we are going to try the index of a person .
    //making linear probing :
    for(int i =0 ; i <tablesize ; i++){
        int key = (i+index) % tablesize ;
        if(hash_table[key] == NULL)
        {
            hash_table[key] = p;
            return true;
        }
    } return false ;

}

void print_table ()
{
    printf("Start \n");
    for(int i = 0 ; i<tablesize ; i++)
    {
        if(hash_table[i] == NULL)
        {
            printf(" %i \t-----\n" ,i);
        }
        else
        {
            printf(" %i\t%s\n",i,hash_table[i]->name);

        }
    }
    printf("End \n \n");
}
//the main concept of the table is too lookup people
//so now lets make a lookup function
//it find a person on the table by their name
person *hash_table_lookup (char *name)
{
    int index = hash(name);
    //adding linear logic in the lookup
    for(int i = 0 ; i<tablesize ; i++)
    {
        int key = (index +i) %tablesize;
        if(hash_table[key] != NULL && strncmp(hash_table[key]->name , name , 50)== 0)
    { //strncmp() func is used to compare two strings with each other to limited no of char passed
        return hash_table[key];
    }
    }
    return NULL ;

}

int main(){
    init_hashtable();
    print_table();
    //lets make some people
    person jacob = {.name = "jacob"};
    person kate = {.name = "kate"};
    person mpho = {.name = "mpho"};
    person Sarah = {.name = "Sarah"};
    person Edna = {.name = "Edna"};
    person Eliza = {.name = "Eliza"};
    person Robert = {.name = "Robert"};
    person Jane = {.name = "Jane"};


    //inserting these people in the hashtable
    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&Sarah);
    hash_table_insert(&Edna);
    hash_table_insert(&Eliza);
    hash_table_insert(&Robert);
    hash_table_insert(&Jane);

    //print
    print_table();

    //looking up  a name in the table :
    person *tmp = hash_table_lookup("mpho");


    if(tmp == NULL )
    {
        printf("we don't found it \n ");
    }
    else
    {
        printf("Found %s \n",tmp ->name);
    }
    //lookin up a value which is not present in the table
    tmp = hash_table_lookup("george");
     if(tmp == NULL )
    {
        printf("we don't found it \n");
    }
    else
    {
        printf("Found %s \n",tmp ->name);
    }



    return 0 ;

}
