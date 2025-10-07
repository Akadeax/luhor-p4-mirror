// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGameInstanceSubsystem.h"

#include "AmbrosiaHealthComponent.h"
#include "Kismet/GameplayStatics.h"

void ULevelGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    RoomData = LoadObject<URoomData>(nullptr, TEXT("/Game/Room/RoomData.RoomData"));
    check(RoomData);
    RoomsLeft = RoomData->Rooms;
}

void ULevelGameInstanceSubsystem::LoadRandomLevel()
{
    SavePlayerData();
    RoomsCompleted++;

    if (RoomsCompleted > RoomsLeft.Num())
    {
        RoomsCompleted = RoomsLeft.Num();
    }
    UGameplayStatics::OpenLevel(GetWorld(), RoomsLeft[RoomsCompleted - 1].Level.GetLongPackageFName());
}

void ULevelGameInstanceSubsystem::RefillRoomsLeft()
{
    RoomsLeft = RoomData->Rooms;
}

void ULevelGameInstanceSubsystem::SavePlayerData()
{
    const APlayerController* controller{ UGameplayStatics::GetPlayerController(this, 0) };
    const UAmbrosiaHealthComponent* healthComp{ controller->GetPawn()->FindComponentByClass<UAmbrosiaHealthComponent>() };
    const UUpgradesComponent* upgradesComp{ controller->GetPawn()->FindComponentByClass<UUpgradesComponent>() };
    PlayerSaveData = {
        healthComp->GetCurrentHealth(),
        healthComp->GetCurrentPoisonedAmbrosia(),
        upgradesComp->GetUpgrades(),
    };
}
