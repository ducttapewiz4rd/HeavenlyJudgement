// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HJAbilitySystemComponent.h"
#include "InteractableInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "HJPlayerController.h"
#include "LockOnCapturer.h"
#include "InteractSphere.h"
#include "Revolver.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "InventoryComponent.h"
#include "AbilityStateComponent.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	AbilityStateComponent = CreateDefaultSubobject<UAbilityStateComponent>(TEXT("AbilityStateComponent"));
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SendJumpEventsToActorAbility);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(ReadyAbilityAction, ETriggerEvent::Completed, this, &APlayerCharacter::ReadyAbilityReleased);
		EnhancedInputComponent->BindAction(ReadyAbilityAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ReadyAbility);
		EnhancedInputComponent->BindAction(LeftFaceAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LeftFaceActionPressed);

	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapons();
	PlayerCont = Cast<AHJPlayerController>(GetOwner());
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	GiveUniqueAbilities();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	if (LockedOnTarget)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockedOnTarget->GetActorLocation());
		FRotator InterpRot = FMath::RInterpTo(PlayerCont->GetControlRotation(), LookAtRotation, DeltaTime, 5.f);
		PlayerCont->SetControlRotation(InterpRot);
	}
}

bool APlayerCharacter::IsLockedOn(AActor*& LockedOnActor)
{
	if (LockedOnTarget)
	{
		LockedOnActor = LockedOnTarget;
		return true;
	}
	return false;
}

void APlayerCharacter::SetPlayerHasKey(bool HasKey)
{
	bHasKey = HasKey;
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

	if (LockedOnTarget)
	{
		AddControllerYawInput(0);
		AddControllerPitchInput(0);
	}
	else
	{
		AddControllerYawInput(CurrentValue.X);
		AddControllerPitchInput(-CurrentValue.Y);
	}

}

void APlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue)
{
	GetAbilitySystemComponent()->AbilityLocalInputPressed(InputActionValue.Get<float>());
}

void APlayerCharacter::LockOn()
{

	if (LockedOnTarget)
	{
		LockedOnTarget = nullptr;
		return;
	}


	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	ALockOnCapturer* Capturer = GetWorld()->SpawnActor<ALockOnCapturer>(LockOnCapturerClass, GetActorTransform(), SpawnParams);
	TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
	if (PotentialTargets.Num() > 0)
	{
		float Distance = 0;
		LockedOnTarget = GetClosestTarget(PotentialTargets, Distance);

	}
	else
	{
		return;
	}
}

void APlayerCharacter::LockOnToggle(const FInputActionValue& Value)
{

	float ToggledAxis = Value.Get<float>();

	if (LockedOnTarget)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = this;
		ALockOnCapturer* Capturer = GetWorld()->SpawnActor<ALockOnCapturer>(LockOnCapturerClass, GetActorTransform(), SpawnParams);
		TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
		AActor* BestEnemy = nullptr;
		float BestDistance = FLT_MAX;

		FVector2D CurrentTargetScreenLoc;

		for (AActor* Enemy : PotentialTargets)
		{
			if (Enemy == LockedOnTarget)
			{
				continue;
			}


			FVector ToEnemy = Enemy->GetActorLocation() - LockedOnTarget->GetActorLocation();
			FVector Right = Camera->GetRightVector();
			float dot = FVector::DotProduct(ToEnemy.GetSafeNormal(), Right);
			bool bothPos = dot > 0 && ToggledAxis > 0;
			bool bothNeg = dot < 0 && ToggledAxis < 0;
			if (dot * ToggledAxis > 0)
			{

				FVector CurrentTargetToEnemy = Enemy->GetActorLocation() - LockedOnTarget->GetActorLocation();
				float CamViewDistance = FMath::Abs(FVector::DotProduct(CurrentTargetToEnemy, Right));

				if (CamViewDistance < BestDistance)
				{

					BestEnemy = Enemy;
					BestDistance = CamViewDistance;
				}
			}


		}
		if (BestEnemy != nullptr)
		{

			LockedOnTarget = BestEnemy;

		}
	}
}

void APlayerCharacter::Interact()
{
	//TODO, spawn interact sphere, if it has the interface use its function to do its stuff.
	UE_LOG(LogTemp, Warning, TEXT("Interacting"));

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	AInteractSphere* Capturer = GetWorld()->SpawnActor<AInteractSphere>(InteractSphereClass, GetActorTransform(), SpawnParams);
	TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
	if (PotentialTargets.Num() > 0)
	{
		float distance = 0;
		IInteractableInterface* interactInferface = Cast<IInteractableInterface>(GetClosestTarget(PotentialTargets, distance));
		interactInferface->InteractWith(this);
	}


}

void APlayerCharacter::ReadyAbility()
{
	bPressingAbilityReadyInput = true;
}

void APlayerCharacter::ReadyAbilityReleased()
{
	bPressingAbilityReadyInput = false;

}

void APlayerCharacter::LeftFaceActionPressed()
{
	if (bPressingAbilityReadyInput)
	{
		UE_LOG(LogTemp, Warning, TEXT("Use Trigger Ability"));
		FAbilityStruct CurrentStateAbility = AbilityStateComponent->GetAbilitiesForState();
		GetAbilitySystemComponent()->TryActivateAbilityByClass(CurrentStateAbility.LeftFaceAbility);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("This is the normal attack"));
		

	}

}

void APlayerCharacter::SpawnWeapons()
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Revolver = GetWorld()->SpawnActor<ARevolver>(RevolverClass, SpawnParams);
	Revolver->SetOwner(this);
	FAttachmentTransformRules AttachRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	Revolver->AttachToComponent(GetMesh(), AttachRules, Revolver->GetWeaponSocketName());
}

void APlayerCharacter::GiveUniqueAbilities()
{
	Super::GiveUniqueAbilities();
	GiveAbility(DoubleJumpAbilityClass);
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



