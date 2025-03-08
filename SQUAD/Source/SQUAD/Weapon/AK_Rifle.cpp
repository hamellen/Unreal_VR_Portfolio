// Fill out your copyright notice in the Description page of Project Settings.


#include "AK_Rifle.h"
#include "Components/BoxComponent.h"
#include "../Component/GrabComponent.h"
#include "../Animation//Rifle_Animinstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "../Player/Squad_Hand.h"
#include "../Util/SquadGameInstance.h"
#include "Magazine.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "../UMG/Gun_Ammo.h"
#include "Components/TextBlock.h"
#include "Bullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Animation/Hand_instance.h"
AAK_Rifle::AAK_Rifle()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Main_Sk(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SK_AR_01.SK_AR_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Grip(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Grip_01.SM_ATT_Grip_01'"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Scope(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Scope_02.SM_ATT_Scope_02'"));

	static ConstructorHelpers::FClassFinder<UUserWidget>Ammo_Class(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/Gun_Ammo_Count.Gun_Ammo_Count_C'"));

	static ConstructorHelpers::FClassFinder<ABullet>Bullet_Class(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Bullet.BP_Bullet_C'"));
	
	grip_socket = TEXT("Socket_Grip");
	magazine_socket = TEXT("Socket_Magazine");
	scope_socket = TEXT("Socket_Scope");
	muzzle_socket = TEXT("Socket_Muzzle");

	damage = 20.f;

	GrabComponent = CreateDefaultSubobject<UGrabComponent>(TEXT("GrabComponent"));
	main_part = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun_Main"));
	Magazine_box = CreateDefaultSubobject<UBoxComponent>(TEXT("Magazine_Collision"));
	GripBox= CreateDefaultSubobject<UBoxComponent>(TEXT("Grip_Collision"));

	Widget_Ammo = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_Ammo"));
	Widget_Ammo->SetDrawSize(FVector2D(10.f,5.f));
	Widget_Ammo->SetupAttachment(main_part);

	Magazine_box->SetupAttachment(main_part);
	GrabComponent->SetupAttachment(main_part);
	GripBox->SetupAttachment(main_part);
	
	if (Bullet_Class.Succeeded()) {
	
		BulletClass = Bullet_Class.Class;
	}


	if (Main_Sk.Succeeded()) {

		main_part->SetSkeletalMesh(Main_Sk.Object);
		
	}
	

	grip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip"));
	if (Grip.Succeeded()) {
	
		grip->SetStaticMesh(Grip.Object);
		grip->SetupAttachment(main_part, grip_socket);
	}


	

	scope = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scope"));
	if (Scope.Succeeded()) {

		scope->SetStaticMesh(Scope.Object);
		scope->SetupAttachment(main_part, scope_socket);
	}

	if (Ammo_Class.Succeeded()) {
	
		Ammo_UMG_Class = Ammo_Class.Class;
		Widget_Ammo->SetWidgetClass(Ammo_Class.Class);
		Widget_Ammo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Widget_Ammo->SetWidgetSpace(EWidgetSpace::World);
	}

	
	
}

void AAK_Rifle::BeginPlay()
{
	Super::BeginPlay();
	Gun_Animinstance = Cast<URifle_Animinstance>(main_part->GetAnimInstance());
	current_ammo = max_ammo;
	GrabComponent->grabtrigger.AddUObject(this, &AAK_Rifle::Weapon_Fire);
	Squad_Instance = Cast<USquadGameInstance>(GetWorld()->GetGameInstance());
	
	Magazine_box->OnComponentBeginOverlap.AddDynamic(this, &AAK_Rifle::OnOverlapBegin);
	GripBox->OnComponentBeginOverlap.AddDynamic(this, &AAK_Rifle::OnOverlapHandBegin);
	GripBox->OnComponentEndOverlap.AddDynamic(this, &AAK_Rifle::OnEndHandOverlap);

	//
	Ammo_UMG = Cast<UGun_Ammo>(Widget_Ammo->GetWidget());
	
	Ammo_UMG->Ammo->Text= FText::Format(FText::FromString("{0}/{1}"),FText::AsNumber(current_ammo), FText::AsNumber(max_ammo));
}

void AAK_Rifle::Weapon_Fire()
{
	current_ammo--;
	current_ammo = FMath::Clamp(current_ammo, 0, max_ammo);
	Ammo_UMG->Ammo->Text = FText::Format(FText::FromString("{0}/{1}"), FText::AsNumber(current_ammo), FText::AsNumber(max_ammo));
	Magazine_Position = main_part->GetSocketLocation(magazine_socket);
	
	if (Magazine_Object) {
		
		if (current_ammo > 0) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Current Ammo : %d"),current_ammo));
			gun_muzzle_location = main_part->GetSocketLocation(muzzle_socket);
			gun_muzzle_rotation = main_part->GetSocketRotation(muzzle_socket);
			UGameplayStatics::PlaySoundAtLocation(this, *Squad_Instance->Map_Cue.Find(TEXT("Gun_Fire")), gun_muzzle_location);//소리재생
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), *Squad_Instance->Map_Vfx.Find("Muzzle_Vfx"), gun_muzzle_location, gun_muzzle_rotation);
			GetWorld()->SpawnActor<ABullet>(BulletClass, gun_muzzle_location, gun_muzzle_rotation);
		}
		else if (current_ammo == 0) {

			
			UGameplayStatics::PlaySoundAtLocation(this, *Squad_Instance->Map_Cue.Find(TEXT("Gun_Magazine_Out")), Magazine_Position);
			Gun_Animinstance->Montage_Play(*Squad_Instance->Map_Montage.Find(TEXT("Gun_Fire")));
			Magazine_Object->Magazine_Out();
			Magazine_Object = nullptr;
		}
	
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Location (%f %f %f)"), gun_muzzle_location.X, gun_muzzle_location.Y, gun_muzzle_location.Z));

}

void AAK_Rifle::Reload_Ammo()
{
	
	current_ammo = max_ammo;
	Ammo_UMG->Ammo->Text = FText::Format(FText::FromString("{0}/{1}"), FText::AsNumber(current_ammo), FText::AsNumber(max_ammo));
	Magazine_Position = main_part->GetSocketLocation(magazine_socket);
	UGameplayStatics::PlaySoundAtLocation(this, *Squad_Instance->Map_Cue.Find(TEXT("Gun_Magazine_In")), Magazine_Position);
}



void AAK_Rifle::OnOverlapHandBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASquad_Hand::StaticClass())) {

		auto hand = Cast<ASquad_Hand>(OtherActor);
		if (hand->hand_tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("VR.HAND.LEFT"))) {
			Vertical_Left = hand;

			Vertical_Left->hand_mesh->AttachToComponent(GripBox, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Vertical_Left->hand_mesh->SetRelativeLocationAndRotation(FVector(0,0,0),FRotator(90,90,0));
			Vertical_Left->hand_instance->Pose_Index = -50;
		}

	}

}

void AAK_Rifle::OnEndHandOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->IsA(ASquad_Hand::StaticClass())) {

		auto hand = Cast<ASquad_Hand>(OtherActor);
		if (hand->hand_tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("VR.HAND.LEFT"))) {
			if (Vertical_Left) {

				Vertical_Left->ResetHandMesh();
				Vertical_Left = nullptr;
			}
		}

	}
	
	
}



void AAK_Rifle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Magazine Reload")));

	if (OtherActor->IsA(AMagazine::StaticClass())) {
		
		OtherActor->AttachToComponent(Magazine_box, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Magazine_Object = Cast<AMagazine>(OtherActor);
		Magazine_Object->Magazine_In();
		Magazine_Object->Magazine->SetCollisionProfileName(TEXT("NoCollision"));
		Reload_Ammo();
	}

}


