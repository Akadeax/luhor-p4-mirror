// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Corruptible.h"
#include "CorruptibleEngineSubsystem.generated.h"
/**
 * 
 */
UCLASS()
class LUHORPROTOTYPE_API UCorruptibleEngineSubsystem final : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    void ResetCurrentRoomCorruptionState() { CurrentRoomCorruptionState = ERoomCorruptionState::clean; }

    UFUNCTION(BlueprintCallable)
    void IncreaseCurrentRoomCorruptionState();

    UFUNCTION(BlueprintCallable)
    ERoomCorruptionState GetCurrentRoomCorruptionState() const { return CurrentRoomCorruptionState; }
    
private:
    UPROPERTY(EditAnywhere)
    ERoomCorruptionState CurrentRoomCorruptionState{ ERoomCorruptionState::clean };
};
