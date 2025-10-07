// Fill out your copyright notice in the Description page of Project Settings.


#include "LuhorPrototype/Corruptible/CorruptibleEngineSubsystem.h"

void UCorruptibleEngineSubsystem::IncreaseCurrentRoomCorruptionState()
{
    const int idx{ static_cast<int>(CurrentRoomCorruptionState) };
    if (idx == static_cast<int>(ERoomCorruptionState::corrupted)) { return; }

    CurrentRoomCorruptionState = static_cast<ERoomCorruptionState>(idx + 1);
}
