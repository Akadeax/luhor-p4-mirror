// Fill out your copyright notice in the Description page of Project Settings.

#include "LuhorEnemyCharacter.h"

bool FEnemyAttack::IsAttackValid(const UWorld* World, const AActor* Enemy, const AActor* Target)
{
	if (!CooldownTimer.IsValid())
	{
		return false;
	}

	if (World->GetTimerManager().IsTimerActive(CooldownTimer))
	{
		return false;
	}

	const bool staticHit{ World->LineTraceTestByChannel(Enemy->GetActorLocation(), Target->GetActorLocation(), ECC_WorldStatic) };
	const bool dynamicHit{ World->LineTraceTestByChannel(Enemy->GetActorLocation(), Target->GetActorLocation(), ECC_WorldDynamic) };

	if (staticHit || dynamicHit)
	{
		return false;
	}
	
	return true;
}


void FEnemyAttack::SetAttackOnCooldown(const UWorld* World)
{
	World->GetTimerManager().SetTimer(CooldownTimer, FTimerDelegate::CreateLambda([]{}), Cooldown, false);
}


bool ALuhorEnemyCharacter::HasValidAttack(AActor* Target)
{
	for (FEnemyAttack& attack : Attacks)
	{
		if (attack.IsAttackValid(GetWorld(), this, Target))
		{
			return true;
		}
	}

	return false;
}


void ALuhorEnemyCharacter::UseValidAttack(AActor* Target)
{
	// int validAttackIndices[Attacks.Num()];
	// int numValidAttacks{ 0 };
	//
	// for (int i{}; i < Attacks.Num(); ++i)
	// {
	// 	if (Attacks[i].IsAttackValid(GetWorld(), this, Target))
	// 	{
	// 		validAttackIndices[numValidAttacks++] = i;
	// 	}
	// }
	//
	// checkf(numValidAttacks != 0, TEXT("No valid attacks found, but tried to use an attack!"));
	//
	// int randValidAttack{ FMath::RandRange(0, numValidAttacks - 1) };
}
