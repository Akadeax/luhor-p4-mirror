// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Engine/DeveloperSettings.h"
#include "LuhorEditorDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class LUHOREDITOR_API ULuhorEditorDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    ULuhorEditorDeveloperSettings();
    
    UPROPERTY(EditAnywhere, Config)
    TSoftObjectPtr<UEditorUtilityWidgetBlueprint> CorruptionViewerEUW;

    UPROPERTY(EditAnywhere, Config)
    TSoftObjectPtr<UEditorUtilityWidgetBlueprint> CorruptibleImporterEUW;
    
    UPROPERTY(EditAnywhere, Config)
    TSoftObjectPtr<UEditorUtilityWidgetBlueprint> AssetImporterEUW;
};
