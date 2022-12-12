// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MLFloaterComponent.generated.h"

/**
 * [2022.12.13]
 * ĳ���͸� ����ٴϴ� ������ "Floater"�� ������Ʈ �ϱ� ���� Ŭ����
 * MLHUD�� ���� ȣ���Ѵ�.
 */
class AMLGameCharacter;
class UUserWidget;

UCLASS()
class MOLEWAR_API UMLFloaterComponent : public UObject
{
	GENERATED_BODY()
public:
	UMLFloaterComponent();

	//�÷��� Ÿ�� ���
	void RegisterFloaterTarget(AMLGameCharacter* InNewTarget, TSubclassOf<UUserWidget>& InWidget);
	//�÷��� Ÿ�� ����
	void UnRegisterFloaterTarget(AMLGameCharacter* InDeleteTarget);
	
	void OnTick_UpdateFloaterWidget();
private:
	TArray<TWeakObjectPtr<AMLGameCharacter>> WidgetTargetList;
};
