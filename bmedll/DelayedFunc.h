#pragma once

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
		std::list<DelayedFunc> delayedFuncsToRunNow{};

		{
			// we will move pointers to functions that are supposed to run now into a separate std::list
			// and then release the mutex to avoid deadlocks
			std::lock_guard<std::recursive_mutex> l(m_lock);

			auto it = m_delayedFuncs.begin();
			while (it != m_delayedFuncs.end())
			{
				auto& delay = *it;
				delay.FramesTilRun = std::max(delay.FramesTilRun - 1, 0);
				if (delay.FramesTilRun == 0)
					// move the element from source list to target list
					delayedFuncsToRunNow.splice(delayedFuncsToRunNow.end(), m_delayedFuncs, it++);
				else
					++it;
			}
		}

		for (auto& delay : delayedFuncsToRunNow)
			delay.Func();
	}

	virtual bool IsFinished()
	{
		return false;
	}

	void AddFunc(const std::function<void()>& func, int frames)
	{
		std::lock_guard<std::recursive_mutex> l(m_lock);
		m_delayedFuncs.emplace_back(frames, func);
	}

private:
	std::recursive_mutex m_lock{};
	std::list<DelayedFunc> m_delayedFuncs{};
};
