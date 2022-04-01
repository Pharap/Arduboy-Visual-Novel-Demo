#pragma once

// For PROGMEM
#include <avr/pgmspace.h>

// For asFlashString
#include "FlashStringHelper.h"

//String dialogue[] = {"Hi there!", "This super speed dating sure is an interesting concept!", "So...", "I've got this list of questions here", "that I'm supposed to ask.", "It says here to answer them truthfully.", "Then we'll see if we're compatible!", "Are you ready to get started?", "choice", "Hooray! Let's get started!", "That's too bad but we have to start now.", "Question 1:", "If you suddenly won the lottery, what would you spend the money on?", "choice", "That's kinda weird since we just met...", "It's always good to look after yourself!", "Next up is Question 2:"};

// The lines of dialogue are stored individually,
// in separate arrays in progmem.
constexpr char dialogue0[] PROGMEM = "Hi there!";
constexpr char dialogue1[] PROGMEM = "This is a small Visual Novel demo!";
constexpr char dialogue2[] PROGMEM = "Here, try this dialogue choice.";
constexpr char dialogue3[] PROGMEM = "choice";
constexpr char dialogue4[] PROGMEM = "Great! Thanks for participating!";
constexpr char dialogue5[] PROGMEM = "Too bad, you answered anyway!";
constexpr char dialogue6[] PROGMEM = "Hopefully it will become a full game one day...";
constexpr char dialogue7[] PROGMEM = "But for now this is all you'll get!";
constexpr char dialogue8[] PROGMEM = "Farewell!";
constexpr char dialogue9[] PROGMEM = "end";

// And then there's another array that contains pointers
// to all the individual lines of dialogue.
constexpr const char * dialogue[] PROGMEM
{
	dialogue0,
	dialogue1,
	dialogue2,
	dialogue3,
	dialogue4,
	dialogue5,
	dialogue6,
	dialogue7,
	dialogue8,
	dialogue9,
};

// This function fetches the lines of dialogue by index
inline const char * getDialogueLine(size_t lineIndex)
{
	return reinterpret_cast<const char *>(pgm_read_ptr(&dialogue[lineIndex]));
}

constexpr uint8_t choiceLine = 3;
constexpr uint8_t endLine = 9;

// As before, individual lines are stored into fixed size arrays in progmem.
constexpr char choice0[] PROGMEM = "Sure!";
constexpr char choice1[] PROGMEM = "No!";

// And then pointed to from an array.
constexpr const char * choices[] PROGMEM
{
	choice0,
	choice1
};

// This function fetches the lines of dialogue by index
inline FlashStringHelper getChoiceForPrinting(size_t choiceIndex)
{
	return readFlashStringPointer(&choices[choiceIndex]);
}