// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class SQUAD : ModuleRules
{
	private string MySql_Directory {

		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../MySql/")); }
	}

	public SQUAD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","HeadMountedDisplay","UMG", "EnhancedInput", "Niagara", "NavigationSystem", "AIModule" , "GameplayTags" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { 
		
			Path.Combine(MySql_Directory,"include"),
            Path.Combine(MySql_Directory,"include/mysqlx"),
            Path.Combine(MySql_Directory,"include/mysqlx/common"),
            Path.Combine(MySql_Directory,"include/mysqlx/devapi")
        });

		PublicAdditionalLibraries.AddRange(new string[] {

			Path.Combine(MySql_Directory,"lib64/vs14/mysqlcppconnx.lib"),
            Path.Combine(MySql_Directory,"lib64/vs14/libcrypto.lib"),
            Path.Combine(MySql_Directory,"lib64/vs14/libssl.lib")

        });

		RuntimeDependencies.Add(

            "$(BinaryOutputDir)/mysqlcppconn-10-vs14.dll",
            Path.Combine(MySql_Directory, "lib64/mysqlcppconn-10-vs14.dll"));
        RuntimeDependencies.Add(

            "$(BinaryOutputDir)/mysqlcppconnx-2-vs14.dll",
            Path.Combine(MySql_Directory, "lib64/mysqlcppconnx-2-vs14.dll"));
        RuntimeDependencies.Add(

            "$(BinaryOutputDir)/libssl-3-x64.dll",
            Path.Combine(MySql_Directory, "lib64/libssl-3-x64.dll"));
        RuntimeDependencies.Add(

            "$(BinaryOutputDir)/libcrypto-3-x64.dll",
            Path.Combine(MySql_Directory, "lib64/libcrypto-3-x64.dll"));
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
