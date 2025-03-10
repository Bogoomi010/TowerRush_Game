// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerRushAbilitySystemComponent.h"

UTowerRushAbilitySystemComponent::UTowerRushAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTowerRushAbilitySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//if (UTowerAbilitySystem* GlobalAbilitySystem = UWorld::GetSubsystem<UTowerAbilitySystem>(GetWorld()))
	//{
	//	GlobalAbilitySystem->UnregisterASC(this);
	//}

	Super::EndPlay(EndPlayReason);
}

void UTowerRushAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	FGameplayAbilityActorInfo* ActorInfo = AbilityActorInfo.Get();
	check(ActorInfo);
	check(InOwnerActor);

	const bool bHasNewPawnAvatar = Cast<APawn>(InAvatarActor) && (InAvatarActor != ActorInfo->AvatarActor);

	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	if (bHasNewPawnAvatar)
	{
		//// Notify all abilities that a new pawn avatar has been set
		//for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		//{
		//	ULyraGameplayAbility* LyraAbilityCDO = Cast<ULyraGameplayAbility>(AbilitySpec.Ability);
		//	if (!LyraAbilityCDO)
		//	{
		//		continue;
		//	}

		//	if (LyraAbilityCDO->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
		//	{
		//		TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
		//		for (UGameplayAbility* AbilityInstance : Instances)
		//		{
		//			ULyraGameplayAbility* LyraAbilityInstance = Cast<ULyraGameplayAbility>(AbilityInstance);
		//			if (LyraAbilityInstance)
		//			{
		//				// Ability instances may be missing for replays
		//				LyraAbilityInstance->OnPawnAvatarSet();
		//			}
		//		}
		//	}
		//	else
		//	{
		//		LyraAbilityCDO->OnPawnAvatarSet();
		//	}
		//}

		//// Register with the global system once we actually have a pawn avatar. We wait until this time since some globally-applied effects may require an avatar.
		//if (ULyraGlobalAbilitySystem* GlobalAbilitySystem = UWorld::GetSubsystem<ULyraGlobalAbilitySystem>(GetWorld()))
		//{
		//	GlobalAbilitySystem->RegisterASC(this);
		//}

		//if (ULyraAnimInstance* LyraAnimInst = Cast<ULyraAnimInstance>(ActorInfo->GetAnimInstance()))
		//{
		//	LyraAnimInst->InitializeWithAbilitySystem(this);
		//}

		//TryActivateAbilitiesOnSpawn();
	}
}
