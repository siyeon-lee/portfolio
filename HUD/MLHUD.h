// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MLHUD.generated.h"

/**
 * 
 */
class AMLGameCharacter;
class UMLFloaterComponent;
class UUserWidget;

UCLASS()
class MOLEWAR_API AMLHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMLHUD();
	virtual void Tick(float InDeltaTime) override;
#pragma region FLOATER
	void RegisterFloaterTarget(AMLGameCharacter* InNewTarget);
	void UnRegisterFloaterTarget(AMLGameCharacter* InDeleteTarget);
#pragma endregion //FLOATER

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floater)
		TSubclassOf<UUserWidget> WidgetFloaterBaseForm = nullptr;
private:
	UPROPERTY(Transient)
		UMLFloaterComponent* FloaterComponent;

};
