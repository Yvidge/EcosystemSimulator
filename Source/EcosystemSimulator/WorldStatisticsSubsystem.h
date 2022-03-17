// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldStatisticsSubsystem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStatisticData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FString Name = "Invalid Name";

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int CurrentNum = 1;

	/*UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Delta = 1;*/

};


UCLASS()
class ECOSYSTEMSIMULATOR_API UWorldStatisticsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	/** Override to control if the Subsystem should be created at all.
	 * For example you could only have your system created on servers.
	 * It's important to note that if using this is becomes very important to null check whenever getting the Subsystem.
	 *
	 * Note: This function is called on the CDO prior to instances being created!
	 */

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

private:
	friend class FSubsystemCollectionBase;
	FSubsystemCollectionBase* InternalOwningSubsystem;

	float DeltaUpdatePeriod = 10;

	FTimerHandle DeltaUpdateTimer;

public:

	TMap<UClass*, FStatisticData> CurrentEntities;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void NewEntityCreated(UPARAM(ref) UClass* Class, FString Name);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void EntityDestroyed(UPARAM(ref) UClass* Class);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	TMap<UClass*, FStatisticData> GetCurrentEntities();

	
};

