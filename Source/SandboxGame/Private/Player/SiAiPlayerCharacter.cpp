// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerCharacter.h"
#include "Engine/SkeletalMesh.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimInstance.h"
#include "SiAiHandObject.h"


// Sets default values
ASiAiPlayerCharacter::ASiAiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置人物碰撞
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));

	// 添加第一人称骨骼模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	MeshFirst->SetupAttachment(RootComponent);
	MeshFirst->bOnlyOwnerSee = true;
	MeshFirst->bCastDynamicShadow = false;
	MeshFirst->bReceivesDecals = false;
	// 更新频率衰落
	MeshFirst->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	MeshFirst->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	// 设置碰撞属性
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);
	// 设置位置
	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// 获取第一人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPlayer_Animation.FirstPlayer_Animation_C'"));
	MeshFirst->AnimClass = StaticAnimFirst.Class;
	
	// 给默认 Mesh 添加骨骼
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// 获取第三人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'"));
	GetMesh()->AnimClass = StaticAnimThird.Class;

	// 摄像机手臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// 设置距离
	CameraBoom->TargetArmLength = 300.f;
	// 设置偏移
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);
	// 绑定Controller的旋转
	CameraBoom->bUsePawnControlRotation = true;

	// 初始化第三人称摄像机
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// 设置ThirdCamera不跟随控制器的旋转
	ThirdCamera->bUsePawnControlRotation = false;

	// 初始化第一人称摄像机
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// 设置跟随Controller的旋转
	FirstCamera->bUsePawnControlRotation = true;
	// 设置偏移
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));

	// 实例化手上物品
	HandObject = CreateDefaultSubobject<UChildActorComponent>(TEXT("HandObject"));

	// 初始化参数
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	//设置初始速度为150.f
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	// 初始为第三人人称
	GameView = EGameViewMode::Third;
	// 析构函数运行时函数还没有解析完成，说以析构函数里不可以调用函数
	// ChangeView(GameView);
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);
	// 不显示第一人称模型
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);

	// 初始化动作为无动作
	UpperType = EUpperBody::None;
	// 是否允许切换视角
	IsAllowSwitch = true;

}

// Called when the game starts or when spawned
void ASiAiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 把手持物品组件绑定到第三人称模型右手插槽
	HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
	// 添加 Actor 到 HandObject
	HandObject->SetChildActorClass(ASiAiHandObject::SpawnHandObject(0));
}

// Called every frame
void ASiAiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASiAiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASiAiPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASiAiPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASiAiPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASiAiPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASiAiPlayerCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASiAiPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASiAiPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASiAiPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASiAiPlayerCharacter::OnStopRun);

}

void ASiAiPlayerCharacter::ChangeView(EGameViewMode::Type NewGameView)
{
	GameView = NewGameView;
	switch (GameView)
	{
	case EGameViewMode::First:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		GetMesh()->SetOwnerNoSee(true);
		MeshFirst->SetOwnerNoSee(false);
		//修改handobject绑定的位置
		HandObject->AttachToComponent(MeshFirst, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	case EGameViewMode::Third:
		// 默认第三人称
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		// 不显示第一人称模型
		GetMesh()->SetOwnerNoSee(false);
		MeshFirst->SetOwnerNoSee(true);
		//修改handobject绑定的位置
		HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	}
}

void ASiAiPlayerCharacter::ChangeHandObject(int32 Index)
{
	// 
	HandObject->SetChildActorClass(ASiAiHandObject::SpawnHandObject(Index));
}

void ASiAiPlayerCharacter::ChangeHandObjectDetect(bool IsOpen)
{
	ASiAiHandObject *HandObjectClass = Cast<ASiAiHandObject>(HandObject->GetChildActor());
	if (HandObjectClass) HandObjectClass->ChangeOverlayDetect(IsOpen);
}

void ASiAiPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.f && Controller) {
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASiAiPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0) {
		const FQuat Rotation = GetActorQuat();
		FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASiAiPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASiAiPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASiAiPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value *BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASiAiPlayerCharacter::OnStartJump()
{
	bPressedJump = true;
}

void ASiAiPlayerCharacter::OnStopJump()
{
	bPressedJump = false;
	StopJumping();
}

void ASiAiPlayerCharacter::OnStartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 375.f;
}

void ASiAiPlayerCharacter::OnStopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}