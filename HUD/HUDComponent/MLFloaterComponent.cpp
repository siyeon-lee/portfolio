// Fill out your copyright notice in the Description page of Project Settings.


#include "MLFloaterComponent.h"

#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

#include "MoleWar.h"
#include "Character/MLGameCharacter.h"

// > public ================================
UMLFloaterComponent::UMLFloaterComponent()
{
	WidgetTargetList.Empty();
}

void UMLFloaterComponent::RegisterFloaterTarget(AMLGameCharacter* InNewTarget, TSubclassOf<UUserWidget>& InWidget)
{
	if (InNewTarget == nullptr || InNewTarget->IsValidLowLevel() == false || InNewTarget->IsPendingKill() == true)
	{
		return;
	}

	if (InWidget == nullptr || InWidget->IsValidLowLevel() == false)
	{
		return;
	}
	//위젯 생성 및 등록
	UUserWidget* NewWidget = CreateWidget(GetWorld(), InWidget);
	if (NewWidget == nullptr || NewWidget->IsValidLowLevel() == false)
	{
		return;
	}
	NewWidget->AddToViewport(0);
	NewWidget->SetVisibility(ESlateVisibility::Collapsed);
	InNewTarget->SetWidgetFloater(NewWidget);
	WidgetTargetList.Emplace(InNewTarget);
}

void UMLFloaterComponent::UnRegisterFloaterTarget(AMLGameCharacter* InDeleteTarget)
{
	if (InDeleteTarget == nullptr || InDeleteTarget->IsValidLowLevel() == false)
	{
		return;
	}
	
	const int64 DeleteUID = InDeleteTarget->GetUniqueID();
	int32 FindIdx = WidgetTargetList.IndexOfByPredicate([DeleteUID](const TWeakObjectPtr<AMLGameCharacter>& TargetChar)
	{
		if (TargetChar.Get() == nullptr || TargetChar.IsValid() == false || TargetChar.IsStale() == true)
		{
			return false;
		}
		return TargetChar->GetUniqueID() == DeleteUID;
	});

	if (FindIdx == INDEX_NONE)
	{
		ML_LOG(Warning, TEXT("Failed to find Floater Delete Target"));
		return;
	}
	
	WidgetTargetList.RemoveAtSwap(FindIdx);
}

void UMLFloaterComponent::OnTick_UpdateFloaterWidget()
{
	if (WidgetTargetList.Num() == 0)
	{
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController == nullptr || PlayerController->IsValidLowLevel() == false)
	{
		return;
	}

	for (TWeakObjectPtr<AMLGameCharacter>& TargetCharacter : WidgetTargetList)
	{
		if (TargetCharacter.Get() == nullptr || TargetCharacter.IsValid() == false || TargetCharacter.IsStale() == true || TargetCharacter.Get()->IsPendingKill() == true)
		{
			continue;
		}

		UUserWidget* FloaterForm = TargetCharacter->GetFloaterWidget();
		if (FloaterForm == nullptr || FloaterForm->IsValidLowLevel() == false)
		{
			ML_LOG(Error, TEXT("[UUserWidget] FloaterForm  is null"));
			continue;
		}

		//월드 좌표를 스크린좌표로
		FVector TargetLocation = TargetCharacter->GetActorLocation();
		FVector2D ScreenLocation = FVector2D();
		if (PlayerController->ProjectWorldLocationToScreen(TargetLocation, ScreenLocation) == false)
		{
			//시야 밖에 있는 경우
			FloaterForm->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			FloaterForm->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			FloaterForm->SetRenderTransform(FWidgetTransform(ScreenLocation, FVector2D::UnitVector, FVector2D::ZeroVector, 0));
		}
	}

}
// < public ================================