// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGISubsystem.h"

void UFirstGISubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]FirstGISubsystem"), *FString(__FUNCTION__), __LINE__);
}
