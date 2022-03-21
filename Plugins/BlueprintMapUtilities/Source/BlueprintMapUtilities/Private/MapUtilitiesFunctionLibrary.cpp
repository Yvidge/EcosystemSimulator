#include "MapUtilitiesFunctionLibrary.h"


void UMapUtilitiesFunctionLibrary::SortMapByValueReferenceInt(const TMap<UObject*, int>& Map,
	TMap<UObject*, int>& SortedMap, const bool SortByDescending)
{
	SortedMap = Map;
	if(!SortByDescending)
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A < B; });
	}
	else
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A > B; });
	}
	
}

void UMapUtilitiesFunctionLibrary::SortMapByValueReferenceFloat(const TMap<UObject*, float>& Map,
	TMap<UObject*, float>& SortedMap, const bool SortByDescending)
{
	SortedMap = Map;
	if (!SortByDescending)
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A < B; });
	}
	else
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A > B; });
	}
}

void UMapUtilitiesFunctionLibrary::SortMapByValueStringInt(const TMap<FString, int>& Map, 
	TMap<FString, int>& SortedMap, const bool SortByDescending)
{
	SortedMap = Map;
	if (!SortByDescending)
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A < B; });
	}
	else
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A > B; });
	}
}

void UMapUtilitiesFunctionLibrary::SortMapByValueStringFloat(const TMap<FString, float>& Map,
	TMap<FString, float>& SortedMap, const bool SortByDescending)
{
	SortedMap = Map;
	if (!SortByDescending)
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A < B; });
	}
	else
	{
		SortedMap.ValueSort([](const auto A, const auto B) {return A > B; });
	}
}

