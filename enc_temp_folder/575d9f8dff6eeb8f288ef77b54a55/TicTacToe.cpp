
#include <iostream>
#include "Slot.h"
#include "TicTacToe.h"
#include <string>

bool playing;
int height = 3;
int width = 3;
//How many slots to make
const int amountOfSlots = 9;
//Array of the different slots
Slot slots[amountOfSlots];
//Variable to store the input just pressed, should maybe be a local var instead
int newInput = 0;
//Enum for the game stage
enum GameStage{ setup, inputStage, executeStage};
GameStage stage = GameStage::setup;

bool player1Turn = true;

int player1Wins = 0;
int player2Wins = 0;

int main()
{
    playing = true;
    player1Turn = true;
   
    while (playing) 
    {
        switch (stage) {
        case setup:
            Setup();
            break;
        case inputStage:
            Input();
            break;
        case executeStage:
            Execute();
            break;
        }
    }
};

void Setup()
{
    system("cls");
    //Set all the slots to empty
    for (int i = 0; i < amountOfSlots - 1; i++)
    {
        slots[i].Initalize();
    }
    DrawMap();
    stage = inputStage;

    
}

void Input() {
    //Put it in loop in case of wrong input etc
    do {
        //Ask for input
        std::cout << "What box do you want to place in" << std::endl;
        //Display if its player 1 or 2's turn
        if (player1Turn) {
            std::cout << "Player 1: ";
        }
        else {
            std::cout << "Player 2: ";
        }
        //Put the input in newInput
        std::cin >> newInput;
        
        //Check if newInput is valid, if it is valid, the slot GetInput function will return true, and set itself to the state
        if (slots[newInput - 1].GetInput(PlayerState())) 
        {
            //Got valid input so go to next phase
            stage = executeStage;
            
        }
        else {
            std::cout << "Not valid input" << std::endl;
            
        }
    } while (stage == inputStage);

}
//Variable to see what state it should give the slot depeing on who's turn it is
Slot::SlotState PlayerState() {
    if (player1Turn) {
        return Slot::SlotState::x;
    }
    else {
        return Slot::SlotState::o;
    }
};
void Execute() 
{
    //Clear previus
    system("cls");
    //Redraw map
    DrawMap();
    //Check for win, if win return to setup phase
    if (Win()) {
        //Add to scores
        if (player1Turn) {
            player1Wins++;
        }
        else {
            player2Wins++;
        }

        stage = setup;
    }
    else {
        //Set next players turn and return to input stage
        player1Turn = !player1Turn;
        stage = inputStage;
    }
    

}

bool Win() {
    //manuel checking, if any of these are true, someone won the game
    if (CheckSlots(0, 1, 2) || CheckSlots(3, 4, 5) || CheckSlots(6, 7, 8) || CheckSlots(0,4,8) || 
        CheckSlots(2,4,6) || CheckSlots(0,3,6) || 
        CheckSlots(0, 3, 6) || CheckSlots(1, 4, 7) || CheckSlots(2, 5, 8)) {
        return true;
    }
    else {
        return false;
    }
    
}

bool CheckSlots(int x, int y, int z) 
{
    //Gets the array place of each slot to check and sees if they are either all x or all o, if they are return true
    if (slots[x].myState == Slot::SlotState::x && slots[y].myState == Slot::SlotState::x && slots[z].myState == Slot::SlotState::x) 
    {
        return true;
    }
    else if (slots[x].myState == Slot::SlotState::o && slots[y].myState == Slot::SlotState::o && slots[z].myState == Slot::SlotState::o)
    {
        return true;
    }
    else {
        return false;
    }
}

void DrawMap()
{
    //Draw scores above map
    std::cout << "Player 1 score: " << player1Wins << " | Player 2 score: " << player2Wins << std::endl;

    //Keeps count of how many slots it has iterated trough, starts at 0 to get 1-9 instead of 0-8
    int drawnSlots = 0;
    //For each vertical line, draw the wished 
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //Find what char should be displayed to the slot
            char toDraw = '0';
            switch (slots[drawnSlots].myState) 
            {
                case Slot::SlotState::empty:
                    toDraw = '0' + drawnSlots +  1;
                    break;
                case Slot::SlotState::x:
                    toDraw = 'X';
                    break;
                case Slot::SlotState::o:
                    toDraw = 'O';
                    break;
                defult:
                    toDraw = '2';
                        break;
            }
            //Drawn some lines between each
            std::cout << "| " << toDraw << " | ";
            //Add to drawn slots do display correct number
            drawnSlots++;
        }
        std::cout << std::endl;
    }
}


