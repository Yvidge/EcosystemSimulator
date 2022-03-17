// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldStatisticsSubsystem.h"

void UWorldStatisticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//GetWorld()->GetTimerManager().SetTimer(DeltaUpdateTimer, this, &UWorldStatisticsSubsystem::UpdateDeltas, DeltaUpdatePeriod, true);

}

void UWorldStatisticsSubsystem::Deinitialize()
{
	CurrentEntities.Empty();
	DeltaUpdateTimer.Invalidate();
	Super::Deinitialize();
}


void UWorldStatisticsSubsystem::NewEntityCreated(UClass* Class, FString Name)
{
	if (CurrentEntities.Contains(Class))
	{
		FStatisticData* UpdatedData = CurrentEntities.Find(Class);
		UpdatedData->CurrentNum++;
		//UpdatedData->Delta++;
	}
	else
	{
		FStatisticData NewData;
		NewData.Name = Name;
		CurrentEntities.Add(Class, NewData);
	}
}


void UWorldStatisticsSubsystem::EntityDestroyed(UClass* Class)
{
	if (CurrentEntities.Contains(Class))
	{
		FStatisticData* UpdatedData = CurrentEntities.Find(Class);
		UpdatedData->CurrentNum--;
		//UpdatedData->Delta--;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Incorrect map keys");
	}
}

TMap<UClass*, FStatisticData> UWorldStatisticsSubsystem::GetCurrentEntities()
{
	return CurrentEntities;
}


