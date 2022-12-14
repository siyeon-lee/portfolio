// Copyright Epic Games, Inc. All Rights Reserved.

#include "MLGameCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"

#include "MoleWar/MoleWar.h"
#include "HUD/MLHUD.h"
//////////////////////////////////////////////////////////////////////////
// AMLGameCharacter

AMLGameCharacter::AMLGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AMLGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController == nullptr || PlayerController->IsValidLowLevel() == false)
	{
		ML_LOG(Error, TEXT("[APlayerController] PlayerController is null"));
		return;
	}

	AMLHUD* Hud = PlayerController->GetHUD<AMLHUD>();
	if (Hud == nullptr || Hud->IsValidLowLevel() == false)
	{
		ML_LOG(Error, TEXT("[AMLHUD] Hud is null"));
		return;
	}

	Hud->RegisterFloaterTarget(this);
}

void AMLGameCharacter::Destroyed()
{
	ReleaseCharacter();
	Super::Destroyed();
}

void AMLGameCharacter::ReleaseCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController == nullptr || PlayerController->IsValidLowLevel() == false)
	{
		ML_LOG(Error, TEXT("[APlayerController] PlayerController is null"));
		return;
	}

	AMLHUD* Hud = PlayerController->GetHUD<AMLHUD>();
	if (Hud == nullptr || Hud->IsValidLowLevel() == false)
	{
		ML_LOG(Error, TEXT("[AMLHUD] Hud is null"));
		return;
	}

	Hud->UnRegisterFloaterTarget(this);

	if (WidgetFloaterBaseForm != nullptr && WidgetFloaterBaseForm->IsValidLowLevel() == true)
	{
		WidgetFloaterBaseForm->ConditionalBeginDestroy();
	}

}

void AMLGameCharacter::SetWidgetFloater(UUserWidget* InWidgetFloater)
{
	WidgetFloaterBaseForm = InWidgetFloater;
}

UUserWidget* AMLGameCharacter::GetFloaterWidget()
{
	return WidgetFloaterBaseForm;
}
