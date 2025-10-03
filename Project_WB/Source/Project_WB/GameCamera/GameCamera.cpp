
#include "GameCamera.h"

#include "Camera/CameraComponent.h"

constexpr float GDefault_Ortho_Width = 1920.0f;
constexpr float GDefault_Field_Of_View = 45.0f;

const FRotator GDefault_Camera_Rotation = FRotator(0.0f, -90.0f, 0.0f); // x, z, y

AGameCamera::AGameCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	UseOrthographicProjection = false;
	OrthoWidth = GDefault_Ortho_Width;
	FieldOfView = GDefault_Field_Of_View;
	
	SetActorRotation(GDefault_Camera_Rotation);
}

void AGameCamera::BeginPlay()
{
	Super::BeginPlay();
	Apply2DCameraSetting();
}

// 2D 카메라 설정
void AGameCamera::Apply2DCameraSetting() const
{
	UCameraComponent* CameraComp = GetCameraComponent();
	if (CameraComp == nullptr)
		return;

	if (UseOrthographicProjection == true)
	{
		CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
		CameraComp->SetOrthoWidth(OrthoWidth);
	}
	else
	{
		CameraComp->SetProjectionMode(ECameraProjectionMode::Perspective);
		CameraComp->SetOrthoWidth(FieldOfView);
	}
}

