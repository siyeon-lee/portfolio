// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MLHUD.h"

#include "Blueprint/UserWidget.h"

#include "MoleWar.h"
#include "HUD/HUDComponent/MLFloaterComponent.h"
#include "Character/MLGameCharacter.h"

// > public =======================================

AMLHUD::AMLHUD()
{
	FloaterComponent = CreateDefaultSubobject<UMLFloaterComponent>(TEXT("FloaterComponent"));
}

void AMLHUD::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	if (FloaterComponent != nullptr && FloaterComponent->IsValidLowLevel() == true)
	{
		FloaterComponent->OnTick_UpdateFloaterWidget();
	}
}

void AMLHUD::RegisterFloaterTarget(AMLGameCharacter* InNewTarget)
{
	if (InNewTarget == nullptr || InNewTarget->IsValidLowLevel() == false || InNewTarget->IsPendingKill() == true)
	{
		return;
	}

	if (WidgetFloaterBaseForm == nullptr || WidgetFloaterBaseForm->IsValidLowLevel() == false)
	{
		return;
	}

	if (FloaterComponent == nullptr || FloaterComponent->IsValidLowLevel() == false)
	{
		ML_LOG(Error, TEXT("[UMLFloaterComponent]FloaterComponent is null"));
		return;
	}

	FloaterComponent->RegisterFloaterTarget(InNewTarget, WidgetFloaterBaseForm);
}

void AMLHUD::UnRegisterFloaterTarget(AMLGameCharacter * InDeleteTarget)
{
	if (FloaterComponent == nullptr || FloaterComponent->IsValidLowLevel() == false)
	{
		ML_LOG(Error, TEXT("[UMLFloaterComponent]FloaterComponent is null"));
		return;
	}

	FloaterComponent->UnRegisterFloaterTarget(InDeleteTarget);
}
// < public =======================================
