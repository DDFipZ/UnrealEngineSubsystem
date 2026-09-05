// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class OnlineSubsystemPluginLibrary : ModuleRules
{
	public OnlineSubsystemPluginLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PublicDefinitions.Add("FORCE_ANSI_ALLOCATOR=1");

		PublicSystemIncludePaths.Add("$(ModuleDir)/Public");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "datachannel.lib"));
			// Deploy the DLL to Binaries/Win64
			RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "datachannel.dll"));
			RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "libssl-3-x64.dll"));
			RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "libcrypto-3-x64.dll"));
			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("datachannel.dll");

			// Ensure that the DLL is staged along with the executable
			PublicSystemIncludePaths.Add("$(PluginDir)/Source/ThirdParty/OnlineSubsystemPluginLibrary/include");
		}
	}
}
