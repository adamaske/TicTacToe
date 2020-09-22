#pragma once
#include "Slot.h"
#include "TicTacToe.h"
class TTTAI
{

	
public:
	Slot _slots[9];
	bool oWon;
	bool tie;
	int aiMove(Slot slots[]) {
		//copy all slots from slots to _slots, to not maky anyChancges to the actual board
		for (int i = 0; i < 9; i++)
		{
			_slots[i] = slots[i];
		}
		//Keep hold of the best found score
		int bestScore = -1000;
		int bestMove = -1;

		//Loop through every slot
		for (int i = 0; i < 9; i++)
		{
			//Is this slot open, then check if its good
			if (_slots[i].myState == Slot::SlotState::empty) 
			{
				//Since it is avalible, go there, then calculate the next 
				//posistions from therewith minimax, then clear it again to not mess with the next checks 
				_slots[i].myState = Slot::SlotState::o;
				//Calls the minimax algorithm for this spot after it is set to O, to find if if this is a good move or not
				//Send false to the minimax, bacuse the next turn is the players
				int score = minimax(false);
				_slots[i].myState = Slot::SlotState::empty;
				//If this is a better move than the last, set the bestScore to this, then return it at the end
				if (score > bestScore) {
					bestScore = score;
					//Sets this move as the current best move to return, so only moves that were better than the last
					//is set as the current best move;
					bestMove = i;
				}
			}
		}

		return bestMove;
	}


	int minimax(bool aiTurn) {
		int result = -10;
		//No win, no more empty spaces, then tie, value 0
		if (!Win() && !MoreEmptySpaces()) {
			result = 0;
			return result;
		}
		//X won, wich is not wanted, the AI is O
		if (Win() && !oWon) {
			result = -1;
			return result;
		}
		//Wanted result, O won, then value 1
		if (Win() && oWon) {
			result = 1;
			return result;
		}
		
		if (aiTurn) {
			//new best score
			int bestScore = -100;
			for (int i = 0; i < 9; i++)
			{
				//Does exactly the same as the AIMove function, just calling minnimax over and over until it reaches, win or tie
				//And switches the aiTurn bool so next time it cheks the others turn
				if (_slots[i].myState == Slot::SlotState::empty)
				{					
					_slots[i].myState = Slot::SlotState::o;					
					int score = minimax(false);
					_slots[i].myState = Slot::SlotState::empty;
					if (score > bestScore) {
						bestScore = score;
					}
				}
			}
			return bestScore;
		}
		else {
			int bestScore = 100;
			for (int i = 0; i < 9; i++)
			{
				if (_slots[i].myState == Slot::SlotState::empty)
				{					
					_slots[i].myState = Slot::SlotState::x;					
					int score = minimax(true);
					_slots[i].myState = Slot::SlotState::empty;					
					if (score < bestScore) {
						bestScore = score;
					}
				}
			}
			return bestScore;
		}
		
		
	}
	//Same functions as the tictactoe.cpp for winning, didnt bother writiing new ways of checking it for this, so its
	//copy pasted and just added a bool wich tells it if X or O won
	bool Win() {
		//manuel checking, if any of these are true, someone won the game
		if (CheckSlots(0, 1, 2) || CheckSlots(3, 4, 5) || CheckSlots(6, 7, 8) || CheckSlots(0, 4, 8) ||
			CheckSlots(2, 4, 6) || CheckSlots(0, 3, 6) ||
			CheckSlots(0, 3, 6) || CheckSlots(1, 4, 7) || CheckSlots(2, 5, 8)) {
			
			return true;
		}
		else {
			return false;
		}

	}
	bool MoreEmptySpaces() {
		//If there is any spaces which are empty, return true
		for (int i = 0; i < 9; i++)
		{
			if (_slots[i].myState == Slot::SlotState::empty) {

				return true;
			}
		}

		return false;
	}
	bool CheckSlots(int x, int y, int z)
	{
		//Gets the array place of each slot to check and sees if they are either all x or all o, if they are return true
		if (_slots[x].myState == Slot::SlotState::x && _slots[y].myState == Slot::SlotState::x && _slots[z].myState == Slot::SlotState::x)
		{
			oWon = false;
			return true;
		}
		else if (_slots[x].myState == Slot::SlotState::o && _slots[y].myState == Slot::SlotState::o && _slots[z].myState == Slot::SlotState::o)
		{
			oWon = true;
			return true;
		}
		else {
			return false;
		}
	}
};

