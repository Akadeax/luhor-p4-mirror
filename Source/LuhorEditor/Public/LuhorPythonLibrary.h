// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LuhorPythonLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LUHOREDITOR_API ULuhorPythonLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static FString RunPythonFile(FString FileName, TArray<FString> Args);
};
