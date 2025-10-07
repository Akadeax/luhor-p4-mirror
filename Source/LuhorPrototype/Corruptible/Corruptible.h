// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Corruptible.generated.h"

UENUM(BlueprintType)
enum class EActorCorruptionState : uint8
{
    clean,
    tainted,
    corrupted
};

UENUM(BlueprintType)
enum class ERoomCorruptionState : uint8
{
    clean,
    cleanTainted,
    tainted,
    taintedCorrupted,
    corrupted
};

USTRUCT(BlueprintType)
struct FCorruptibleState
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ActiveComponentsTag{ NAME_None };
};

UCLASS()
class LUHORPROTOTYPE_API ACorruptible : public AActor
{
    GENERATED_BODY()

public:
    // Expose to blueprints only on this type; not BlueprintCallable normally
    UFUNCTION(BlueprintCallable)
    void RerunConstruction() { RerunConstructionScripts(); }
    
protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    
    ERoomCorruptionState GetRoomCorruption();
    EActorCorruptionState GetActorCorruptionState();

    double GetDistanceFactorAlongRoom();

#if WITH_EDITOR
    void HideInactiveComponents(const FCorruptibleState& State);
#endif
    void DestroyInactiveComponents(const FCorruptibleState& State);

    UPROPERTY(EditAnywhere)
    TMap<EActorCorruptionState, FCorruptibleState> CorruptibleStates;

    UPROPERTY(EditInstanceOnly, meta = (ToolTip = "How far along the room does this prop have to be in transition rooms (neither fully clean nor tainted nor corrupted room, in-between) before it transitions"))
    float CustomFactorAlongRoom{ 0.5f };
};
