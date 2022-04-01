//Code by Sebastian Scaini
//61 Chars max per line of dialogue.

#include <Arduboy2.h>

#include "Images.h"

Arduboy2 arduboy;
BeepPin1 beep;

enum GameState {
  credits,
  selection,
  game
};

GameState currentState = credits;

enum Emotion {
  happy,
  neutral,
  sad
};

Emotion currentEmotion = happy;

int girl = 0;

bool controlsDisplaying = true;
bool creditsDisplaying = true;

int score = 0;
bool aCorrect = false;

enum GameplayState {
  speaking,
  choice
};

GameplayState currentGameplayState = speaking;

//String dialogue[] = {"Hi there!", "This super speed dating sure is an interesting concept!", "So...", "I've got this list of questions here", "that I'm supposed to ask.", "It says here to answer them truthfully.", "Then we'll see if we're compatible!", "Are you ready to get started?", "choice", "Hooray! Let's get started!", "That's too bad but we have to start now.", "Question 1:", "If you suddenly won the lottery, what would you spend the money on?", "choice", "That's kinda weird since we just met...", "It's always good to look after yourself!", "Next up is Question 2:"};
String dialogue[] = {"Hi there!", "This is a small Visual Novel demo!", "Here, try this dialogue choice.", "choice", "Great! Thanks for participating!", "Too bad, you answered anyway!", "Hopefully it will become a full game one day...", "But for now this is all you'll get!", "Farewell!", "end"};
Emotion emotions[] = {happy, happy, neutral, happy, sad, neutral, sad, happy};
String choices[] = {"Sure!", "No!"};
bool correctChoices[] = {true, false};
int lineIndex = 0;
int choiceIndex = 0;
bool choiceMade = false;

void setup() {
  arduboy.begin();
  beep.begin();
  arduboy.setFrameRate(60);

  int selection = random(0, 100);

  if(selection > 50)
  {
    girl = 1;
  }
  else
  {
    girl = 0;  
  }
}

int emotionIndex = 0;

void loop() {
  
  if (!(arduboy.nextFrame()))
    return;

  beep.timer();
  arduboy.pollButtons();
  arduboy.clear();
  arduboy.setCursor(0, 10);
  arduboy.setTextWrap(true);
  arduboy.setTextSize(1);

  if(currentState == credits){
    arduboy.drawSlowXYBitmap(0, 0, creditsImage, 128, 64, WHITE);
    if(arduboy.justPressed(B_BUTTON) || arduboy.justPressed(A_BUTTON)){
       currentState = game;
    }
  }
  else{
  if(currentGameplayState == speaking){
    if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)){
      lineIndex++;
    }
  }
  else if(currentGameplayState == choice){
     if(arduboy.justPressed(A_BUTTON)){
      if(!choiceMade){
        lineIndex++;
        choiceMade = true;
             
        if(correctChoices[choiceIndex]){
          score++;
        }
      }
      else{
        lineIndex += 2;
        choiceMade = false;
        choiceIndex += 2;
        currentGameplayState = speaking;
      }
    }
    else if(arduboy.justPressed(B_BUTTON)){
      if(!choiceMade){
        lineIndex += 2;
        choiceMade = true;

        if(correctChoices[choiceIndex + 1]){
          score++;
          Serial.print(score);
        }
      }
      else{
        lineIndex++;
        choiceMade = false;
        choiceIndex += 2;
        currentGameplayState = speaking;
      }
    }
  }
  
  currentEmotion = emotions[lineIndex];
  
  if(dialogue[lineIndex] == "choice"){
    currentGameplayState = choice;
    arduboy.println("(A) " + choices[choiceIndex]);
    arduboy.println("(B) " + choices[choiceIndex + 1]);
  }
  else if(dialogue[lineIndex] == "end")
  {
    arduboy.exitToBootloader();
  }
  else {
    AdvancedPrint(dialogue[lineIndex]);
  }
  
  DrawEmotion();
  }
  arduboy.display();
}

void AdvancedPrint(String text){
  String prepText;
  
  for(int i = 0; i < text.length(); i++){
    prepText += text[i];
    if(i % 9 == 0 && i != 0){
      arduboy.println(prepText);
      prepText = "";
    }
  }

  arduboy.println(prepText);
}

void DrawEmotion(){
  if(girl == 0){
    switch(currentEmotion){
      case happy:
        arduboy.drawSlowXYBitmap(50, 0, girlHappy, 88, 64, WHITE);
        break;
        
      case sad:
        arduboy.drawSlowXYBitmap(50, 0, girlSad, 88, 64, WHITE);
        break;

      case neutral:
        arduboy.drawSlowXYBitmap(50, 0, girlNeutral, 88, 64, WHITE);
        break;
    }
  }
  else{
        switch(currentEmotion){
      case happy:
        arduboy.drawSlowXYBitmap(50, 0, boyHappy, 88, 64, WHITE);
        break;
        
      case sad:
        arduboy.drawSlowXYBitmap(50, 0, boySad, 88, 64, WHITE);
        break;

      case neutral:
        arduboy.drawSlowXYBitmap(50, 0, boyNeutral, 88, 64, WHITE);
        break;
    }
  }
}
