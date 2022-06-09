#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE_WORD 100
#define SIZE_ABC 26
#define SIZE_ABC_DOUBLED 52
#define UPPERCASE 26 /*It is added to each uppercase letter so that it enters the correct index in the array (at least after index 26)*/
#define SIZE_LINE 500

typedef struct Word
{
	int m_count;                           
	char m_word[SIZE_WORD];
	struct Word* m_next;
}Word;

/*prints all the words in the Word array*/
PrintWords(Word *_pArr[], int _size){
	Word *temp;
	int i, j;
	for(i = 0; i < _size; i++){
		temp = _pArr[i];
		while(temp != NULL){		
			printf("%s %d\n", temp->m_word, temp->m_count);
			temp = temp->m_next;
		}
	}
}

/*Creates new Word and sets it's counter to 1 */
Word* CreateWord(char* _word){
	Word *new = (Word*)malloc(sizeof(Word));
	if(new == NULL){
		return NULL;  /* add NULL check in the function and free*/
	}
	strcpy(new->m_word, _word);
	new->m_count = 1;
	return new;
}

/* Insert a word to the Word-list in the right place*/
Word* placeWordInList(Word *_head, char *_word){
	Word *current, *prev, *new;
	if(_head == NULL || 0 > strcmp(_word, _head->m_word)){
		new = CreateWord(_word);
		new->m_next = _head;
		return new;
	}
	current = _head;
	while(current != NULL){
		if(0 == strcmp(_word, current->m_word)){
			current->m_count++;
			return _head;
		}
		else if(0 > strcmp(_word, current->m_word)){			
			new = CreateWord(_word);
			new->m_next = current;
			prev->m_next = new;
			return _head;
		}
		else{
			prev = current;
			current = current->m_next;
		}
	}
	if(current == NULL){
		new = CreateWord(_word);
		new->m_next = NULL;
		prev->m_next = new;
		return _head;
	}	
}

/* prints every single word in text and it's frequency*/
void wordFrequency(char * _file){
	int i = 0, j;
	char word[SIZE_WORD];
	Word *abc[SIZE_ABC]= {0};
	FILE *fp;
	fp = fopen(_file, "r");
	if(fp == NULL){
		printf("file could not be upload!\n");
		return;
	}
	fscanf(fp,"%s",word);						
	while(!feof(fp)){  
		for(j = 0; word[j] != '\0'; j++){
		 	if((word[j]>= 'A' && word[j] <= 'Z')){
 				word[j] += ('a' - 'A');	
		 	}
		}
		i = word[0]-'a';
		abc[i] = placeWordInList(abc[i], word); /*return head of list*/
		fscanf(fp,"%s",word);						
	}
	PrintWords(abc, SIZE_ABC);	
	fclose(fp);	
}
/****************************************************************/
/****************************************************************/
void SetCharsToZero(char *_chars){
	int i;
	for(i = 0; _chars[i] != '\0'; i++){
		_chars[i] = 0;
	}
}

void PrintCharAndFreq(char *_chars, int *_freq){
	int i;
	for(i = 0; i < SIZE_ABC_DOUBLED; i++){
		if(0 != _freq[i] && 0 != _chars[i]){
			printf("%c %d\n", _chars[i], _freq[i]);
		}
	}
}

/* prints every single character in text and it's frequency*/
void CharFrequency(char * _file){
	int i, j;
	char lineAr[SIZE_LINE];
	char chars[SIZE_ABC_DOUBLED] = {0};
	int freq[SIZE_ABC_DOUBLED] = {0};
	FILE *fp;
	if(_file == NULL){
		printf("NULL\n");
		return;
	}
	fp = fopen(_file, "r");
	if(fp == NULL){
		printf("file could not be upload!\n");
		return;
	}
	/*SetCharsToZero(chars);*/
	fgets(lineAr, SIZE_LINE, fp);					
	while(!feof(fp)){
		for(i = 0; lineAr[i] != '\0'; i++){
			
			if((lineAr[i] >= 'A' && lineAr[i] <= 'Z') || (lineAr[i] >= 'a' && lineAr[i] <= 'z')){
				
				if((lineAr[i] >= 'A' && lineAr[i] <= 'Z')){    
					j = (lineAr[i] - 'A') + UPPERCASE;
					freq[j]++;
					chars[j] = lineAr[i];					
				}
				else{
					j = lineAr[i]-'a';
					freq[j]++;
					chars[j] = lineAr[i];
				}
			} 
		}
		fgets(lineAr, SIZE_LINE, fp); 							
	}
	PrintCharAndFreq(chars, freq);
	fclose(fp);	
}


int main(){
	
	wordFrequency("ex8_text");
	
	CharFrequency("ex9_text");
}








