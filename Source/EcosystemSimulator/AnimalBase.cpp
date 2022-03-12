// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalBase.h"

#include "AnimalMovementComponent.h"

// Sets default values
//AAnimalBase::AAnimalBase()
//{
// 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}

AAnimalBase::AAnimalBase(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UAnimalMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BaseAttributeSet = CreateDefaultSubobject<UAnimalAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &AAnimalBase::MoveSpeedChanged);
	}
}

void AAnimalBase::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = Data.NewValue;
}

// Called every frame
void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


