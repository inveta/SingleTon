// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleActor.generated.h"

UCLASS()
class SINGLETON_API ASingleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
