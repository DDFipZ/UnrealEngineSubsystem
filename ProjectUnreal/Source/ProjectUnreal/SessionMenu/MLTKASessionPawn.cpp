// Fill out your copyright notice in the Description page of Project Settings.


#include "MLTKASessionPawn.h"


// Sets default values
AMLTKASessionPawn::AMLTKASessionPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up widget component
	ConstructorHelpers::FClassFinder<UMLTKUSessionWidget> SessionWidgetClassBP(TEXT("/Game/Menus/SessionMenu/BP_SessionWidget"));
	if (!ensure(SessionWidgetClassBP.Class != nullptr)) return;
	SessionWidgetClass = SessionWidgetClassBP.Class;
}

// Called when the game starts or when spawned
void AMLTKASessionPawn::BeginPlay()
{
	Super::BeginPlay();
	LoadSessionWidget();
}

// Called every frame
void AMLTKASessionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMLTKASessionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

// Helpers
void AMLTKASessionPawn::LoadSessionWidget()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr) return;

	UMLTKUSessionWidget* SessionWidget = CreateWidget<UMLTKUSessionWidget>(PlayerController, SessionWidgetClass);
	SessionWidget->AddToViewport();
}


