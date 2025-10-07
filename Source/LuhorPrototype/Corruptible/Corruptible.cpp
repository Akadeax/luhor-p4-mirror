// Fill out your copyright notice in the Description page of Project Settings.

#include "LuhorPrototype/Corruptible/Corruptible.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LuhorPrototype/Corruptible/CorruptibleEngineSubsystem.h"
#include "LuhorPrototype/Corruptible/PlayerEndRoomTrigger.h"

void ACorruptible::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    const EActorCorruptionState corruption{ GetActorCorruptionState() };
    if (!CorruptibleStates.Contains(corruption)) { return; }

    const FCorruptibleState& corruptibleState{ CorruptibleStates[corruption] };

    if (GetWorld() == nullptr) { return; }
    if (GetWorld()->IsGameWorld())
    {
        DestroyInactiveComponents(corruptibleState);
        return;
    }

#if WITH_EDITOR
    HideInactiveComponents(corruptibleState);
#endif
}

ERoomCorruptionState ACorruptible::GetRoomCorruption()
{
    return GEngine->GetEngineSubsystem<UCorruptibleEngineSubsystem>()->GetCurrentRoomCorruptionState();
}

EActorCorruptionState ACorruptible::GetActorCorruptionState()
{
    const ERoomCorruptionState roomState{ GetRoomCorruption() };
    EActorCorruptionState actorState{ EActorCorruptionState::clean };

    switch (roomState)
    {
        case ERoomCorruptionState::clean: actorState = EActorCorruptionState::clean; break;
        case ERoomCorruptionState::tainted: actorState = EActorCorruptionState::tainted; break;
        case ERoomCorruptionState::corrupted: actorState = EActorCorruptionState::corrupted; break;

        case ERoomCorruptionState::cleanTainted:
            {
                const double distFactor{ GetDistanceFactorAlongRoom() };
                if (distFactor < CustomFactorAlongRoom)
                {
                    actorState = EActorCorruptionState::clean;
                    break;
                }
                actorState = EActorCorruptionState::tainted;
                break;
            }

        case ERoomCorruptionState::taintedCorrupted:
            {
                const double distFactor{ GetDistanceFactorAlongRoom() };
                if (distFactor < CustomFactorAlongRoom)
                {
                    actorState = EActorCorruptionState::tainted;
                    break;
                }
                actorState = EActorCorruptionState::corrupted;
                break;
            }
    }

    return actorState;
}

double ACorruptible::GetDistanceFactorAlongRoom()
{
    const AActor* playerStart{ UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()) };
    const AActor* endRoomTrigger{ UGameplayStatics::GetActorOfClass(GetWorld(), APlayerEndRoomTrigger::StaticClass()) };

    if (!playerStart || !endRoomTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("Room has either no player start or no end room trigger, it shouldn't contain corruptible blueprints!"));
        return 0.f;
    }

    const FVector startToEnd{ endRoomTrigger->GetActorLocation() - playerStart->GetActorLocation() };
    const FVector startToCorruptible{ GetActorLocation() - playerStart->GetActorLocation() };

    // Project Corruptible onto |Start End| to get distance along it
    const double distance{ startToCorruptible.Dot(startToEnd) / startToEnd.Length() };
    const double normalizedDistance{ distance / startToEnd.Length() };

    return normalizedDistance;
}

#if WITH_EDITOR
void ACorruptible::HideInactiveComponents(const FCorruptibleState& State)
{
    for (UActorComponent* comp : GetComponents())
    {
        USceneComponent* sceneComp{ Cast<USceneComponent>(comp) };
        if (!sceneComp)
        {
            continue;
        }

        const bool visible{ comp->ComponentHasTag(State.ActiveComponentsTag) };
        sceneComp->SetVisibility(visible);
    }
}
#endif

void ACorruptible::DestroyInactiveComponents(const FCorruptibleState& State)
{
    for (UActorComponent* comp : GetComponents())
    {
        const bool destroy{ !comp->ComponentHasTag(State.ActiveComponentsTag) };
        if (destroy)
        {
            comp->DestroyComponent();
        }
    }
}
