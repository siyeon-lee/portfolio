// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MLGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UUserWidget;

UCLASS(config = Game)
class AMLGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMLGameCharacter();

#pragma region THIRDPERSON_ENGINE_BASE
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion //THIRDPERSON_ENGINE_BASE


public:
#pragma region THIRDPERSON_ENGINE_BASE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;
#pragma endregion //THIRDPERSON_ENGINE_BASE

public:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	void ReleaseCharacter();
	void SetWidgetFloater(UUserWidget* InWidgetFloater);
	UUserWidget* GetFloaterWidget();
#pragma region FLOATER_SETTING_VALUE
private:
	UPROPERTY(Transient)
		UUserWidget* WidgetFloaterBaseForm;
#pragma endregion //FLOATER_SETTING_VALUE


};


