/* File for definition of classes
The game logic (no wiev or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once

#include <string>
#include<map>

#define TMap std::map

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Word,
	Not_Lowercase
};

class FBullCowGame{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetMyCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	int32 GetMinLength() const;
	int32 GetMaxLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	bool SetWordLength(int32);

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);
	//Ignore below!
private:
	//see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool bGameIsWon;

	// Isograms for the game. Must be ordered
	TMap<int32, FString> Isograms{
		{3, FString("ado")},
		{4, FString("grow")},
		{5, FString("cargo")},
		{6, FString("planet")},
		{7, FString("girasol")},
		{8, FString("orgasmic")}
	};

};