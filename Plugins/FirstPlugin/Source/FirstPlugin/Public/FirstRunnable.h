#pragma once

#include "HAL/Runnable.h"

class FIRSTPLUGIN_API FFirstRunnable : public FRunnable
{
public:
    FFirstRunnable() {}
    ~FFirstRunnable() {}

    virtual bool Init();
    virtual uint32 Run();
    virtual void Stop();
    virtual void Exit();
};