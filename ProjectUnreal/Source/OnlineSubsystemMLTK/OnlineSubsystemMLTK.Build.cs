using System.Net;
using UnrealBuildTool;

public class OnlineSubsystemMLTK : ModuleRules
{
    public OnlineSubsystemMLTK(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "OnlineSubsystemUtils",
                "OnlineServicesInterface",
                "OnlineServicesCommon",
                "InputCore",
                "Http",
                "Json",
                "JsonUtilities"
                
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "OnlineSubsystem",
                "OnlineBase",
                "OnlineSubsystemNull", 
                "OnlineServicesInterface",
                "OnlineServicesCommonEngineUtils"
            }
        );
    }
}