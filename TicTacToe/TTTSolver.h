#pragma once

#include "Slot.h"
class TTTSolver
{
public:
	int Move(Slot slots[], Slot::SlotState team, int length) {
		//Do stuff to find out what move it should take

		//If middle is not taken, take middle
		if (slots[4].myState == Slot::SlotState::empty) {
			return 4;
		}
		return 1;
	}

};

