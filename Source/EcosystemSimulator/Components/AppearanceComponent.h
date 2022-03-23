// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AppearanceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class ECOSYSTEMSIMULATOR_API UAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAppearanceComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SexualDemorphism", meta = (DisplayName = "SexualDemorphism"))
	bool bSexualDemorphism;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SexualDemorphism", meta = (EditCondition = "bSexualDemorphism", EditConditionHides))
	USkeletalMesh* MaleMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SexualDemorphism", meta = (EditCondition = "bSexualDemorphism", EditConditionHides))
	USkeletalMesh* FemaleMesh;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
