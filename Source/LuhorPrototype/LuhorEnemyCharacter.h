// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuhorCharacter.h"
#include "LuhorEnemyCharacter.generated.h"

USTRUCT(BlueprintType)
struct FEnemyAttack
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinRange{ 100.f };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxRange{ 200.f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AssociatedAttackerTag{ NAME_None };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Cooldown{ 10.f };

	FTimerHandle CooldownTimer{};

	bool IsAttackValid(const UWorld* World, const AActor* Enemy, const AActor* Target);
	void SetAttackOnCooldown(const UWorld* World);  
};


UCLASS()
class LUHORPROTOTYPE_API ALuhorEnemyCharacter : public ALuhorCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool HasValidAttack(AActor* Target);

	UFUNCTION(BlueprintCallable)
	void UseValidAttack(AActor* Target);

protected:
	TArray<FEnemyAttack> Attacks;
};
