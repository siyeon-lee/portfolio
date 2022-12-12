// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MLFloaterComponent.generated.h"

/**
 * [2022.12.13]
 * 캐릭터를 따라다니는 위젯인 "Floater"를 업데이트 하기 위한 클래스
 * MLHUD를 통해 호출한다.
 */
class AMLGameCharacter;
class UUserWidget;

UCLASS()
class MOLEWAR_API UMLFloaterComponent : public UObject
{
	GENERATED_BODY()
public:
	UMLFloaterComponent();

	//플로터 타겟 등록
	void RegisterFloaterTarget(AMLGameCharacter* InNewTarget, TSubclassOf<UUserWidget>& InWidget);
	//플로터 타겟 해제
	void UnRegisterFloaterTarget(AMLGameCharacter* InDeleteTarget);
	
	void OnTick_UpdateFloaterWidget();
private:
	TArray<TWeakObjectPtr<AMLGameCharacter>> WidgetTargetList;
};
