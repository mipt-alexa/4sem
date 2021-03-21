#include <exception>
#include <stdexcept>
#include <thread>
#include <utility>

class Scoped_Thread
{
public:

	explicit Scoped_Thread(std::thread thread) :
		m_thread(std::move(thread))
	{
		if (!m_thread.joinable())
		{
			throw std::logic_error("No thread");
		}
	}

	Scoped_Thread			 (const Scoped_Thread &) = delete;

	Scoped_Thread & operator=(const Scoped_Thread &) = delete;

	~Scoped_Thread() noexcept
	{
		try
		{
			m_thread.join();
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::thread m_thread;
};

class F
{
public:

	explicit F(int & variable) noexcept:
		m_variable(variable) 
	{}

	void operator()() const noexcept
	{
		for (std::size_t i = 0; i < 1000000; ++i)
		{
			++m_variable;
		}
	}

	~F() noexcept = default;

private:

	int & m_variable;
};

#include <iostream>

void f(int x int y){
    std::cout << x+y;
}

int main(int argc, char ** argv)
{
	int local_variable = 42;

	Scoped_Thread thread{ std::thread(F(local_variable)) };

	std::thread(f, 1,2);

	std::ref(	        )

	// join -> OK

	// detach -> OK, but very dangerous

	// exception -> OK

	system("pause");

	return EXIT_SUCCESS;
}