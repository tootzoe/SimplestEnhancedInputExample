// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "InputActionValue.h"

#include "MovingCube.generated.h"

UCLASS()
class PAWNCONTROLEXAM1_API AMovingCube : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	AMovingCube();



    UPROPERTY(EditAnywhere,  Category = "TOOT Property")
    USceneComponent *TOOTVisibleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

    void setupInput();

    void startJump();
    void stopJump();
    void moveAct(const FInputActionValue &val);


    FVector currVelocity;
    bool bGrowing;


};


