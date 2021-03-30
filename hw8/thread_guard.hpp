#include <thread>

class Thread_Guard
{
public:

	explicit Thread_Guard(std::thread & thread) noexcept :
		m_thread(thread)
	{}


	Thread_Guard			(const Thread_Guard &) = delete;

	Thread_Guard & operator=(const Thread_Guard &) = delete;

	~Thread_Guard() noexcept
	{
		try
		{
			if (m_thread.joinable())
			{
				m_thread.join();
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::thread & m_thread;
};


