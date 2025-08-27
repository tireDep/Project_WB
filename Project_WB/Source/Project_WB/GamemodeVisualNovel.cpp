
// #include "Camera/CameraActor.h"
#include "GamemodeVisualNovel.h"

AGamemodeVisualNovel::AGamemodeVisualNovel()
{
	// cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	
	// springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	// springArmComp->SetupAttachment(RootComponent);
	// 
	// springArmComp->bUsePawnControlRotation = false; // 컨트롤러의 회전을 따름
	// springArmComp->bInheritPitch = false;
	// springArmComp->bInheritYaw = false;
	// springArmComp->bInheritRoll = false;
	// 
	// springArmComp->TargetArmLength = 600.0f;
	// springArmComp->bDoCollisionTest = false;
	// springArmComp->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	// 
	// cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	// cameraComp->SetupAttachment(springArmComp, USpringArmComponent::SocketName);
}

void AGamemodeVisualNovel::BeginPlay()
{
	Super::BeginPlay();

	// FVector cameraLocation = FVector(mainCameraLocation.X, mainCameraLocation.Y, mainCameraLocation.Z);
	// FRotator cameraRotation = FRotator(mainCameraRotation.Y, mainCameraRotation.Z, mainCameraRotation.X);
	// 
	// mainCamera = GetWorld()->SpawnActor<ACameraActor>(cameraLocation,cameraRotation);
	// 
	// APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	// if ( playerController != nullptr)
	// {
	// 	playerController->SetViewTarget(mainCamera);
	// }
}
