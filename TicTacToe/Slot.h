#pragma once
#include <iostream>
class Slot
{
	
public:
	//Enum for the different states the slot can be in
	enum SlotState { empty, x, o };
	//Variable for the state
	SlotState myState = empty;
	//Using a bool to get the input wich takes in a slotState and returns true if it is possible, false if it is locked
	bool GetInput(SlotState newState) 
	{
		if (myState == empty) 
		{
			myState = newState;
			return true;
		}
		else 
		{
			return false;
		}
		
	}
	//Initailze/reset the slot
	void Initalize() {
		//Set the state to empty
		myState = empty;
		//std::cout << "Slot initalized" << std::endl;
	}
	
};

