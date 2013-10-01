#include <stdio.h>
#include <string.h>
#include "jsKeyWords.h"
enum states {
	before = 0, inside = 1, after = 2
};

struct branch {
	unsigned char new_state:2;
	unsigned char should_putchar:1;
};

struct branch the_table[3][3] = {
				 /*	''			'\n'		others */
		/*before*/ {{before,0},{before,1},{inside,1}},
		/*inside*/ {{after, 0},{before,1},{inside,1}},
		/*after */ {{after, 0},{before,1},{after, 0}}
};

char words[20];
int wordIndex;

void step(enum states *state,int c) {
	int idx2 = (c == ' ')?0:(c == '\n' || c == '('||c == ')')?1:2;
	struct branch *b = &the_table[*state][idx2];
	*state = (enum states)(b->new_state);
	
	if(b->should_putchar){
		//putchar(c);
	}

	if(idx2 == 2){
		words[wordIndex] = c;
		wordIndex++;
	}else if( idx2 ==1){
       printf("%s\n",words);
	   memset(words,'\0',strlen(words));
	   wordIndex = 0;
	}
	//printf("%d\t\n",idx2);	
}

//解析JS语句
char *testJSSource = "alert(1111);";
//char keyWords[5][10] = {"if","else","switch","case","alert"};

void main(int argc,char **argv){
    int c;
	wordIndex = 0;
	enum states state = before;
	int len = strlen(testJSSource);
	int i = 0;
	while(i < len){
		c = testJSSource[i];
		step(&state,c);
		i++;
	}
	printf("%s\n",words);
}
