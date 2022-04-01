//Code by Sebastian Scaini
//61 Chars max per line of dialogue.

#include <Arduboy2.h>

#include "Images.h"
#include "Strings.h"

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

Emotion emotions[] = {happy, happy, neutral, happy, sad, neutral, sad, happy};
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
  
  if(lineIndex == choiceLine){
    currentGameplayState = choice;
    arduboy.print(F("(A) "));
    arduboy.println(choices[choiceIndex + 0]);
    arduboy.print(F("(B) "));
    arduboy.println(choices[choiceIndex + 1]);
  }
  else if(lineIndex == endLine)
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

void AdvancedPrint(const String & text){
  for(size_t i = 0; i < text.length(); i++){
    arduboy.print(text[i]);

    if(((i % 9) == 0) && (i != 0)){
      arduboy.println();
    }
  }

  arduboy.println();
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
