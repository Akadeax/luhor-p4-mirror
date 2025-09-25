#include "StaggerComponent.h"

UStaggerComponent::UStaggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStaggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsStaggered)
	{
		CurrentStagger -= DeltaTime * StaggerFastClearSpeed;
		if (CurrentStagger <= 0.f)
		{
			CurrentStagger = 0.f;
			IsStaggered = false;
			OnUnStaggered.Broadcast();
		}
	} else if (CurrentStagger > 0)
	{
		CurrentStagger =  FMath::Max( CurrentStagger - DeltaTime * StaggerSlowClearSpeed,0);
	}
}

void UStaggerComponent::Stagger(float Amount)
{
	CurrentStagger += Amount;
	if (CurrentStagger >= MaxStagger)
	{
		if (!IsStaggered)
		{
			IsStaggered = true;
			OnStaggered.Broadcast();
		} else
		{
			CurrentStagger = MaxStagger;
		}
	}
	
}

void UStaggerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(true);
	
}
