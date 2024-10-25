// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UHealth.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUHealth : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSPATIUM_API IUHealth
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	void HealthAdd();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	void HealthSubtract();
};
