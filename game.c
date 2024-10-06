#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>

// Length of word. If you want to change it you also need to change the word list also
#define LETTERCOUNT 5
// How many chance the user can have
#define CHANCES 5

// Change color of font to red
#define REDC "\033[0;31m"
// Change color of font to green
#define GREENC "\033[0;32m"
// Change color of font to yello
#define YELLOWC "\033[0;33m"
// Change color of font to defualt
#define DEFAULTC "\033[0m"

//colors we can use
// Black \033[0;30m
// Red \033[0;31m
// Green \033[0;32m
// Yellow \033[0;33m
// Blue \033[0;34m
// Purple \033[0;35m
// Cyan \033[0;36m
// White \033[0;37m

// Files for list to store all words
FILE *fpAll,  *fpSol;

// To store file status
struct stat stats;

// The word
char gameWord[LETTERCOUNT+1];

// total words in solution list
long wordCount;

// print the guessed word with color to represent its progress and clues
void printGuess(char guess[LETTERCOUNT+1]);

// load game status
int loadGameSetup();

// To check whether the word is in the list
int isValidWord(char guess[LETTERCOUNT+1]);

// game startup
int game(){
    int gameId = loadGameSetup();

    printf("Guess the %d letter word\n", LETTERCOUNT);
    printf("%sRED%s color means the letter is not in the word\n",REDC, DEFAULTC);
    printf("%sYEllOW%s color means the letter is in the word but different position\n",YELLOWC, DEFAULTC);
    printf("%sGREEN%s color means the letter is in the word and in correct position\n",GREENC, DEFAULTC);

    printf("Game id: %d\n", gameId);
    int chance = 0;

    while( chance < CHANCES){
        printf("Guess  %d: ", chance+1);
        scanf("%s",guess);
        strupr(guess);
        if(strlen(guess) != LETTERCOUNT ){
            printf("Need to enter 5 letter word\n");
        }else if(!isValidWord(guess)){
            printf("Word in not in list\n");
        }else{
            printGuess(guess);
            if(strcmp(guess, gameWord)== 0){
                printf("%sYou WON!%s\nYou entered correct word\n", GREENC, DEFAULTC);
                break;
            }else{
                chance++;
            }
        }
    }
    if(chance == CHANCES){
        printf("%sYou lost!%s", REDC, DEFAULTC);
        printf("The word was %s%s%s",GREENC, gameWord,DEFAULTC );
    }
}

int main(){

    char guess[LETTERCOUNT+1];

    char solutionHard[] = "lists\\solution.txt";
    char solutionEasy[] = "lists\\solution-easy.txt";

    fpAll = fopen("lists\\all.txt", "r");
    fpSol = fopen("lists\\solution-easy.txt","r");
    if(fpAll == NULL || fpSol == NULL){
        printf("Error in reading file\n");
        return EXIT_FAILURE;
    }


    
    fclose(fpAll);
    fclose(fpSol);

    getch();
    return 0;
}

void printGuess(char guess[LETTERCOUNT+1]){
    
    char *found;
    printf("\t");
    for(int i=0;guess[i]!='\0';i++){
        found = strchr(gameWord, guess[i]);
        if(found == NULL){
            printf(REDC);
            
        }else if((found-gameWord) == i){
            printf(GREENC);
        }else{
            printf(YELLOWC);
        }
        printf("%c ",guess[i]);
        printf(DEFAULTC);
    }
    printf("\n");
}

int loadGameSetup(){

    printf("Loading....");
    char currentWord[LETTERCOUNT+1];

    while (fgets(currentWord, LETTERCOUNT+1, fpSol) != NULL) {
		if (strlen(currentWord) == LETTERCOUNT) {
			++wordCount;
		}
	}
    srand(time(NULL));
    long wordIndex = rand() % wordCount;

    fseek(fpSol, 7*(wordIndex-1), SEEK_SET);
    do
    {
        fgets(gameWord, LETTERCOUNT+1, fpSol);
    } while (strlen(gameWord) != LETTERCOUNT);
    system("cls");
    
    return wordIndex;
    
}

int isValidWord(char guess[LETTERCOUNT + 1]){

    char t_word[LETTERCOUNT+1];
    fseek(fpAll, 0, SEEK_SET);

    while (fgets(t_word, LETTERCOUNT+1, fpAll) != NULL) {
        if(strcmp(guess, t_word) == 0){
            return 1;
        }
    }
    
    return 0;
}
