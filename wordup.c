#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomwords(FILE *inFile){
	inFile = fopen("word.txt","w");
	
	if (inFile == NULL) {
        printf("There was an error opening the file.\n");
    	}
    	
    	//lists of 5 letter words that could generate in word.txt
	const char *ranwords[] = {"anomy", "beins", "alert", "beach", "guard", "doing","guest", "zilch", "quark", "jinxed", "vexed", "kultz"};
	
	//variable for the amount of words there are to randomly pick one
	int wordcount = 12;
	
	//calculates for a random word in ranwords
	int random = rand() % wordcount;
	
	fprintf(inFile, "%s", ranwords[random]);
	
	
	//closes file
	fclose(inFile);
}



void compareletters(FILE  *inFile, char userguess[], int *correct){
	
	char word[6]; //store the correct word
	
	int found = 0; // check if letter is in the word
	
	int answer;
	
	//counts how many letters the user entered
	int count;
	
	fscanf(inFile, "%5s", word); //read the word from the file
	
	for(int i = 0; i < 5; i++){
		if(userguess[i] == word[i]){
		//right letter is in the correct spot
			printf("This letter is correct %c\n", userguess[i]);
			*correct += 1;
		} else{
		///check if letter is in the word but not in the right spot
		for(int j = 0; j < 5; j++){
		if(userguess[i] == word[j]){
				found = 1; // found in wrong spot
				answer = 0;
				break;
			}
			found = 0; //not found
		}
		
		if(found){
		printf("This letter %c is correct but in the wrong position\n",userguess[i]);
		} else{
		printf("Letter %c is not in the word\n", userguess[i]);
		}
	}
}
}

void reset_game(FILE **inFile, int *chances, int *dischance, int *correct) {
    *chances = 0;
    *correct = 0;
}


int main(){
	srand(time(NULL));
	
	FILE* inFile;
	
	int choice;
	//variable to store the user guess
	char userguess[6];
	
	//increases by 1 everytime the user guesses incorrectly
	int chances = 0;
	//default amount of chances they get
	int dischance = 5;
	
	//increases whenever the user guesses a letter
	int correct = 0;
	
	//the user enters 1 or 2 to end the game or replay
	int replay;
	
	//starts the function that generates a word in word.txt
	randomwords(inFile);
	
	printf("You Have 5 Attempts To Get The Correct Word\n");
	
	//repeats until the user guesses 5 times
	while(chances < 5 && correct != 5){
	printf("\nChances left %d \nEnter A 5 Letter Word: ", dischance);
	scanf("%5s", userguess);
	
	int count = 0;
	int valid = 1;
	
    while (userguess[count] != '\0') {
    //tests if the user enters a letter or puncuation mark
        if (userguess[count] < 'a' || userguess[count] > 'z') {
        	valid = 0;
        	break;
        }
        count++;
}
        //tests if the count is lower than 5 then ends the program if true
        if(count != 5){
        valid = 0;
        }
        
        if(!valid){
        	printf("Invalid word, you must have 5 lower case letters.\n");
        	continue;
        }
	//prints how many chances the user has left
	printf("count: %d\n", count);
	
	chances++;
	dischance--;
	
	//opens file for the compare function
	inFile = fopen("word.txt","r");
		
	if (inFile == NULL) {
	printf("There was an error opening the file.\n");
	return 1;
	}
	
	//opens function to compare the words the user writes
	compareletters(inFile, userguess, &correct);
		
		//if the user doesnt get all 5 letters correct it resets the count
		if(correct != 5){
			correct = 0;
		}
		
		//if the user does guess all of the letters it asks if the user wants to
		//play again or end the game
		if(chances == 5){
		printf("You couldnt guess the word\n");
		printf("(1 yes, 2 No) Would you like to try again?: ");
		scanf("%d", &replay);
			if(replay == 1){
			//resets the game
				chances = 0;
				correct = 0;
				dischance = 5;
			} else {
			//ends the game
				return 0;
			}
		}
	}
	
	//tests to see if the user guesses the word correctly
	if(correct == 5){
		printf("Congrats you guessed the word\n");
		return 0;
	} else {
		correct = 0;
	}
	
}
