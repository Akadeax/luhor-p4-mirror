// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "LuhorImporterWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUHOREDITOR_API ULuhorImporterWidget : public UEditorUtilityWidget
{
    GENERATED_BODY()

protected:
    UFUNCTION(Blueprintcallable)
    static FString CreateBlueprint(FString PackagePath, FString CleanMeshPackagePath, FString TaintedMeshPackagePath, FString CorruptedMeshPackagePath);
};
