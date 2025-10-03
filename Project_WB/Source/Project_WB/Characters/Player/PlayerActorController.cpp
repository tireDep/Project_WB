
#include "PlayerActorController.h"

#include "API_DebugUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Project_WB/GameCamera/GameCamera.h"

APlayerActorController::APlayerActorController()
{
	// PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bCanEverTick = true;
	
	CurrentCamera = nullptr;
}

void APlayerActorController::BeginPlay()
{
	Super::BeginPlay();

	SetupLevelCamera();
}

void APlayerActorController::SwitchCamera(AGameCamera* NewCamera, float TransitionTime)
{
	if (NewCamera == nullptr)
	{
		FAPI_DebugUtils::ShowError("SwitchCamera NewCamera is nullptr!");
		return;
	}

	CurrentCamera = NewCamera;
	SetViewTargetWithBlend( NewCamera, TransitionTime );
	
	FAPI_DebugUtils::ShowInfo("SwitchCamera Switched to camera[" + NewCamera->GetName() + "]");
}

void APlayerActorController::SwitchCameraByTag(FName CameraTag, float TransitionTime)
{
	TArray<AActor*> FoundCameras;

	UGameplayStatics::GetAllActorsOfClassWithTag(
		GetWorld(),
		AGameCamera::StaticClass(),
		CameraTag,
		FoundCameras
		);

	if ( FoundCameras.IsEmpty() == true )
	{
		FAPI_DebugUtils::ShowError("SwitchCameraByTag FoundCameras is empty!");
	}
	else
	{
		AGameCamera* FoundCamera = Cast<AGameCamera>(FoundCameras[0]);
		SwitchCamera(FoundCamera, TransitionTime);
	}
}

void APlayerActorController::SetupLevelCamera()
{
	SwitchCameraByTag(FindCameraTagName, 0.0f);

	if ( CurrentCamera == nullptr )
	{
		FAPI_DebugUtils::ShowError("SetupLevelCamera is nullptr! FindCamerasTagName[" + FindCameraTagName.ToString() + "]");

		TArray<AActor*> AlLCameras;
		UGameplayStatics::GetAllActorsOfClass( GetWorld(), AGameCamera::StaticClass(),AlLCameras);
		if ( AlLCameras.IsEmpty() == true )
		{
			FAPI_DebugUtils::ShowError("SetupLevelCamera AlLCameras is empty!");
		}
		else
		{
			AGameCamera* FirstCamera = Cast<AGameCamera>(AlLCameras[0]);
			SwitchCamera(FirstCamera,0.0f);
		}
	}
}
