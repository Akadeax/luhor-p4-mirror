#include "LuhorEditor.h"

#include "EditorUtilitySubsystem.h"
#include "LuhorEditorDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "FLuhorEditorModule"

void FLuhorEditorModule::StartupModule()
{
    InitializeMenu();
}

void FLuhorEditorModule::ShutdownModule()
{
}

void FLuhorEditorModule::InitializeMenu()
{
    UToolMenus::RegisterStartupCallback(FSimpleDelegate::CreateRaw(this, &FLuhorEditorModule::SetupMenu));
}

void FLuhorEditorModule::SetupMenu()
{
    const FToolMenuOwner owner(this);

    UToolMenu* menu{ UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu") };
    check(menu);

    UToolMenu* submenu{ menu->AddSubMenu(this,
                                         "luhor",
                                         "luhor",
                                         LOCTEXT("luhor_menu_label", "Luhor"),
                                         LOCTEXT("luhor_menu_tooltip", "Options related to Luhor's Memory")) };

    PopulateSubMenu(submenu);
}

void FLuhorEditorModule::PopulateSubMenu(UToolMenu* Menu)
{
    FToolMenuSection& section{ Menu->FindOrAddSection("tools", LOCTEXT("tools_menu_section_name", "Tools")) };

    section.AddMenuEntry("corruption_viewer",
                         LOCTEXT("corruption_viewer_label", "Corruption Viewer"),
                         LOCTEXT("corruption_viewer_tooltip", "Preview different corruption stages in the currently open level"),
                         FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Details"),
                         FExecuteAction::CreateRaw(this, &FLuhorEditorModule::CorruptionViewerEntryClicked));

    section.AddMenuEntry("corruptible_importer",
                         LOCTEXT("corruptible_importer_label", "Corruptible Importer"),
                         LOCTEXT("corruptible_importer_tooltip", "Import assets that have 3 stages of corruption"),
                         FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Convert"),
                         FExecuteAction::CreateRaw(this, &FLuhorEditorModule::CorruptibleImporterEntryClicked));

    section.AddMenuEntry("asset_importer",
                     LOCTEXT("asset_importer_label", "Asset Importer"),
                     LOCTEXT("asset_importer_tooltip", "Import assets that only have 1 stage"),
                     FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Convert"),
                     FExecuteAction::CreateRaw(this, &FLuhorEditorModule::AssetImporterEntryClicked));
}

void FLuhorEditorModule::CorruptionViewerEntryClicked()
{
    OpenEUW(GetDefault<ULuhorEditorDeveloperSettings>()->CorruptionViewerEUW.LoadSynchronous());
}

void FLuhorEditorModule::CorruptibleImporterEntryClicked()
{
    OpenEUW(GetDefault<ULuhorEditorDeveloperSettings>()->CorruptibleImporterEUW.LoadSynchronous());
}

void FLuhorEditorModule::AssetImporterEntryClicked()
{
    OpenEUW(GetDefault<ULuhorEditorDeveloperSettings>()->AssetImporterEUW.LoadSynchronous());
}

void FLuhorEditorModule::OpenEUW(UEditorUtilityWidgetBlueprint* Blueprint)
{
    checkf(Blueprint, TEXT("Corruption Viewer not assigned in project settings!"));
    GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>()->SpawnAndRegisterTab(Blueprint);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLuhorEditorModule, LuhorEditor)
