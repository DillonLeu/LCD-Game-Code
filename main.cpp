/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Joystick.h"
#include "N5110.h"
#include "Utils.h"
#include "InvasionEngine.h"
#include "Gameover.h"
//#include <tuple>

N5110 lcd( PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(PC_11);
InvasionEngine invasion;
Gameover gameover; 
int update = 2;  
int score = 0; 
void init();
void mainmenu();
void gameIntroduction();
void render();
void selection();
void initButton();
void gameOver();
void victory();

int main()
{
  init();
  initButton();
  mainmenu();
  gameIntroduction();
  render();
  int fps = 10;
  int lives = 3;
  thread_sleep_for(1000/fps); 
  while (lives > 0 && score < 20) 
  {
    UserInput input = {joystick.get_direction(),joystick.get_mag()};
    tie(lives, score) = invasion.update(input);
    // printf("lives = %d", lives);
    render();
    thread_sleep_for(1000/fps); 
  }
  printf("Exit while loop.\n");
  if (lives == 0){
    gameOver();
  }
  if (score == 20){
    victory();
  }
  
}

void init()
{
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    lcd.setBrightness(0.5);
    joystick.init();
    invasion.init();
}

// main menu page of the game
void mainmenu() 
{
    while(buttonA.read() == 1 ||update == 0 || update == 1){
    lcd.clear();
    lcd.printString("   INVASION   ", 0, 1);
    lcd.printString("     PLAY     ", 0, 3);
    lcd.printString("   TUTORIAL   ", 0, 4);
    lcd.printString("  BRIGHTNESS  ", 0, 5);
    selection();  
    lcd.refresh();
    }
}

void initButton()
{
    buttonA.mode(PullNone);
}

void selection()
{

    UserInput input = {joystick.get_direction(),joystick.get_mag()};
    if (input.d == N){
        // lcd.drawCircle(4, 27, 2, FILL_BLACK);
        update += 1;
        if (update >= 2)
        {
            update = 2;
        }
        thread_sleep_for(300); 
    }
    else if (input.d == S){
        // lcd.drawCircle(4, 35, 2, FILL_BLACK);
        update -= 1;
        if (update <= 0)
        {
            update = 0;
        }
        thread_sleep_for(300); 
    }
    else if (input.d == CENTRE){
            if (update == 2){
                lcd.drawCircle(4, 27, 2, FILL_BLACK);
            }
            else if (update == 1){
                lcd.drawCircle(4, 35, 2, FILL_BLACK);
            }
            else if (update == 0){
                lcd.drawCircle(4, 43, 2, FILL_BLACK);
            }
    }

    if (update == 0 && buttonA.read() == 0)
    {
        //int selDifficulty = 1;
        float width = 0.5;
        int brightness = 50;
        thread_sleep_for(300);
        while (buttonA.read() == 1) {
            char buffer[14];
            UserInput input = {joystick.get_direction(),joystick.get_mag()};
            lcd.clear();
            lcd.printString("  ADJUSTMENT:  ", 0, 1);
            lcd.drawRect(11,23, width * 60, 6, FILL_BLACK);
            sprintf(buffer, "     %d%%      ", brightness);
            lcd.printString(buffer, 0, 5);
            if (input.d == E){
                if (width >= 1)
                {
                    width = 1;
                }
                else 
                {
                    width += 0.01;
                }
            }
            else if (input.d == W){
                if (width <= 0)
                {
                    width = 0;
                }
                else 
                { 
                    width -= 0.01;
                }
            }
            brightness = (width/1) * 100;
            lcd.setBrightness(width);
        
            lcd.refresh();
            update = 0;
        }
        thread_sleep_for(300);

    }

    else if (update == 1 && buttonA.read() == 0)
    {
        int tutorialPage = 0;
        while(true)
        {
           
        if(buttonA.read() == 0 && tutorialPage == 0)
        {
        lcd.clear();
        lcd.printString("  WELCOME TO  ", 0, 1);
        lcd.printString("   TUTORIAL   ", 0, 2);
        lcd.printString(" PRESS OK TO  ", 0, 3);
        lcd.printString("SHOW NEXT PAGE", 0, 4);
        lcd.refresh();
        thread_sleep_for(300); 

        tutorialPage = 1;
        }

        if(buttonA.read() == 0  && tutorialPage == 1)
        {
        const int up [7][6] = {{0,0,1,1,0,0}
                              ,{0,1,1,1,1,0}
                              ,{1,0,1,1,0,1}
                              ,{0,0,1,1,0,0}
                              ,{0,0,1,1,0,0}
                              ,{0,0,1,1,0,0}
                              ,{0,0,1,1,0,0}}; 

        const int down [7][6] = {{0,0,1,1,0,0}
                                ,{0,0,1,1,0,0}
                                ,{0,0,1,1,0,0}
                                ,{0,0,1,1,0,0}
                                ,{1,0,1,1,0,1}
                                ,{0,1,1,1,1,0}
                                ,{0,0,1,1,0,0}}; 

        
        const int left [6][7] = {{0,0,1,0,0,0,0}
                                ,{0,1,0,0,0,0,0}
                                ,{1,1,1,1,1,1,1}
                                ,{1,1,1,1,1,1,1}
                                ,{0,1,0,0,0,0,0}
                                ,{0,0,1,0,0,0,0}};

        const int right [6][7] = {{0,0,0,0,1,0,0}
                                 ,{0,0,0,0,0,1,0}
                                 ,{1,1,1,1,1,1,1}
                                 ,{1,1,1,1,1,1,1}
                                 ,{0,0,0,0,0,1,0}
                                 ,{0,0,0,0,1,0,0}};

        const int button [8][8] = {{1,1,1,1,1,1,1,1}
                                  ,{1,0,0,0,0,0,0,1}
                                  ,{1,0,0,1,1,0,0,1}
                                  ,{1,0,1,1,1,1,0,1}
                                  ,{1,0,1,1,1,1,0,1}
                                  ,{1,0,0,1,1,0,0,1}
                                  ,{1,0,0,0,0,0,0,1}
                                  ,{1,1,1,1,1,1,1,1}};
        lcd.clear();    
        lcd.printString("JOYSTICK CTRL ", 0, 0);
        lcd.drawLine(0, 7, 83, 7, 2);
        lcd.printString("up-Push       ", 0, 1);
        lcd.drawSprite(47, 8, 7, 6, (int*) up);
        lcd.printString("down-Push     ", 0, 2);
        lcd.drawSprite(59, 17, 7, 6, (int*) down);
        lcd.printString("left-Push     ", 0, 3);
        lcd.drawSprite(59, 25, 6, 7, (int*) left);
        lcd.printString("right-Push    ", 0, 4);
        lcd.drawSprite(65, 32, 6, 7, (int*) right);
        lcd.printString("fire-Push     ", 0, 5);
        lcd.drawSprite(59, 40, 8, 8, (int*) button);
        lcd.refresh();
        thread_sleep_for(300); 
        tutorialPage = 2;
        }

        if(buttonA.read() == 0  && tutorialPage == 2)
        {
        lcd.clear();
        lcd.printString("    Mission   ", 0, 0);
        lcd.drawLine(0, 7, 83, 7, 2);
        lcd.printString("Destroy all   ", 0, 1);
        lcd.printString("BOMBERs. Avoid", 0, 2);
        lcd.printString("SUPERSONICs as", 0, 3);
        lcd.printString("they can kill ", 0, 4);
        lcd.printString("instantly!!   ", 0, 5);
        lcd.refresh();
        thread_sleep_for(300); 
        tutorialPage = 3;
        }
        if(buttonA.read() == 0  && tutorialPage == 3)
        {
            thread_sleep_for(300); 
            break;
        }
        }
    }
}

void gameIntroduction()
{
    
    int rollingScreen = 0;
    
    while (true)
    {
    lcd.clear();
    lcd.printString("Dear Top Gun: ", 0, 0 - rollingScreen);
    lcd.printString("You have been ", 0, 1 - rollingScreen);
    lcd.printString("assigned on a ", 0, 2 - rollingScreen);
    lcd.printString("treacherous   ", 0, 3 - rollingScreen);
    lcd.printString("mission to    ", 0, 4 - rollingScreen);
    lcd.printString("take control  ", 0, 5 - rollingScreen);
    lcd.printString("of the last   ", 0, 6 - rollingScreen);
    lcd.printString("remaining     ", 0, 7 - rollingScreen);
    lcd.printString("flight        ", 0, 8 - rollingScreen);
    lcd.printString("to save your  ", 0, 9 - rollingScreen);
    lcd.printString("CITY from     ", 0, 10 - rollingScreen);
    lcd.printString("major         ", 0, 11 - rollingScreen);
    lcd.printString("catastrophe.  ", 0, 12 - rollingScreen);
    lcd.printString("BEST OF LUCK  ", 0, 13 - rollingScreen);
    lcd.refresh();
    thread_sleep_for(500); 
    rollingScreen += 1;
    if (rollingScreen == 15)
    {
        break;
    }
    }
}

void render()
{
    lcd.clear();
    invasion.draw(lcd);
    lcd.refresh();
}

void gameOver()
{
    int explosionEffect = 0;
    gameover.init();
    while (explosionEffect <= 14) 
    {
        gameover.updateEnemyJet();    
        gameover.updateNuclearBomb();  
        explosionEffect = gameover.draw(lcd, explosionEffect, score);
    }
}

void victory()
{
    const int victory [21][44] ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0}
                                ,{0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1,1,0,0,0,0,0,0,0}
                                ,{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0}
                                ,{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                                ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
   

    lcd.clear();
    lcd.printString(" MISSION PASS! ",0,0);
    lcd.printString(" MISSION PASS! ",0,1);
    lcd.drawSprite(18, 18, 21, 44, (int*) victory);
    lcd.printString(" MISSION PASS! ",0,5);
    lcd.refresh(); 
    thread_sleep_for(100);

}
