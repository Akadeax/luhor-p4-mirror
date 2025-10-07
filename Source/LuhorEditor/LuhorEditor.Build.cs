using UnrealBuildTool;

public class LuhorEditor : ModuleRules
{
    public LuhorEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "ToolMenus",
                "Blutility",
                "DeveloperSettings",
                "UMG",
                "UMGEditor",
                "Slate",
                "SlateCore",
                "PythonScriptPlugin",
                "LuhorPrototype"
            }
        );
    }
}