// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::UP;
	

}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
	
	
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i) {
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform  NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		int32 ElemIndex =  SnakeElements.Add(NewSnakeElem);	
		if (ElemIndex == 0) {
			NewSnakeElem->SetFirstElementType();
		}
	
	}

	
}

void ASnakeBase::Move(){
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Tick");


	MovementSpeed = ElementSize;
	FVector MovementVector(ForceInitToZero);
	FRotator SnakeRotation(0,0,0);
	
	switch (LastMoveDirection) {
	case EMovementDirection::UP:
			MovementVector.X += MovementSpeed;
			SnakeRotation = FRotator(0, -90, 0);
		break;

	case EMovementDirection::DOWN:
			MovementVector.X -= MovementSpeed;
			SnakeRotation = FRotator(0, 90, 0);
		break;

	case EMovementDirection::RIGHT:
			MovementVector.Y += MovementSpeed;
			SnakeRotation = FRotator(0, 0, 0);
		break;

	case EMovementDirection::LEFT:
			MovementVector.Y -= MovementSpeed;	
			SnakeRotation = FRotator(0, 180, 0);
		break;

	}

	

	for (int i = SnakeElements.Num() - 1; i > 0; i--) {
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);

	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->SetActorRotation(SnakeRotation);
	
}

