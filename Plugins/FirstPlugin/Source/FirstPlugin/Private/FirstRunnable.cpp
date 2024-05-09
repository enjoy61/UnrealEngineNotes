#include "FirstRunnable.h"

bool FFirstRunnable::Init()
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]Init FirstRunnable"), *FString(__FUNCTION__), __LINE__);
    return true;
}

uint32 FFirstRunnable::Run()
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]Put work here"), *FString(__FUNCTION__), __LINE__);
    return 0;
}

void FFirstRunnable::Stop()
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]Called only when received signal"), *FString(__FUNCTION__), __LINE__);
}

void FFirstRunnable::Exit()
{
    UE_LOG(LogTemp, Display, TEXT("[%s][%d]After run finished"), *FString(__FUNCTION__), __LINE__);
}