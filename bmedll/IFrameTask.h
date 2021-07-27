#pragma once

class IFrameTask
{
public:
    virtual ~IFrameTask() {}
    virtual void RunFrame() = 0;
    virtual bool IsFinished() = 0;
};