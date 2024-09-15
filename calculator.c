#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#define MAX_ARR_SIZE 1024


int numOperands = 0; // Global Variable

char *noSpaces(char calculation[]) 
{
	int length = strlen(calculation);
	char *noSpaces = NULL;
	noSpaces = (char *)calloc(length + 1, sizeof(char));
	int j = 0;
	
	if (noSpaces != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			if (calculation[i] != ' ' && calculation[i] != '\n')
			{	
				noSpaces[j] = calculation[i];
				j++;
			}
		}
		
		noSpaces[j] = '\0';
		noSpaces = (char *)realloc(noSpaces, j + 1);
	}
	
	return noSpaces;
}

char *operatorsArray(char noSpaces[]) 
{
	int length = strlen(noSpaces);
	
	char *operators = NULL;
	operators = (char *)calloc(length, sizeof(char));	// size of char because we need to create enough memory to store each character,
															// and we have strlen(noSpaces) + 1 characters (account for '\0')
	int j = 0;
	
	if (operators != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			if ((noSpaces[i] == '+' && ((isdigit(noSpaces[i + 1]) && isdigit(noSpaces[i - 1])) || (noSpaces[i + 1] == '(' && 
			isdigit(noSpaces[i - 1])) || (noSpaces[i - 1] == ')' && noSpaces[i + 1] == '(') || (noSpaces[i - 1] == ')' && 
			isdigit(noSpaces[i + 1])) || ((noSpaces[i + 1] == '+' || noSpaces[i + 1] == '-') && (noSpaces[i - 1] == ')' || 
			isdigit(noSpaces[i - 1]))))) || (noSpaces[i] == '-' && ((isdigit(noSpaces[i + 1]) && isdigit(noSpaces[i - 1])) || 
			(noSpaces[i + 1] == '(' && isdigit(noSpaces[i - 1])) || (noSpaces[i - 1] == ')' && noSpaces[i + 1] == '(') || 
			(noSpaces[i - 1] == ')' && isdigit(noSpaces[i + 1])) || ((noSpaces[i + 1] == '-' || noSpaces[i + 1] == '+') && 
			(noSpaces[i - 1] == ')' || isdigit(noSpaces[i - 1]))))) || noSpaces[i] == '*' || noSpaces[i] == '/' || 
			noSpaces[i] == '(' || noSpaces[i] == ')' || noSpaces[i] == '^')
			{
				operators[j] = noSpaces[i];
				j++;
			}
		}
		
		operators[j] = '\0';
		
		operators = (char *)realloc(operators, j + 1);
	}
	
	return operators;
}

float *operandsArray(char noSpaces[]) 
{
	numOperands = 0;
	
	char *copy = NULL;
	copy = noSpaces;
	
	int length = strlen(copy);
	
	float *operands = NULL;
	operands = (float *)calloc(length, sizeof(float));
	
	char *operators = NULL;
	operators = operatorsArray(noSpaces);
	
	char *endptr = NULL;
	int index = 0;
	
	if (operands != NULL)
	{
		if (*copy == '(')
		{
			for (int i = 0; i < length; i++)
			{
				if (isdigit(copy[i]) || copy[i] == '+' || copy[i] == '-')
				{
					copy += i;
					break;
				}
			}
		}
		
		while (*copy != '\0')
		{
			operands[index] = strtof(copy, &endptr);
			copy = endptr;
			
			index++;
			numOperands++;
		
			while (*copy != '\0' && ((*copy == '+' && ((isdigit(*(copy + 1)) && isdigit(*(copy - 1))) || 
			(*(copy + 1) == '(' && isdigit(*(copy - 1))) || (*(copy - 1) == ')' && *(copy + 1) == '(') || 
			(*(copy - 1) == ')' && isdigit(*(copy + 1))) ||((*(copy + 1) == '+' || *(copy + 1) == '-') && 
			(*(copy - 1) == ')' || isdigit(*(copy - 1)))))) || (*copy == '-' && ((isdigit(*(copy + 1)) && 
			isdigit(*(copy - 1))) || (*(copy + 1) == '(' && isdigit(*(copy - 1))) || (*(copy - 1) == ')' && 
			*(copy + 1) == '(') || (*(copy - 1) == ')' && isdigit(*(copy + 1))) ||((*(copy + 1) == '-' || 
			*(copy + 1) == '+') && (*(copy - 1) == ')' || isdigit(*(copy - 1)))))) || *copy == '*' || 
			*copy == '/' || *copy == '(' || *copy == ')' || *copy == '^'))	// Skip over all characters that aren't digits, 
																			//allowing for strtof to be used again.
			{
					copy++;
			}			
		}
	}
	
	return operands;
}

int parenthesesCheck(char noSpaces[], int stringLen) 
{
	int counter1 = 0;
	int counter2 = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (noSpaces[i] == '(')
		{
			counter1++;
		}
		else if (noSpaces[i] == ')')
		{
			counter2++;
		}
	}
	
	return counter1 == counter2;
}

int additionCheck(char noSpaces[], int stringLen) 
{
	
	int check = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (i != stringLen - 1 && noSpaces[i] == '+' && ((i != 0 && isdigit(noSpaces[i + 1]) && 
		isdigit(noSpaces[i - 1])) || (i != 0 && noSpaces[i + 1] == '(' && isdigit(noSpaces[i - 1])) || 
		(i != 0 && isdigit(noSpaces[i + 1]) && noSpaces[i - 1] == '(') || (i != 0 && noSpaces[i + 1] == '(' && 
		noSpaces[i - 1] == ')') || (i != 0 && isdigit(noSpaces[i + 1]) && noSpaces[i - 1] == ')') ||
		(i == 0 && isdigit(noSpaces[i + 1]))))
		{
			check = 1;
		}
		else if (noSpaces[i] != '+')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return check;
}

int subtractionCheck(char noSpaces[], int stringLen) 
{
	int check = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (i != stringLen - 1 && noSpaces[i] == '-' && ((i != 0 && isdigit(noSpaces[i + 1]) && 
		isdigit(noSpaces[i - 1])) || (i != 0 && noSpaces[i + 1] == '(' && isdigit(noSpaces[i - 1])) || 
		(i != 0 && isdigit(noSpaces[i + 1]) && noSpaces[i - 1] == '(') || (i != 0 && 
		noSpaces[i + 1] == '(' && noSpaces[i - 1] == ')') || (i != 0 && isdigit(noSpaces[i + 1]) && 
		noSpaces[i - 1] == ')') || (i == 0 && isdigit(noSpaces[i + 1]))))
		{
			check = 1;
		}
		else if (noSpaces[i] != '-')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return check;
}

int multiplicationCheck(char noSpaces[], int stringLen) 
{
	int check = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (i != stringLen - 1 && i != 0 && noSpaces[i] == '*' && ((isdigit(noSpaces[i + 1]) && isdigit(noSpaces[i - 1])) || 
		(noSpaces[i + 1] == '(' && isdigit(noSpaces[i - 1])) || (noSpaces[i + 1] == '(' && noSpaces[i - 1] == ')') || 
		(isdigit(noSpaces[i + 1]) && noSpaces[i - 1] == ')')))
		{
			check = 1;
		}
		else if (noSpaces[i] != '*')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return check;
}

int divisionCheck(char noSpaces[], int stringLen) 
{
	int check = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (i != stringLen - 1 && i != 0 && noSpaces[i] == '/' && ((isdigit(noSpaces[i + 1]) && isdigit(noSpaces[i - 1])) || 
		(noSpaces[i + 1] == '(' && isdigit(noSpaces[i - 1])) || (noSpaces[i + 1] == '(' && noSpaces[i - 1] == ')') || 
		(isdigit(noSpaces[i + 1]) && noSpaces[i - 1] == ')')))
		{
			check = 1;
		}
		else if (noSpaces[i] != '/')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return check;
}

int exponentCheck(char noSpaces[], int stringLen) 
{
	int check = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (i != stringLen - 1 && i != 0 && noSpaces[i] == '^' && ((isdigit(noSpaces[i + 1]) && isdigit(noSpaces[i - 1])) || 
		(noSpaces[i + 1] == '(' && isdigit(noSpaces[i - 1])) || (noSpaces[i + 1] == '(' && noSpaces[i - 1] == ')') || 
		(isdigit(noSpaces[i + 1]) && noSpaces[i - 1] == ')')))
		{
			check = 1;
		}
		else if (noSpaces[i] != '^')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return check;
}

int decimalCheck(char noSpaces[], int stringLen) 
{

	int check = 0;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (i != stringLen - 1 && i != 0 && noSpaces[i] == '.' && 
		isdigit(noSpaces[i - 1]) && isdigit(noSpaces[i + 1]))
		{
			check = 1;
		}
		else if (noSpaces[i] != '.')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	return check;
}


int bracketCheck(char noSpaces[], int stringLen) 
{
	char operators[] = "+-*/^";
	int check = 1;
	
	for (int i = 0; i < stringLen; i++)
	{
		if (noSpaces[i] == '(' && i != stringLen - 1 && ((i != 0 && ((strchr(operators, noSpaces[i - 1]) != NULL || 
		noSpaces[i - 1] == '(') && (isdigit(noSpaces[i + 1]) || noSpaces[i + 1] == '+' || noSpaces[i + 1] == '-' || 
		noSpaces[i + 1] == '('))) || (i == 0 && (isdigit(noSpaces[i + 1]) ||noSpaces[i + 1] == '+' || 
		noSpaces[i + 1] == '-' || noSpaces[i + 1] == '('))))
		{
			check = 1;
		}
		else if (noSpaces[i] == ')' && i != 0 && ((i != stringLen && ((strchr(operators, noSpaces[i + 1]) != NULL || 
		noSpaces[i + 1] == ')') && (isdigit(noSpaces[i - 1]) || noSpaces[i - 1] == ')'))) || (i == stringLen - 1 && 
		(isdigit(noSpaces[i - 1]) || noSpaces[i - 1] == ')'))))
		{
			check = 1;
		}
		else if (noSpaces[i] != '(' && noSpaces[i] != ')')
		{
			check = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return check;
}

int mathCheck(char noSpaces[], int stringLen)
{
	for (int i = 0; i < stringLen; i++)
	{
		if (noSpaces[i] == '+' || noSpaces[i] == '-' || noSpaces[i] == '*' ||
		noSpaces[i] == '/' || noSpaces[i] == '^' || noSpaces[i] == '.' ||
		noSpaces[i] == '(' || noSpaces[i] == ')' || isdigit(noSpaces[i]))
		{
			
		}
		else
		{
			return 0;
		}
	}
	
	return 1;
}

int userCheck(char noSpaces[])
{
    int length = strlen(noSpaces);
    
    return parenthesesCheck(noSpaces, length) && additionCheck(noSpaces, length) && 
	subtractionCheck(noSpaces, length) &&multiplicationCheck(noSpaces, length) && 
	divisionCheck(noSpaces, length) && exponentCheck(noSpaces, length) && decimalCheck(noSpaces, length) && 
	bracketCheck(noSpaces, length) && mathCheck(noSpaces, length);
}


char *noParentheses(char operators[]) 
{
	int length = strlen(operators);
	
	char *onlyOperators = NULL;
	onlyOperators = (char *)calloc(length + 1, sizeof(char));
	
	int j = 0;	// This incrementer variable is used to ensure onlyOperators has operators beginning at the first index
	
	if (onlyOperators != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			if (operators[i] != '(' && operators[i] != ')')
			{
				onlyOperators[j] = operators[i];
				j++;
			}
		}
		
		onlyOperators[j] = '\0';
	}
	
	return onlyOperators;
}

float calculations(char operator, float a, float b) 
{
	if (operator == '+')
	{
		return a + b;
	}
	if (operator == '-')
	{
		return a - (b);
	}
	if (operator == '*')
	{
		return a * b;
	}
	if (operator == '/')
	{
		if (b == 0)
		{
			printf("You cannot divide by zero. Please enter a new expression.\n"); 
		}
		else
		{
			return a / b;
		}
	}
	if (operator == '^')
	{
		return pow(a, b);
	}
}

float *newOperandArray(float operands[], int index, float result) // All correct
{
	float *newOperands = NULL;
	newOperands = calloc(numOperands - 1, sizeof(float));
	
	int j = 0;
	
	for (int i = 0; i < numOperands; i++)
	{
		if (j == index)
		{
			newOperands[j] = result;
			j++;
		}
		else if (i != index && i != index + 1)
		{
			newOperands[j] = operands[i];
			j++;
		}
	}
	
	numOperands--;
	
	return newOperands;
}

char *newOperatorArray(char onlyOperators[], int index) 
{
	int length = strlen(onlyOperators);
	
	char *newOperators = NULL;
	newOperators = calloc(length - 1, sizeof(char));
	
	int j = 0;
	if (newOperators != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			if (i != index)
			{
				newOperators[j] = onlyOperators[i];
				j++;
			}
		}
		
		newOperators[j] = '\0';
	}
	
	return newOperators;
}

float evaluation(char noSpaces[]) 
{
	char *temp = NULL;
	temp = noSpaces;
	float result;
	
	char *operators = NULL;
	operators = operatorsArray(temp);
	
	char *onlyOperators = NULL;
	onlyOperators = noParentheses(operators);
	
	int length = strlen(onlyOperators);
	
	float *operands = NULL;
	operands = operandsArray(noSpaces);
	
	for (int i = 0; i < length; i++)
	{
		if (onlyOperators[i] == '^')
		{
			result = calculations('^', operands[i], operands[i + 1]);
			operands = newOperandArray(operands, i, result);
			onlyOperators = newOperatorArray(onlyOperators, i);
			i--;
		}
	}
	
	for (int i = 0; i < length; i++)
	{
		if (onlyOperators[i] == '/' || onlyOperators[i] == '*')
		{
			result = calculations(onlyOperators[i], operands[i], operands[i + 1]);
			operands = newOperandArray(operands, i, result);
			onlyOperators = newOperatorArray(onlyOperators, i);
			i--;
		}
	}
	
	for (int i = 0; i < length; i++)
	{
		if (onlyOperators[i] == '-' || onlyOperators[i] == '+')
		{
			result = calculations(onlyOperators[i], operands[i], operands[i + 1]);
			operands = newOperandArray(operands, i, result);
			onlyOperators = newOperatorArray(onlyOperators, i);
			i--;
		}
	}
	return operands[0];
}

float orderOfOperations(char noSpaces[])
{
	int index1;
	int index2;
	
	char *temp = NULL;
	temp = noSpaces;
	
	while (strchr(temp, '(') != NULL)
	{
		int length = strlen(temp);
		
		for (int i = 0; i < length; i++)
		{
			if (temp[i] == ')')
			{
				index1 = i;
				break;
				
			}
		}
			
		for (int j = index1; j > -1; j--)
		{
			if (temp[j] == '(')
			{
				index2 = j;
				break;
			}
		}
			
		char *substring = NULL;
		substring = (char *)calloc(index1 - index2, sizeof(char)); // Correctly accounts for '\0' as well
			
		if (substring != NULL)
		{
			strncpy(substring, &temp[index2 + 1], index1 - index2 - 1); // Copying index1 - index2 - 1 characters to substring,
			substring[index1 - index2 - 1] = '\0';						// essentially all characters from inside the brackets
			
			if (index2 == 0)
			{
				return evaluation(temp);
			}
			else
			{
				float result = evaluation(substring);
				char *beforeBrackets = NULL;
				beforeBrackets = (char *)calloc(index2 + 1, sizeof(char));
				char *afterBrackets = NULL;
				afterBrackets = (char *)calloc(length - index1, sizeof(char));
					
				if (beforeBrackets != NULL && afterBrackets != NULL)
				{
					strncpy(beforeBrackets, temp, index2);
					beforeBrackets[index2] = '\0';
					strncpy(afterBrackets, &temp[index1 + 1], length - index1 - 1);
					afterBrackets[length - index1 - 1] = '\0';
					
						
					if (result < 0)
					{
						sprintf(temp, "%s%.2f%s%", beforeBrackets, result, afterBrackets);
					}
					else
					{
						sprintf(temp, "%s%.2f%s", beforeBrackets, result, afterBrackets);
					}
						
					free(beforeBrackets);
					free(afterBrackets);
				}
			}
				
			free(substring);
		}
	}
	
	return evaluation(temp);
}

int main()
{
	char calculation[MAX_ARR_SIZE]; // User Input
	int choice = -1;
	
	while (choice != 0)
	{
		printf("\n--- Calculator Menu ---\n");
		printf("1. Enter a mathematical expression.\n");
		printf("0. Exit the program.\n");
		
		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid. Please enter a valid number\n.");
			getchar();
			continue;
		}
		
		getchar();
		
		if (choice == 1)
		{			
			printf("Please enter your mathematical expression.\n");
	
			fgets(calculation, MAX_ARR_SIZE, stdin);
			
			char *withoutSpaces = noSpaces(calculation);
			
			if (userCheck(withoutSpaces))
			{
				float answer = orderOfOperations(withoutSpaces);
				printf("%.2f\n", answer);
				free(withoutSpaces);
			}
			else
			{
				printf("Sorry, you have not entered a complete/correct mathematical expression. Please try again.\n");
				free(withoutSpaces);
			}
		}
		else if (choice == 0)
		{
			printf("Exiting the program.\n");
		}
		else  
		{
			printf("Invalid option. Please choose either 1 or 0 to continue or exit the program.\n");
		}
		
	}
}