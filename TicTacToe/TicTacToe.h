#pragma once

void Setup();

void Input();

Slot::SlotState PlayerState();

void Execute();

bool MoreEmptySpaces();

bool Win();

bool CheckSlots(int x, int y, int z);


void DrawMap();
