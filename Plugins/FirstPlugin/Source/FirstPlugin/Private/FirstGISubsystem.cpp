// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGISubsystem.h"
#include "FirstRunnable.h"
#include "HAL/RunnableThread.h"
#include "Async/TaskGraphInterfaces.h"
#include "Async/Async.h"

void UFirstGISubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]FirstGISubsystem"), *FString(__FUNCTION__), __LINE__);

    // FRunnable
    auto Runnable = new FFirstRunnable();
    FRunnableThread *Thread = FRunnableThread::Create(Runnable, TEXT("FirstRunnable"));

    // FGraphEvent
    // TestGraphTask();

    // FEvent
    // TestEvent();

    // AsyncTask
    // TestAsyncTask();

    // HTTP
    // TestHttp();
}

void UFirstGISubsystem::TestHttp()
{
    FString Token = TEXT("<token string>");

    FString Auth = FString::Printf(TEXT("Bearer %s"), *Token);
    FString Url = FString::Printf(TEXT("<url string>"));

    FHttpRequestRef Req = FHttpModule::Get().CreateRequest();
    Req->SetTimeout(1050);
    Req->SetURL(Url);
    Req->SetVerb(TEXT("GET"));
    Req->SetHeader(TEXT("Authorization"), Auth);

    // Req->SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy::CompleteOnHttpThread);
    // UE_LOG(LogTemp, Display, TEXT("On %s thread"),
    //       Req->GetDelegateThreadPolicy() == EHttpRequestDelegateThreadPolicy::CompleteOnHttpThread ? TEXT("http") : TEXT("game"));

    // Req->SetHeader(TEXT("content-Type"), TEXT("application/json"));

    // Req->OnProcessRequestComplete().BindUObject(this, &UFirstGISubsystem::OnHttpResponse);
    Req->OnProcessRequestComplete().BindLambda(
        [](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess && Response.IsValid())
            {
                int32 ResponseCode = Response->GetResponseCode();
                FString ResponseContent = Response->GetContentAsString();
                // TArray<uint8> ResponseContent = Response->GetContent();

                UE_LOG(LogTemp, Display, TEXT("[%s][%d]Response Content: %s"), *FString(__FUNCTION__), __LINE__, *ResponseContent);
            }
            else { UE_LOG(LogTemp, Warning, TEXT("[%s][%d]Invalid response"), *FString(__FUNCTION__), __LINE__); }
        });
    Req->ProcessRequest();
}

void UFirstGISubsystem::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess && Response.IsValid())
    {
        int32 ResponseCode = Response->GetResponseCode();
        FString ResponseContent = Response->GetContentAsString();
        // TArray<uint8> ResponseContent = Response->GetContent();

        UE_LOG(LogTemp, Display, TEXT("[%s][%d]Response Content: %s"), *FString(__FUNCTION__), __LINE__, *ResponseContent);
    }
    else { UE_LOG(LogTemp, Warning, TEXT("[%s][%d]Invalid response"), *FString(__FUNCTION__), __LINE__); }
}

void UFirstGISubsystem::TestGraphTask()
{
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
}

void UFirstGISubsystem::TestEvent()
{

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
}

void UFirstGISubsystem::TestAsyncTask()
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread start"), *FString(__FUNCTION__), __LINE__);

    AsyncTask(ENamedThreads::AnyThread, []() { UE_LOG(LogTemp, Display, TEXT("[%s][%d]ASyncTask"), *FString(__FUNCTION__), __LINE__); });

    UE_LOG(LogTemp, Display, TEXT("[%s][%d]In main thread end"), *FString(__FUNCTION__), __LINE__);
}