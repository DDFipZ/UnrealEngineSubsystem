// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MLTKUSessionWidget.h"
#include "GameFramework/Pawn.h"
#include "MLTKASessionPawn.generated.h"

UCLASS()
class PROJECTUNREAL_API AMLTKASessionPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMLTKASessionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<UMLTKUSessionWidget> SessionWidgetClass;
	void LoadSessionWidget();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};