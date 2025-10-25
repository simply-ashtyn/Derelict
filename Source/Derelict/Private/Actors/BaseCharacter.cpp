// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	SpringArm->SetupAttachment(GetRootComponent() /*, Not needed unless we have to set something by it's SOCKET'*/);
	SpringArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);;
	GetMesh()->SetGenerateOverlapEvents(true);

	isDead = false;
	MaxStamina = 10.f;
	WalkSpeed = 600.f;
	SprintSpeed = 1200.f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
	PlayerController = (APlayerController*)GetController();

}

void ABaseCharacter::HandleDeath()
{

}

void ABaseCharacter::RestoreStamina(float Time)
{
	if (CurrentStamina < MaxStamina)
	{
		CurrentStamina++;
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RestoreStamina(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnRight", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABaseCharacter::Strafe);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ABaseCharacter::OpenInventory);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::SprintEnd);
}

void ABaseCharacter::InputAxisMoveForward(float AxisValue)
{
	AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), AxisValue);
}

void ABaseCharacter::Strafe(float value)
{
	FRotator MakeRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(FRotationMatrix(MakeRotation).GetScaledAxis(EAxis::Y), value);

	//AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector().RightVector, value);
}

void ABaseCharacter::OpenInventory()
{

}

void ABaseCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ABaseCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}