
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MouseInteractionComponent.generated.h"

class UPaperSpriteComponent;
class UPrimitiveComponent;

// 이벤트 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseOverDelegate, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseExitDelegate, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseClickDelegate, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseReleaseDelegate, AActor*, Actor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_WB_API UMouseInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMouseInteractionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetTargetSprite(UPaperSpriteComponent* PaperSpriteComponent);

	UPROPERTY(BlueprintAssignable)
	FOnMouseOverDelegate OnMouseOverEvent;

	UPROPERTY(BlueprintAssignable)
	FOnMouseExitDelegate OnMouseExitEvent;

	UPROPERTY(BlueprintAssignable)
	FOnMouseClickDelegate OnMouseClickEvent;

	UPROPERTY(BlueprintAssignable)
	FOnMouseReleaseDelegate OnMouseReleaseEvent;

private:
	UPROPERTY()
	UPaperSpriteComponent* TargetSpriteComponent;

	UFUNCTION()
	void HandleMouseOverEvent(UPrimitiveComponent* SelectComp);

	UFUNCTION()
	void HandleMouseExitEvent(UPrimitiveComponent* SelectComp);

	UFUNCTION()
	void HandleMouseClickEvent(UPrimitiveComponent* SelectComp, FKey ButtonPressed);

	UFUNCTION()
	void HandleMouseReleaseEvent(UPrimitiveComponent* SelectComp, FKey ButtonPressed);
};
