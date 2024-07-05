// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
	
	

}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
		
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		Input->BindAction(SnakeAction, ETriggerEvent::Triggered, this, &APlayerPawnBase::SnakeInput);
	}


}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}



void APlayerPawnBase::SnakeInput(const FInputActionInstance& Instance)
{

	FVector2D EnhancedInputValue = Instance.GetValue().Get<FVector2D>();
	
	if (IsValid(SnakeActor)) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("value X: %f value Y: %f"), value.X, value.Y));

		if (EnhancedInputValue.X > 0 && SnakeActor->LastMoveDirection!= EMovementDirection::DOWN) {
			SnakeActor->LastMoveDirection = EMovementDirection::UP;	
		}
		else if (EnhancedInputValue.X <0 && SnakeActor->LastMoveDirection != EMovementDirection::UP) {
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
		}
		else if (EnhancedInputValue.Y > 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT) {
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
		}
		else if (EnhancedInputValue.Y < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT) {
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
	
}



