#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FLuhorEditorModule final : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void InitializeMenu();
    void SetupMenu();
    void PopulateSubMenu(UToolMenu* Menu);

    void CorruptionViewerEntryClicked();
    void CorruptibleImporterEntryClicked();
    void AssetImporterEntryClicked();

    void OpenEUW(class UEditorUtilityWidgetBlueprint* Blueprint);
};
