// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSPATIUM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	void PassiveHealthRegen(float Amount);

	UFUNCTION()
	void OnPassiveHealthRegenFinished();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable)
	void SetRegenCooldown();
	
	UFUNCTION()
	void OnCooldownTimerFinished();

	///////////////////


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float RegenCooldownTime;

private:


	UPROPERTY()
	bool IsDead;

	FTimerHandle PassiveHealTimerHandle;
	
	UPROPERTY()
	float PassiveAmountToHeal;

	UPROPERTY()
	bool IsHealing;

	FTimerHandle CooldownTimerHandle;

	UPROPERTY()
	bool IsRegenHealthOnCooldown;


public:	
	
	//Getters and setters 
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsHealthZero() const { return Health <= 0; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsHealthMax() const { return Health == MaxHealth; }
		
};
