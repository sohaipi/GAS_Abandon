// Copyright M9Only


#include "AbilitySystem/Data/B9CharacterClassInfo.h"

FCharacterClassDefaultInfo UB9CharacterClassInfo::FindCharacterClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInfo.FindChecked(CharacterClass);
}
