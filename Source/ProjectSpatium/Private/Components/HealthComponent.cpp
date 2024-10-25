// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "TimerManager.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHealthComponent::Heal(float Amount)
{
	if (!IsDead && Health != MaxHealth) 
	{
		Health = FMath::Clamp(Amount + Health, 0.f, MaxHealth);

		//UE_LOG(LogTemp, Warning, TEXT("The current health of %s is %f. Added %f."), *GetOwner()->GetName(), Health, Amount);
		
		if (GEngine)
		{
			FString DebugMessage = FString::Printf(TEXT("The current health of %s is %f. Added %f."),
				*GetOwner()->GetName(), Health, Amount);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
		}
	}
}

void UHealthComponent::PassiveHealthRegen(float Amount)
{
	if (!IsRegenHealthOnCooldown && !IsHealing && !IsHealthMax())
	{
		IsHealing = true;
		PassiveAmountToHeal = Amount;
		GetWorld()->GetTimerManager().SetTimer(PassiveHealTimerHandle, this, &UHealthComponent::OnPassiveHealthRegenFinished, 2.f, false);
	}
}

void UHealthComponent::OnPassiveHealthRegenFinished()
{
	IsHealing = false;
	Heal(PassiveAmountToHeal);
	GetWorld()->GetTimerManager().ClearTimer(PassiveHealTimerHandle);
}

void UHealthComponent::TakeDamage(float Amount)
{
	if (!IsDead)
	{
		Health = FMath::Clamp(Health - Amount, 0.f, MaxHealth);

		//UE_LOG(LogTemp, Warning, TEXT("The current health of %s is %f. Subtracted %f."), *GetOwner()->GetName(), Health, Amount);
		
		if (GEngine)
		{
			FString DebugMessage = FString::Printf(TEXT("The current health of %s is %f. Subtracted %f."),
				*GetOwner()->GetName(), Health, Amount);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
		}

		if (IsHealthZero())
		{
			IsDead = true;
		}
	}
}

void UHealthComponent::SetRegenCooldown()
{
	IsRegenHealthOnCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UHealthComponent::OnCooldownTimerFinished, RegenCooldownTime, false);
}

void UHealthComponent::OnCooldownTimerFinished()
{
	IsRegenHealthOnCooldown = false;

	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

