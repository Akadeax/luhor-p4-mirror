// Fill out your copyright notice in the Description page of Project Settings.

#include "LuhorImporterWidget.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "LuhorPrototype/Corruptible/Corruptible.h"

FString ULuhorImporterWidget::CreateBlueprint(FString PackagePath, FString CleanMeshPackagePath, FString TaintedMeshPackagePath, FString CorruptedMeshPackagePath)
{
    const FString assetName{ "BP_" + FPackageName::GetLongPackageAssetName(PackagePath) };

    UPackage* package{ CreatePackage(*PackagePath) };
    if (!package)
    {
        return "Failed to create package";
    }
    if (FindObject<UBlueprint>(package, *assetName))
    {
        return "Package already exists!";
    }

    package->FullyLoad();
    UBlueprint* bp{ FKismetEditorUtilities::CreateBlueprint(ACorruptible::StaticClass(), package, FName(assetName), BPTYPE_Normal) };

    // TODO: Blueprint not being created, WTF (being created not displayed?)
    FAssetRegistryModule::AssetCreated(bp);
    // ReSharper disable once CppExpressionWithoutSideEffects
    bp->MarkPackageDirty();


    // Load static meshes
    UStaticMesh* cleanMesh{ FindObject<UStaticMesh>(nullptr, *(CleanMeshPackagePath)) };
    checkf(cleanMesh, TEXT("Clean mesh not found at package path somehow?"));
    UStaticMesh* taintedMesh{ FindObject<UStaticMesh>(nullptr, *(TaintedMeshPackagePath)) };
    checkf(cleanMesh, TEXT("Tainted mesh not found at package path somehow?"));
    UStaticMesh* corruptedMesh{ FindObject<UStaticMesh>(nullptr, *(CorruptedMeshPackagePath)) };
    checkf(cleanMesh, TEXT("Corrupted mesh not found at package path somehow?"));
    
    
    USimpleConstructionScript* scs{ bp->SimpleConstructionScript };
    checkf(scs, TEXT("No SCS found on new blueprint somehow."));



    
    USCS_Node* smNodeClean{ scs->CreateNode(UStaticMeshComponent::StaticClass(), "CleanMesh") };
    UStaticMeshComponent* smClean{ smNodeClean->ComponentTemplate };
    smClean->SetStaticMesh(cleanMesh);
    scs->AddNode(smNodeClean);


    USCS_Node* smNodeTainted{ scs->CreateNode(UStaticMeshComponent::StaticClass(), "TaintedMesh") };
    UStaticMeshComponent* smTainted{ smNodeTainted->ComponentTemplate };
    smTainted->SetStaticMesh(taintedMesh);
    scs->AddNode(smNodeTainted);

    
    FBlueprintEditorUtils::MarkBlueprintAsModified(bp);

    return "";
}
