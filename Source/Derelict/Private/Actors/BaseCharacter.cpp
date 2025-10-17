// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0., 0., 60.));
	SpringArm->SetupAttachment(GetRootComponent() /*, Not needed unless we have to set something by it's SOCKET'*/);
	SpringArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);;
	GetMesh()->SetGenerateOverlapEvents(true);

	isDead = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::HandleDeath()
{

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnRight", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABaseCharacter::Strafe);
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