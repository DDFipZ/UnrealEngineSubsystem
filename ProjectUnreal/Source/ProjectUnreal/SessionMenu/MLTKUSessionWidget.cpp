// Fill out your copyright notice in the Description page of Project Settings.


#include "MLTKUSessionWidget.h"

#include "Components/Button.h"
#include "ProjectUnreal/GameInstanceMLTK.h"

void UMLTKUSessionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionBtn->OnClicked.AddDynamic(this, &UMLTKUSessionWidget::OnCreateSessionClicked);
	FindSessionsBtn->OnClicked.AddDynamic(this, &UMLTKUSessionWidget::OnFindSessionsClicked);
}

void UMLTKUSessionWidget::OnCreateSessionClicked()
{
	// Not implemented yet
	UE_LOG(LogTemp, Warning, TEXT("UMLTKUSessionWidget::OnCreateSessionClicked"));
	if (UGameInstanceMLTK* instance = Cast<UGameInstanceMLTK>(GetGameInstance()))
	{
		instance->Host();
	}
}

void UMLTKUSessionWidget::OnFindSessionsClicked()
{
	// Not implemented yet
	UE_LOG(LogTemp, Warning, TEXT("UMLTKUSessionWidget::OnFindSessionsClicked"));
	if (UGameInstanceMLTK* instance = Cast<UGameInstanceMLTK>(GetGameInstance()))
	{
		instance->ConnectSession();
	}
}
