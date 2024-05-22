// Fill out your copyright notice in the Description page of Project Settings.


#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Engine/LocalPlayer.h>
#include <InputMappingContext.h>
#include <UserActivityTracking.h>
#include <Kismet/GameplayStatics.h>
//
#include "MovingCube.h"
// Sets default values
AMovingCube::AMovingCube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();

     setupInput();
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovingCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovingCube::setupInput()
{
    APlayerController *controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if(!controller || !InputComponent ){
        UE_LOG(LogTemp, Warning, TEXT(" get ontroller Failed...."));
        return;
    }



    // I don't expose this InputActions and InputMappingContext to UnrealEditor, I just load them on the fly
    // the correct way is exposing all them to UnrealEditor and let user configure them, and then no need to load them with code again....
     UInputAction* myJumaAct = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/IA_Jump.IA_Jump"), NULL, LOAD_None, NULL);
     UInputAction* myMoveAct = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/IA_Move.IA_Move"), NULL, LOAD_None, NULL);
     UInputMappingContext* myInputMapCtx = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Input/IMC_MovingCube.IMC_MovingCube"), NULL, LOAD_None, NULL);


   if (!myJumaAct || !myMoveAct || !myInputMapCtx) {
        UE_LOG(LogTemp, Warning, TEXT(" Load IA_Jump or IA_Move or IMC_MovingCube failed...."));
        return;
   }

    //EnableInput(controller);

    if (UEnhancedInputComponent *eic = CastChecked<UEnhancedInputComponent>(InputComponent)){

         eic->BindAction(myJumaAct , ETriggerEvent::Triggered , this , &AMovingCube::startJump );
         eic->BindAction(myJumaAct , ETriggerEvent::Completed , this , &AMovingCube::stopJump );
         eic->BindAction(myMoveAct , ETriggerEvent::Triggered , this , &AMovingCube::moveAct );
    }

    if (APlayerController *pctllor = Cast<APlayerController>(controller)){
        if (UEnhancedInputLocalPlayerSubsystem *subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pctllor->GetLocalPlayer()))
        {
            subsys->AddMappingContext(myInputMapCtx , 0);
        }
    }
}


void AMovingCube::startJump()
{
    UE_LOG(LogTemp, Warning, TEXT(" startJump...."));
}

void AMovingCube::stopJump()
{
    UE_LOG(LogTemp, Warning, TEXT(" stopJump...."));
}

void AMovingCube::moveAct(const FInputActionValue &val)
{
    FVector2D val2D = val.Get<FVector2D>();
    UE_LOG(LogTemp, Warning, TEXT(" Moving: x: %f , y: %f") , val2D.X , val2D.Y );
}
























