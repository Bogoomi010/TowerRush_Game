#pragma once

#include "NativeGameplayTags.h"

namespace TowerRushGameplayTags
{
	TOWERRUSH_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Gameplay Tags
	TOWERRUSH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_GodMode);
	TOWERRUSH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_UnlimitedHealth);
}