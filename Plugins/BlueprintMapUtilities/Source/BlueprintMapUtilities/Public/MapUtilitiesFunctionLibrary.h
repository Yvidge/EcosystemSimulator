#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MapUtilitiesFunctionLibrary.generated.h"


UCLASS()
class UMapUtilitiesFunctionLibrary: public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Map|Utilities")
	static void SortMapByValueReferenceInt(const TMap<UObject*, int>& Map, TMap<UObject*, int>& SortedMap, const bool SortByDescending);

	UFUNCTION(BlueprintCallable, Category = "Map|Utilities")
	static void SortMapByValueReferenceFloat(const TMap<UObject*, float>& Map, TMap<UObject*, float>& SortedMap, const bool SortByDescending);

	UFUNCTION(BlueprintCallable, Category = "Map|Utilities")
	static void SortMapByValueStringInt(const TMap<FString, int>& Map, TMap<FString, int>& SortedMap, const bool SortByDescending);

	UFUNCTION(BlueprintCallable, Category = "Map|Utilities")
	static void SortMapByValueStringFloat(const TMap<FString, float>& Map, TMap<FString, float>& SortedMap, const bool SortByDescending);
	
};