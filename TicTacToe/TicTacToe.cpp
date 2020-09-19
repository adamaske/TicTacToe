
#include <iostream>
#include "Slot.h"
#include "TicTacToe.h"
#include <string>
#include <vector>

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
int aiWins = 0;

bool ai = false;

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

    return 0;
};

void Setup()
{
    system("cls");
    //Set all the slots to empty
    for (int i = 0; i < amountOfSlots; i++)
    {
        slots[i].Initalize();
    }

    player1Turn = true;
    //Ask for 2 player or AI
    
    bool askForAI = true;
    do {
        int aiOr2Player;
        std::cout << "2-PLayer or play versus AI?:" << std::endl << "1. 2-Player" << std::endl << "2. AI" << std::endl;
        std::cin >> aiOr2Player;
        switch (aiOr2Player) {
        case 1:
            ai = false;
            askForAI = false;
            break;
        case 2:
            ai = true;
            askForAI = false;
            break;
        default:
            system("cls");
            std::cout << "That's not an option!" << std::endl;
            askForAI = true;
            break;
        }
    } while (askForAI);
    //Clear it to remvoe the ai question 
    system("cls");
    //Draws map;
    DrawMap();

    stage = inputStage;
}

void Input() {
    //Check if youre playing versus AI, then check if the its the Ai turn, 
    //then pass the AIMove function as the newInput which is used in execute
    if (ai && !player1Turn)
    {
        //New input is set to what the ai function determines
        newInput = AIMove();
        //Set the wished slot to the new input
        slots[newInput].GetInput(PlayerState());
        //Go to exectute stage
        stage = executeStage;
        //Using return so it dosent trigger the do function under
        return;
    }
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
        //Use new input minus 1 becuse the player sees number as one more than they are in the array
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
        //Restart if there is no more empty spaces
        if (!MoreEmptySpaces()) {
            
            stage = setup;

            return;
        }

        //Set next players turn and return to input stage
        player1Turn = !player1Turn;
        stage = inputStage;
    }
}

int AIMove() 
{
    //Only give vaild returns;
    //Check for the middle slot, if its empty, then take it
    if (slots[4].myState == Slot::SlotState::empty) {
        return 4;
    }

    //Temperory, just take the first avalibe slot
    for (int i = 0; i < 9; i++) {
        if (slots[i].myState == Slot::SlotState::empty) {
            std::cout << i;
            return i;
        }
    }
    return 1;
}
bool MoreEmptySpaces() {
    //If there is any spaces which are empty, return true
    for (int i = 0; i < 8; i++)
    {
        if (slots[i].myState == Slot::SlotState::empty) {
            
            return true;
        }
    }

    return false;
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
                default:
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


