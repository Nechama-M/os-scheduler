#include <unistd.h>
#include "scheduler.h"

/* ------------------- Auxiliary Functions -------------------*/

inline bool Scheduler::shouldRun() const
{
	return !m_queueTask.empty();
}

inline void Scheduler::handleNextTask(SharedPtr<ITask>& task)
{
    	task->run();
    	m_queueTask.pop();

    	if (task->getNextRunPeriod())
    	{
        	m_queueTask.push(task);
    	}
}

inline void waitForNextTask(size_t timeToSleep)
{
	usleep(timeToSleep);
}

/* ------------------- End Auxiliary Functions ---------------*/


void Scheduler::run()
{
	while (shouldRun())
    	{
        	SharedPtr<ITask> task = m_queueTask.top();
		
		if (task->getNextRunPeriod() > Time::now().getMilliseconds())
		{
			waitForNextTask(task->getNextRunPeriod() - Time::now().getMilliseconds());
		}

        	handleNextTask(task);
    	}
}



