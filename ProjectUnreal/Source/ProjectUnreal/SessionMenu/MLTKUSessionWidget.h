// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MLTKUSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUNREAL_API UMLTKUSessionWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	protected:
// Bind widgets here
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CreateSessionBtn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* FindSessionsBtn;

	UFUNCTION()
	void OnCreateSessionClicked();

	UFUNCTION()
	void OnFindSessionsClicked();
};
