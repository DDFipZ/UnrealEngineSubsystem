// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MLTKUSessionItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUNREAL_API UMLTKUSessionItem : public UUserWidget
{
	GENERATED_BODY()
	protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SessionNameText;
};
