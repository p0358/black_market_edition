#pragma once
#include "pch.h"
#include "IFrameTask.h"

struct DelayedFunc
{
    int FramesTilRun;
    std::function<void()> Func;
    DelayedFunc(int frames, std::function<void()> func) : FramesTilRun(frames), Func(func) {}
};

class DelayedFuncTask : public IFrameTask
{
public:
    virtual ~DelayedFuncTask() {}
    virtual void RunFrame()
    {
        std::lock_guard<std::recursive_mutex> l(m_lock);

        for (auto& delay : m_delayedFuncs)
        {
            delay.FramesTilRun = std::max(delay.FramesTilRun - 1, 0);
            if (delay.FramesTilRun == 0)
            {
                delay.Func();
            }
        }

        auto newEnd = std::remove_if(m_delayedFuncs.begin(), m_delayedFuncs.end(), [](const DelayedFunc& delay)
            {
                return delay.FramesTilRun == 0;
            });
        m_delayedFuncs.erase(newEnd, m_delayedFuncs.end());
    }

    virtual bool IsFinished()
    {
        return false;
    }

    void AddFunc(std::function<void()> func, int frames)
    {
        std::lock_guard<std::recursive_mutex> l(m_lock);
        m_delayedFuncs.emplace_back(frames, func);
    }

private:
    std::recursive_mutex m_lock;
    std::list<DelayedFunc> m_delayedFuncs;
};