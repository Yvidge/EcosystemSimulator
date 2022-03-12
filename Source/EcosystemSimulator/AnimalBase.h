// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AnimalAttributeSet.h"
#include "AnimalBase.generated.h"

UCLASS()
class ECOSYSTEMSIMULATOR_API AAnimalBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimalBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = AbilitySystem)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, meta = (AllowPrivateAccess = "true"))
	UAnimalAttributeSet* BaseAttributeSet;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveSpeedChanged(const FOnAttributeChangeData& Data);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//AbilitySystemInterface
	FORCEINLINE class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

};
