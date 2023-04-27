// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HJAbilitySystemComponent.h"
#include "LockOnCapturer.h"
#include "Revolver.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleAbilityInput);
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LockOn);
		EnhancedInputComponent->BindAction(ToggleLockOnAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LockOnToggle);

	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapons();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	
	AddMovementInput(FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0).GetSafeNormal(), CurrentValue.Y);
	AddMovementInput(Camera->GetRightVector(), CurrentValue.X);
	
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	AddControllerYawInput(CurrentValue.X);
	AddControllerPitchInput(CurrentValue.Y);
}

void APlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue)
{
	GetAbilitySystemComponent()->AbilityLocalInputPressed(InputActionValue.Get<float>());
}

void APlayerCharacter::LockOn()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	ALockOnCapturer* Capturer = GetWorld()->SpawnActor<ALockOnCapturer>(LockOnCapturerClass, GetActorTransform(), SpawnParams);
	TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
	if (PotentialTargets.Num() > 0)
	{
		float Distance = 0;
		// if (LockedOnTarget)
		// {
		// 	UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
		// 	WidgetCpt->SetVisibility(false);
		// }
		LockedOnTarget = GetClosestTarget(PotentialTargets, Distance);


		// UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
		// if (WidgetCpt)
		// {
		// 	WidgetCpt->SetVisibility(true);
		// }
	}
	else
	{
		return;
	}
}

void APlayerCharacter::LockOnToggle(const FInputActionValue& Value)
{
}

void APlayerCharacter::SpawnWeapons()
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Revolver = GetWorld()->SpawnActor<ARevolver>(RevolverClass, SpawnParams);
	FAttachmentTransformRules AttachRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	Revolver->AttachToComponent(GetMesh(), AttachRules, Revolver->GetWeaponSocketName());
}

AActor* APlayerCharacter::GetClosestTarget(TArray<AActor*> Targets, float& Distance)
{
	AActor* ClosestTarget = nullptr;
	float ClosestDistance = 1600;

	for (AActor* Target : Targets)
	{
		float DistTo = Target->GetDistanceTo(this);
		if (DistTo < ClosestDistance)
		{
			ClosestDistance = DistTo;
			ClosestTarget = Target;
		}
	}
	Distance = ClosestDistance;
	return ClosestTarget;
}

