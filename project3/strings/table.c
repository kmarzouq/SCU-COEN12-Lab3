/* Khondakar Marzouq Mujtaba
 *
 * A program that has functions to creates sets of strings and manipulate and/or searches them using a Hash function
 * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
// creates a set data type. Big O(1)
struct set{
	int count;
	int length;
	char **data;
	char *flags;
};
// creates a hashing function that takes in string and returns an index. Big O(1)
unsigned  strhash(char *s){
	unsigned  hash = 0;
	while (*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}
// a search function which takes in the set ptr, a string, and the address of a found variable. It uses the hash function to start and then finds the closest positions possible to the string in the set. If the item is found, the found variable is set to true, otherwise it is false. Big O(n)
static int search (SET *sp, char* elt, bool *found){
	assert(sp!=NULL);
	int x;
	int res=-1;
	int z = strhash(elt)%sp->length;
	for(x=0;x< sp->length;x++){
		int index=(x+z)%sp->length;
		if (sp->flags[index]=='f'){
			if (strcmp(sp->data[index],elt)==0){
				*found = true;
				return index;
				}
			}
		
		if (sp->flags[index]=='d'&&res==-1){
			res=index;
		}
		if(sp->flags[index]=='e'){
			*found= false;
			if (res!=-1){
				return res;
				}
			return index;
			}
		}
	*found = false;
	return res;
	}
//Creates the set data type. Big O(n)
SET *createSet(int maxElts){
	SET* sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count =0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*sp->length);
	sp->flags = malloc(sizeof(char)*sp->length);
	assert(sp->data!=NULL);
	int i;
	for (i=0;i<sp->length;i++){
		sp->flags[i]='e';
		}
	return(sp);
	}

//Destroys a set. Big O(n)
void destroySet(SET *sp){
	assert (sp!=NULL);
	int i;
	for(i=0;i < sp->length;i++){
		if (sp->flags[i]=='f'){
			free(sp->data[i]);
			}
		}
	free (sp->data);
	free (sp->flags);	
	}
//returns the number of elements in a set. Big O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
	}
// takes in a set ptr and a string and adds that element to the set by hashing and finding the closest possible index to the hash. It will not do anything if the element is found. Big O(n)
void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	bool found;
	int ind = search(sp, elt,&found);
	if (sp->length==sp->count){
		printf("array full");
		exit(1);
		}	
	
	else if(found==false){
			sp->data[ind]=strdup(elt);
			sp->flags[ind]='f';
			sp->count++;
			}
		
}
//This funtion removes an element from a set. Big O(n)
void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	bool found;
	int ind = search(sp, elt, &found);
	if (found==true){
		free(sp->data[ind]);
		sp->flags[ind]='d';
		sp->count--;
		}
	}
//searches a set for an element. Will return the element if found, otherwise it will return NULL. Big O(n)
char *findElement(SET *sp, char *elt){
		assert(sp!=NULL);
		bool found;
		int ind = search(sp, elt, &found);
		if(found==true){
			return sp->data[ind];
			}
		else{
			return NULL;
			}
	}

//creates and returns an array of all the elements in a set. Big O(n)
char **getElements(SET *sp){
	assert(sp!=NULL);
	char** arrstr;
	arrstr=malloc(sizeof(char*)*sp->count);
	int i;
	int x=0;
	for(i=0; i< sp->length; i++){
		if(sp->flags[i]=='f'){
			arrstr[x]=sp->data[i];
			x++;
			}
		}
	return arrstr;
}	
