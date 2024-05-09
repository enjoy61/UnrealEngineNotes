// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGISubsystem.h"
#include "FirstRunnable.h"
#include "HAL/RunnableThread.h"
#include "Async/TaskGraphInterfaces.h"

void UFirstGISubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]FirstGISubsystem"), *FString(__FUNCTION__), __LINE__);

    // FRunnable
    auto Runnable = new FFirstRunnable();
    FRunnableThread *Thread = FRunnableThread::Create(Runnable, TEXT("FirstRunnable"));

    // FGraphEvent
    // Example 1
    /*
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread start"), *FString(__FUNCTION__), __LINE__);

    FGraphEventRef ATask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]A"), *FString(__FUNCTION__), __LINE__); }, TStatId(), nullptr,
        ENamedThreads::AnyThread);

    FGraphEventRef BTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]B"), *FString(__FUNCTION__), __LINE__); }, TStatId(), nullptr,
        ENamedThreads::AnyThread);

    FGraphEventRef CTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]C"), *FString(__FUNCTION__), __LINE__); }, TStatId(), nullptr,
        ENamedThreads::AnyThread);

    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread end"), *FString(__FUNCTION__), __LINE__);
    */

    // Example 2
    /*
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread start"), *FString(__FUNCTION__), __LINE__);

    FGraphEventRef ATask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]A"), *FString(__FUNCTION__), __LINE__); }, TStatId(), nullptr,
        ENamedThreads::AnyThread);

    FGraphEventRef BTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]B"), *FString(__FUNCTION__), __LINE__); }, TStatId(), ATask,
        ENamedThreads::AnyThread);

    FGraphEventRef CTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]C"), *FString(__FUNCTION__), __LINE__); }, TStatId(), ATask,
        ENamedThreads::AnyThread);

    FGraphEventArray TaskDependencies;
    TaskDependencies.Add(BTask);
    TaskDependencies.Add(CTask);

    FGraphEventRef DTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]D"), *FString(__FUNCTION__), __LINE__); }, TStatId(), &TaskDependencies,
        ENamedThreads::AnyThread);

    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread end"), *FString(__FUNCTION__), __LINE__);
    */

    // Example 3
    /*
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread start"), *FString(__FUNCTION__), __LINE__);

    FGraphEventRef ATask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]A"), *FString(__FUNCTION__), __LINE__); }, TStatId(), nullptr,
        ENamedThreads::AnyThread);

    FGraphEventRef BTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]B"), *FString(__FUNCTION__), __LINE__); }, TStatId(), ATask,
        ENamedThreads::AnyThread);

    FTaskGraphInterface::Get().WaitUntilTaskCompletes(BTask);

    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread end"), *FString(__FUNCTION__), __LINE__);
    */

    // FEvent
    /*
    FEvent *SyncEvent = FPlatformProcess::GetSynchEventFromPool();
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread start"), *FString(__FUNCTION__), __LINE__);

    FGraphEventRef ATask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]A"), *FString(__FUNCTION__), __LINE__); }, TStatId(), nullptr,
        ENamedThreads::AnyThread);

    FGraphEventRef BTask = FFunctionGraphTask::CreateAndDispatchWhenReady(
        [&]()
        {
            UE_LOG(LogTemp, Display, TEXT("[%s][%d]B"), *FString(__FUNCTION__), __LINE__);
            SyncEvent->Trigger();
        },
        TStatId(), ATask, ENamedThreads::AnyThread);

    SyncEvent->Wait();
    FPlatformProcess::ReturnSynchEventToPool(SyncEvent);

    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread end"), *FString(__FUNCTION__), __LINE__);
    */
}
