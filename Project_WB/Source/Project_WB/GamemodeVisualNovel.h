// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamemodeVisualNovel.generated.h"

// class ACameraActor;
// class USceneComponent;

UCLASS()
class PROJECT_WB_API AGamemodeVisualNovel : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGamemodeVisualNovel();

protected:
	virtual void BeginPlay() override;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// ACameraActor* mainCamera;
	// 
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// USceneComponent* cameraRoot;
	// 
	// UPROPERTY(EditAnywhere, Category="CameraPosition")
	// FVector mainCameraLocation;
	// 
	// UPROPERTY(EditAnywhere, Category="CameraPosition")
	// FVector mainCameraRotation;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	// USpringArmComponent* springArmComp;
	// 
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	// UCameraComponent* cameraComp;
};
