// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	void Fire();

	FORCEINLINE bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

protected:
	virtual void BeginPlay() override;


private:
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate{45.f};

	void LookUpRate(float AxisValue);

	void TurnRate(float AxisValue);


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth{100.f};

	UPROPERTY(VisibleAnywhere)
	float Health{100.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsDead{false};
};
