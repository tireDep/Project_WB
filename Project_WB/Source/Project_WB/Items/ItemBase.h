
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DataTables/CharacterEnumType.h"
#include "Project_WB/DataTables/ItemTable.h"
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
	virtual void OnItemMouseClick(AActor* Actor) PURE_VIRTUAL(AItemBase::OnItemMousePressed,);
	virtual void OnItemMouseReleased(AActor* Actor) PURE_VIRTUAL(AItemBase::OnItemMouseReleased,);

	// UI Subsystem 접근 헬퍼
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUIManagerSubsystem* GetUISubsystem() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* RootBoxComponent;

	// 아이템 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FItemTableData ItemData;

	// 아이템 필드 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	UPaperSpriteComponent* ItemFieldSprite;

	// 상호작용 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UMouseInteractionComponent* MouseInteractionComponent;

public:
	virtual void Tick(float DeltaTime) override;
};
