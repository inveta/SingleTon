// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleActor.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HAL/FileManager.h"
#include "Runtime/ApplicationCore/Public/Windows/WindowsPlatformApplicationMisc.h"

// Sets default values
ASingleActor::ASingleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
    m_fLock = nullptr;
}

// Called when the game starts or when spawned
void ASingleActor::BeginPlay()
{
	Super::BeginPlay();
	
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

    m_fLock = IFileManager::Get().CreateFileWriter(*LockFilePath, 0);
    if (!m_fLock)
    {
        UE_LOG(LogTemp, Log, TEXT("CheckAnotherAppInstance RequestExit"));
        FPlatformApplicationMisc::RequestMinimize();
        FPlatformMisc::RequestExit(0);
    }
#endif
}

void ASingleActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
#if !UE_EDITOR
    if (nullptr != m_fLock)
    {
        m_fLock->Close();
    }
#endif 
    Super::EndPlay(EndPlayReason);
}

