
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerActorController.generated.h"

class AGameCamera;
UCLASS()
class PROJECT_WB_API APlayerActorController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerActorController();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Camera")
	AGameCamera* CurrentCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	FName FindCameraTagName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float BlendTime = 1.0f;

public:
	UFUNCTION(BlueprintCallable, Category="Camera")
	void SwitchCamera(AGameCamera* NewCamera, float TransitionTime = 1.0f);	// 카메라 전환 함수

	UFUNCTION(BlueprintCallable, Category="Camera")
	void SwitchCameraByTag(FName CameraTag, float TransitionTime = 1.0f);	// 태그로 카메라 찾아서 전환 함수

	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetupLevelCamera();	// 자동으로 레벨의 메인 카메라 설정
};
