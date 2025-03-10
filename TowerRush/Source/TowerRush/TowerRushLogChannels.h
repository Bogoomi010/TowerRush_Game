// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Logging/LogMacros.h"

class UObject;

TOWERRUSH_API DECLARE_LOG_CATEGORY_EXTERN(LogTowerRush, Log, All);
TOWERRUSH_API DECLARE_LOG_CATEGORY_EXTERN(LogTowerRushExperience, Log, All);
TOWERRUSH_API DECLARE_LOG_CATEGORY_EXTERN(LogTowerRushAbilitySystem, Log, All);
TOWERRUSH_API DECLARE_LOG_CATEGORY_EXTERN(LogTowerRushTeams, Log, All);

TOWERRUSH_API FString GetClientServerContextString(UObject* ContextObject = nullptr);
