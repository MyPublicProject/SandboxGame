// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SiAiHandObject.generated.h"

UCLASS()
class SANDBOXGAME_API ASiAiHandObject : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASiAiHandObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//������ƷID������Ʒ�Ĺ������� TSubclassOf ?
	static TSubclassOf<AActor> SpawnHandObject(int ObjectID);

	// �Ƿ�������
	void ChangeOverlayDetect(bool IsOpen);

public:

	// ��ƷID
	int ObjectIndex;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	// �����
	class USceneComponent *RootScene;

	// ��̬ģ��
	UPROPERTY(EditAnywhere, Category = "SiAi")
		class UStaticMeshComponent *BaseMesh;

	// ������ײ��
	UPROPERTY(EditAnywhere, Category = "SiAi")
		class UBoxComponent *AffectCollision;

};
