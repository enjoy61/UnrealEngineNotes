// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HTTP.h"
#include "FirstGISubsystem.generated.h"

/**
 *
 */

UCLASS()
class FIRSTPLUGIN_API UFirstGISubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    void TestGraphTask();

    void TestEvent();

    void TestAsyncTask();

    void TestHttp();

    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
};
