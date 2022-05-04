/* Khondakar Marzouq Mujtaba
 *
 * A program that contains functions that allow it to create sets of multiple data types and then is able to manipulate them using hash functions
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
//creating set data type that can take multiple data types. Big O(1)
struct set{
	int count;
	int length;
	void **data;
	char *flags;
	int(*compare)();
	unsigned (*hash)();
};
// creating a search function that uses a hash to find the closest open spot for an element Big O(n)
static int search (SET *sp, void *elt, bool *found){
	assert(sp!=NULL);
	int x;
	int res=-1;
	int z = (*sp->hash)(elt)%sp->length;
	for(x=0;x< sp->length;x++){
		int index=(x+z)%sp->length;
		if (sp->flags[index]=='f'){
			if ((*sp->compare)(sp->data[index],elt)==0){
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
//creates a set of elements of varying data types the size of maxElts. Big O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)()){
	SET* sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count =0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(void*)*sp->length);
	sp->flags = malloc(sizeof(char)*sp->length);
	assert(sp->data!=NULL);
	int i;
	for (i=0;i<sp->length;i++){
		sp->flags[i]='e';
		}
	sp->compare = compare;
	sp->hash = hash;
	return (sp);
	}

//destroys a set and deallocates the memory we reserved. Big O(1)
void destroySet(SET *sp){
	assert (sp!=NULL);
	int i;
	free (sp->data);
	free (sp->flags);
	free (sp);
	}
//returns the number of elements in the set. Big O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
	}
//searches for a spot to place an element in using the has function. If the element is found, it stops the function. BigO(n)
void addElement(SET *sp, void *elt){
	assert(sp!=NULL);
	bool found;
	int ind = search(sp, elt,&found);
	if (sp->length==sp->count){
		exit(1);
		}	
	
	else if(found==false){
			sp->data[ind]= elt;
			sp->flags[ind]='f';
			sp->count++;
			}
		
}
//removes an element from the set. Big O(n)
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL);
	bool found;
	int ind = search(sp, elt, &found);
	if (found==true){
		sp->flags[ind]='d';
		sp->count--;
		}
	}
// finds an element and returns it if it is found. Otherwise it returns NULL. Big O(n)
void *findElement(SET *sp, void *elt){
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

// returns and array of the elements in a set. Big O(n)
void *getElements(SET *sp){
	assert(sp!=NULL);
	void** arrstr;
	arrstr=malloc(sizeof(void*)*sp->count);
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
