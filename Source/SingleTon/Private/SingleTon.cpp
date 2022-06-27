// Copyright 2020 Andrew Bindraw. All Rights Reserved.

#include "SingleTon.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HAL/FileManager.h"
#include "Runtime/ApplicationCore/Public/Windows/WindowsPlatformApplicationMisc.h"

#define LOCTEXT_NAMESPACE "FSingleTonModule"

void FSingleTonModule::StartupModule()
{
#if !UE_EDITOR
  // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
  UE_LOG(LogTemp, Log, TEXT("CheckAnotherAppInstance enter"));

  auto CmdLine = UKismetSystemLibrary::GetCommandLine();
  UE_LOG(LogTemp, Log, TEXT("%s"), *CmdLine);

  FString ProjectIDParam = "UE5";
  if (true == FParse::Value(FCommandLine::Get(), TEXT("ProjectID="), ProjectIDParam))
  {
    UE_LOG(LogTemp, Log, TEXT("ProjectID= %s"), *ProjectIDParam);
  }

  // Only one instance of the game can be initialized!
  const FString LockFilePath = FPlatformProcess::UserTempDir() + ProjectIDParam;

  UE_LOG(LogTemp, Log, TEXT("LockFilePath= %s"), *LockFilePath);

  if (!IFileManager::Get().CreateFileWriter(*LockFilePath, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("CheckAnotherAppInstance RequestExit"));
    FPlatformApplicationMisc::RequestMinimize();
    FPlatformMisc::RequestExit(0);
  }
#endif
}

void FSingleTonModule::ShutdownModule()
{
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSingleTonModule, SingleTon)