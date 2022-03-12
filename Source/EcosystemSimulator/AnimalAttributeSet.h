// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AnimalAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEMSIMULATOR_API UAnimalAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAnimalAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(MoveSpeed);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MoveSpeed);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MoveSpeed);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAnimalAttributeSet, MoveSpeed);

};
