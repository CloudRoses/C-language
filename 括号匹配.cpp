


#include<stdio.h>
#include<stdlib.h>




#define ERROR 0
#define OK 1




typedef int Status;
typedef struct {
	char *base;
	char *top;

	int stackSize;
}Stack;
typedef char * BracketList;



Status initStack(Stack &stack) {
	stack.base = stack.top = (char *)malloc(sizeof(char) * 100);
	stack.stackSize = 0;

	return OK;
}//initStack



Status push(Stack &stack, char bracket) {
	if (stack.stackSize >= 100) {
		printf("Error,stack is full!");
		return ERROR;
	}

	*stack.top++ = bracket;

	stack.stackSize++;

	return OK;
}//push



Status pop(Stack &stack, char &bracket) {
	if (stack.stackSize <= 0) {
		printf("Error,stack is empty!");
		return ERROR;
	}

	bracket = *(--stack.top);

	stack.stackSize--;

	return OK;
}//pop



int traversRow(char bracket) {
	char bracketTable[2][3] = { {'(','[','{'},{')',']','}' } };
	
	for (int i=0; i <= 1; i++) {
		for (int j = 0; j <= 2; j++) {
			if (bracket == bracketTable[i][j])
			return i;
		}//for
	}//for

	return OK;
}//traversRow



int traversColumn(char bracket) {
	char bracketTable[2][3] = { {'(','[','{'},{')',']','}'} };

	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 2; j++) {
			if (bracket == bracketTable[i][j])
			return j;
		}//for
	}//for

	return OK;
}//traversColumn



Status getInputBracketList(BracketList &bracketList) {
	bracketList = (char *)malloc(sizeof(char) * 100);

	int i = 0;		//count
	
	while (1) {
		char bracket;
		printf("please input a bracket:");
		scanf_s("%c", &bracket, 1);
		getchar();

		if (bracket == 'q') {
			break;
		}

		bracketList[i] = bracket;
		i++;
	}//while

	bracketList[i] = '\0';

	return OK;
}//getInputBracketList


int judge(Stack stack, BracketList bracketList) {

	int i = 0;		//count

	while (true) {
		char getBracket = bracketList[i];
		if (getBracket != '\0') {
			int choice = traversRow(getBracket);

			switch (choice) {
			case 0:
				push(stack, getBracket);
				break;
			case 1:
				if (stack.stackSize == 0) {
					printf("Error,right bracket can not input first!");
					return ERROR;
				}//if

				int stackBracketColumn = traversColumn(*(stack.top - 1));
				int getBracketColumn = traversColumn(getBracket);

				if (stackBracketColumn != getBracketColumn) {
					printf("Error,can not match the left bracket!");
					return ERROR;
				}
				else {
					char saveBracket;
					pop(stack, saveBracket);
				}//if-else

			}//switch
		}//if
		else {
			break;
		}

		i++;
	}//while
	
	if (stack.stackSize != 0) {
		printf("Error,leave left bracket!");
		return ERROR;
	}
	
	printf("Ok,match!");
	return OK;
}//judge



int main() {
	BracketList bracketList;
	getInputBracketList(bracketList);
	

	Stack stack;
	initStack(stack);

	
	int result;
	result=judge(stack, bracketList);

	if (result == OK) {
		printf("congradualation!");
	}
	else {
		printf("bug......")
	}
}
