// Copyright M9Only


#include "B9AssetManager.h"
#include "B9GameplayTags.h"

UB9AssetManager& UB9AssetManager::Get()
{
	check(GEngine);
	UB9AssetManager* B9AssetManager =  Cast<UB9AssetManager>(GEngine->AssetManager.Get());
	return *B9AssetManager;
}

void UB9AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FB9GameplayTags::InitializeNativeGameplayTags();
}
