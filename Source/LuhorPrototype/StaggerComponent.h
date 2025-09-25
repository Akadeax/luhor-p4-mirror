// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaggerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUHORPROTOTYPE_API UStaggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaggerComponent();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaggered);
	UPROPERTY(BlueprintAssignable) FOnStaggered OnStaggered;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnStaggered);
	UPROPERTY(BlueprintAssignable) FOnUnStaggered OnUnStaggered;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BLueprintCallable)
	virtual void Stagger(float Amount);

	UFUNCTION(BLueprintCallable)
	float GetMaxStagger() const { return MaxStagger; }

	UFUNCTION(BLueprintCallable)
	float GetCurrentStagger() const { return CurrentStagger; }

	UFUNCTION(BLueprintCallable)
	bool GetStaggered() const {return IsStaggered;}
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxStagger{ 100.f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StaggerFastClearSpeed{ 20.f };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StaggerSlowClearSpeed{ 5.f };

	bool IsStaggered{ false };
	float CurrentStagger{ 0.f };
};
