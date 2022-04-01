#pragma once

// For String
#include <Arduino.h>

//String dialogue[] = {"Hi there!", "This super speed dating sure is an interesting concept!", "So...", "I've got this list of questions here", "that I'm supposed to ask.", "It says here to answer them truthfully.", "Then we'll see if we're compatible!", "Are you ready to get started?", "choice", "Hooray! Let's get started!", "That's too bad but we have to start now.", "Question 1:", "If you suddenly won the lottery, what would you spend the money on?", "choice", "That's kinda weird since we just met...", "It's always good to look after yourself!", "Next up is Question 2:"};

String dialogue[]
{
	// 0
	"Hi there!",

	// 1
	"This is a small Visual Novel demo!",

	// 2
	"Here, try this dialogue choice.",

	// 3
	"choice",

	// 4
	"Great! Thanks for participating!",

	// 5
	"Too bad, you answered anyway!",

	// 6
	"Hopefully it will become a full game one day...",

	// 7
	"But for now this is all you'll get!",

	// 8
	"Farewell!",

	// 9
	"end"
};

constexpr uint8_t choiceLine = 3;
constexpr uint8_t endLine = 9;

String choices[]
{
	"Sure!",
	"No!"
};