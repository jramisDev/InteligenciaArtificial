#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SteeringCustom.generated.h"

class USteering_BlendBehavior;
class UCharacterMovementComponent;

UCLASS()
class AI2_API USteeringCustom : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	friend USteering_BlendBehavior;

	bool bIsInitialized = false;
	
protected:
	
	UPROPERTY(Transient) ACharacter* Character;
	UPROPERTY(Transient) AActor* Target;	

public:
	
	void TickSteering(float DeltaSeconds);

	virtual void Init(ACharacter* InCharacter, AActor* InTarget);
	
	void SetAgent(ACharacter* InAgent) {Character = InAgent; }
	
	void SetTarget(AActor* InTarget) { Target = InTarget; }

protected:

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "SteeringBehaviors")
	FVector GetDesiredVelocity(float DeltaSeconds) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "SteeringBehaviors")
	FVector GetSteering(float DeltaSeconds) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "SteeringBehaviors")
	FVector GetDestination(float DeltaSeconds) const;
	
	void SetActualVelocity(const FVector& InVelocity) const;

	FORCEINLINE UCharacterMovementComponent* GetMovementComponent() const;
	FORCEINLINE FVector GetCurrentVelocity() const;
	FORCEINLINE float GetMaxVelocity() const;
	FORCEINLINE float GetMaxAcceleration() const;

#if WITH_EDITOR
	virtual void DrawDebugMovementComponents(float DeltaSeconds) ;
#endif
	

};
