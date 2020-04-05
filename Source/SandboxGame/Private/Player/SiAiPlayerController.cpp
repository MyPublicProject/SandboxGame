// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerController.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerState.h"
#include "SiAiMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "SiAiHelper.h"
#include "Components/LineBatchComponent.h"
#include "Camera/CameraComponent.h"
#include "CollisionQueryParams.h"
#include "SiAiPickupObject.h"
#include "SiAiResourceObject.h"


ASiAiPlayerController::ASiAiPlayerController()
{
	// 允许Tick
	PrimaryActorTick.bCanEverTick = true;
}

void ASiAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// 进行射线检测
	RunRayCast();
	// 处理动作状态
	StateMachine();

}

void ASiAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// 绑定视角切换
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASiAiPlayerController::ChangeView);
	// 绑定鼠标事件
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASiAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASiAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASiAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASiAiPlayerController::RightEventStop);
	// 绑定鼠标滚轮事件
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ASiAiPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ASiAiPlayerController::ScrollDownEvent);
	// 退出游戏
	InputComponent->BindAction("QuitGame", IE_Pressed, this, &ASiAiPlayerController::QuitGame);
}

void ASiAiPlayerController::ChangeHandObject()
{
	// 切换手持物品
	SPCharacter->ChangeHandObject(SPState->GetCurrentHandObjectIndex());
}

void ASiAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!SPCharacter) SPCharacter = Cast<ASiAiPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ASiAiPlayerState>(PlayerState);
	// 设置鼠标不显示
	bShowMouseCursor = false;
	// 设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

// 	LeftUpperType = EUpperBody::PickUp;
// 	RightUpperType = EUpperBody::PickUp;

	IsRightButtonDown = false;
	IsLeftButtonDown = false;
}

void ASiAiPlayerController::ChangeView()
{
	//如果不允许切换视角,直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		SPCharacter->ChangeView(EGameViewMode::Third);
		break;
	case EGameViewMode::Third:
		SPCharacter->ChangeView(EGameViewMode::First);
		break;
	default:
		break;
	}
}

void ASiAiPlayerController::LeftEventStart()
{
	IsLeftButtonDown = true;
	SPCharacter->UpperType = LeftUpperType;
}

void ASiAiPlayerController::LeftEventStop()
{
	IsLeftButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASiAiPlayerController::RightEventStart()
{
	IsRightButtonDown = true;
	SPCharacter->UpperType = RightUpperType;
}

void ASiAiPlayerController::RightEventStop()
{
	IsRightButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASiAiPlayerController::ScrollUpEvent()
{
	// 如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	// 如果鼠标有在按键不允许切换
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// 告诉快捷栏切换快捷容器
	SPState->ChooseShortcut(true);

	//更改Character的手持物品
	ChangeHandObject();
}

void ASiAiPlayerController::ScrollDownEvent()
{
	// 如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	// 如果鼠标有在按键不允许切换
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// 告诉快捷栏切换快捷容器
	SPState->ChooseShortcut(false);

	//更改Character的手持物品
	ChangeHandObject();
}

void ASiAiPlayerController::QuitGame()
{
	// 控制台
	Cast<ASiAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
}

void ASiAiPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	//根据当前手持物品的类型来修改预动作
	switch (SPState->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;
		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		//如果右键状态是拾取那就给拾取,拾取优先级高
		RightUpperType = RightType == EUpperBody::None ? EUpperBody::Eat : RightType;
		break;
	case EObjectType::Tool:
		LeftUpperType = EUpperBody::Hit;
		RightUpperType = RightType;
		break;
	case EObjectType::Weapon:
		LeftUpperType = EUpperBody::Fight;
		RightUpperType = RightType;
		break;
	}
}

FHitResult ASiAiPlayerController::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	FCollisionQueryParams TraceParams(true);
	TraceParams.AddIgnoredActor(SPCharacter);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, TraceParams))
	{
		// DrawRayLine(TraceStart, TraceEnd, 5.f);
	}
	return Hit;
}

void ASiAiPlayerController::DrawRayLine(FVector StartPos, FVector EndPos, float Duration)
{
	ULineBatchComponent *const LineBatcher = GetWorld()->PersistentLineBatcher;
	if (LineBatcher != nullptr)
	{
		float LineDuration = (Duration > 0.f) ? Duration : LineBatcher->DefaultLifeTime;
		LineBatcher->DrawLine(StartPos, EndPos, FLinearColor::Red, 10, 0.f, LineDuration);
	}
}

void ASiAiPlayerController::RunRayCast()
{
	FVector StartPos(0.f);
	FVector EndPos(0.f);

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		StartPos = SPCharacter->FirstCamera->K2_GetComponentLocation();
		EndPos = StartPos + SPCharacter->FirstCamera->GetForwardVector() * 2000.f;
		break;
	case EGameViewMode::Third:
		StartPos = SPCharacter->ThirdCamera->K2_GetComponentLocation();
		StartPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector() * 300.f;
		EndPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector() * 2000.f;
		break;
	}

	// 是否检测到物品
	bool IsDetected = false;
	FHitResult Hit = RayGetHitResult(StartPos, EndPos);
	RayActor = Hit.GetActor();

	if (Cast<ASiAiPickupObject>(RayActor))
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ASiAiPickupObject>(RayActor)->GetInfoText();
	}
	if (Cast<ASiAiResourceObject>(RayActor))
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ASiAiResourceObject>(RayActor)->GetInfoText();
	}

	// 如果什么都没有检测到那就设置信息为无
	if (!IsDetected) {
		SPState->RayInfoText = FText();
	}
}

void ASiAiPlayerController::StateMachine()
{
	//普通模式
	ChangePreUpperType(EUpperBody::None);
	if (!Cast<ASiAiResourceObject>(RayActor) && !Cast<ASiAiPickupObject>(RayActor)) {
		//准星显示未锁定
		UpdatePointer.ExecuteIfBound(false, 1.f);
	}
	//如果检测到资源
	if (Cast<ASiAiResourceObject>(RayActor)) {
		//如果左键没有按下,在资源模式下右键没有特殊意义
		if (!IsLeftButtonDown) {
			//准星锁定模式
			UpdatePointer.ExecuteIfBound(false, 0.f);
		}
		//如果左键已经按下
		if (IsLeftButtonDown && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) < SPState->GetAffectRange())
		{
			//获取实际伤害
			int Damage = SPState->GetDamageValue(Cast<ASiAiResourceObject>(RayActor)->GetResourceType());
			//让资源受到伤害并且获取剩余血量百分比
			float Range = Cast<ASiAiResourceObject>(RayActor)->TakeObjectDamage(Damage)->GetHPRange();
			//更新准星
			UpdatePointer.ExecuteIfBound(true, Range);
		}
	}
	//如果检测到可拾取物品,并且两者的距离小于300
	if (Cast<ASiAiPickupObject>(RayActor) && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) < 300.f)
	{
		//改变右键预状态为拾取
		ChangePreUpperType(EUpperBody::PickUp);
		//修改准星锁定模式
		UpdatePointer.ExecuteIfBound(false, 0);
		//如果右键按下
		if (IsRightButtonDown) {
			Cast<ASiAiPickupObject>(RayActor)->TakePickup();
		}
	}
}
