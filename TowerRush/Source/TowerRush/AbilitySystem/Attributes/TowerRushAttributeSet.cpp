// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerRushAttributeSet.h"
#include "AbilitySystem/TowerRushAbilitySystemComponent.h"

UTowerRushAttributeSet::UTowerRushAttributeSet()
{
}

UWorld* UTowerRushAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UTowerRushAbilitySystemComponent* UTowerRushAttributeSet::GetTowerRushAbilitySystemComponent() const
{
	return Cast<UTowerRushAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
