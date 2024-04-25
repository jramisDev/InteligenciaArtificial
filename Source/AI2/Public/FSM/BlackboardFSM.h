#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BlackboardFSM.generated.h"

#define DEFINE_MAP(MapType, MapName) \
	private: \
	TMap<FName, MapType> Data_##MapName; \
	public: \
	void SetValuesInMap_##MapName##(const FName& InPropertyName, MapType InValue) \
	{ \
		if(Data_##MapName##.Contains(InPropertyName)) \
		{ \
			Data_##MapName##[InPropertyName] = InValue; \
		} \
		else \
		{ \
			Data_##MapName##.Add(InPropertyName, InValue); \
		} \
	} \
	MapType GetValueFromProperty_##MapName##(const FName& InPropertyName) \
	{ \
		return Data_##MapName##.FindOrAdd(InPropertyName); \
	} \

//#define BB_PROPERTY(PropertyName) static const FName PropertyName(##PropertyName##);
UCLASS(DefaultToInstanced, EditInlineNew)
class AI2_API UBlackboardFSM : public UObject
{
	GENERATED_BODY()

	//BB_PROPERTY(ActorExample);
	
	DEFINE_MAP(float, Float);
	DEFINE_MAP(int, Int);
	DEFINE_MAP(FString, String);
	DEFINE_MAP(FVector, Vector);
	DEFINE_MAP(FRotator, Rotator);
	DEFINE_MAP(AActor*, Actor);
	
};
