
#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameCamera.generated.h"

UCLASS()
class PROJECT_WB_API AGameCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AGameCamera();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2DSettings")
	bool UseOrthographicProjection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2DSettings", meta = (EditCondition = "UseOrthographicProjection"))
	float OrthoWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2DSettings", meta = (EditCondition = "!UseOrthographicProjection"))
	float FieldOfView;

public:
	void Apply2DCameraSetting() const;
};
