// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class DERELICT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// PLAYER ATTRIBUTES
	bool isDead;
	float MaxStamina;
	float CurrentStamina;

	/// PLAYER COMPONENETS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* PlayerCamera;

	/// FUNCTIONS
	UFUNCTION(BlueprintCallable)
	void HandleDeath();
	void RestoreStamina(float Time);

private:
	/// Player Input Functions
	APlayerController* PlayerController;
	void InputAxisMoveForward(float AxisValue);
	void Strafe(float value);
	void OpenInventory();
	void SprintStart();
	void SprintEnd();

	float WalkSpeed;
	float SprintSpeed;
};
