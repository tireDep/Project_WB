
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class UMouseInteractionComponent;

UCLASS(Abstract)
class PROJECT_WB_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();

protected:
	virtual void BeginPlay() override;

	// 순수 가상 함수
	// 해당 방식으로 선언하면, 상속받은 클래스에서 선언을 하지 않아도 빌드 에러가 나지 않음에 유의!
	virtual void OnItemMouseOver(AActor* Actor) PURE_VIRTUAL(AItemBase::OnItemMouseOver,);
	virtual void OnItemMouseExit(AActor* Actor) PURE_VIRTUAL(AItemBase::OnItemMouseExit,);
	virtual void OnItemMousePressed(AActor* Actor) PURE_VIRTUAL(AItemBase::OnItemMousePressed,);
	virtual void OnItemMouseReleased(AActor* Actor) PURE_VIRTUAL(AItemBase::OnItemMouseReleased,);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* RootBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* ItemSprite;

	// 상호작용 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UMouseInteractionComponent* MouseInteractionComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Item Info")
	int ItemID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Item Info")
	FName ItemName;

	// 아이템 설명
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Item Info")
	FName ItemDescription;

	// npc키 값, 상호작용 대사 키 값
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Item Info")
	TMap<int, int> InteractionInfo;

public:
	virtual void Tick(float DeltaTime) override;
};
