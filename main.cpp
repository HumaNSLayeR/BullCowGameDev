/*This is the console executabe, that makes use of BullCow Class.
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class.

*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using int32 = int;
using FText = std::string;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
void SetWordLength();

bool AskToPlayAgain();
FText GetValidGuess();


FBullCowGame BCGame; // instatiate a new game, which we re-use across plays 


//the entry point for our game
int32 main()
{
	bool bPlayAgain = false;
	do{
		std::cout << std::endl;
		PrintIntro();

		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exits the game
}

//plays a single game to completion
void PlayGame()
{
//instantiate a new game
	BCGame.Reset();
	SetWordLength();
	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'am thinking of?\n";
	std::cout << std::endl;

	std::cout << "Max Tries " << MaxTries << std::endl;
	//loop asking for guesses while the game
	// is NOT an there are still tries remeaning
	while (!BCGame.IsGameWon() && BCGame.GetMyCurrentTry() <= MaxTries)		
	{
		FText Guess = GetValidGuess(); 

		
		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

bool AskToPlayAgain() // asks player to input an answer
{
	std::cout << "Do you want to play again with the same hidden word? y/n ";
	FText Response = "";
	std::getline(std::cin, Response);
	return(Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{ 	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player 
		int32 GetCurrentTry = BCGame.GetMyCurrentTry();
		std::cout << "Try " << GetCurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght: //Wrong length error message
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram: //Not isogram error message
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase: // not lowercase error message
			std::cout << "Please enter all letters lowercase.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}

void PrintGameSummary() {


	if (BCGame.IsGameWon() == true)
	{
		std::cout << " YOU WIN! \n\n";
	}
	else if(BCGame.IsGameWon() == false)
	{
		std::cout << "YOU LOSE! \n\n";
	}
	return;
}
// asks user to set the isogram's length
void SetWordLength() { 
	FString WordLength = "";
	std::cout << "Please select the word Length between " << BCGame.GetMinLength() << " and " << BCGame.GetMaxLength() << ". ";
	std::cout << std::endl;
	std::getline(std::cin, WordLength);
	while (!BCGame.SetWordLength(std::atoi(WordLength.c_str()))) {
		std::cout << "Wrong length. Must be beetween " << BCGame.GetMinLength() << " and " << BCGame.GetMaxLength();
		std::cout << std::endl;
		std::getline(std::cin, WordLength);
	}
	return;
}