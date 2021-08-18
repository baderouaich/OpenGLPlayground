#pragma once
#include <chrono>
#include <functional>
#include <thread>
#include <atomic>

// Calls a function afer a specific interval (similar to setTimeout in Javascript)
// Example: call "Hello World" after 3 seconds from starting the timer:
// 	TimeoutTimer timer(std::chrono::seconds(3), []()
//		{
//			std::cout << "Hello World\n";
//		});
//	timer.Start(); // start the timer
// 
// Note: timer will be canceled when goes out of scope

class TimeoutTimer
{
public:
	TimeoutTimer()
		:
		m_running(false),
		m_thread(nullptr),
		m_function(nullptr),
		m_duration(0)
	{}

	TimeoutTimer(const std::chrono::steady_clock::duration& duration, const std::function<void()>& func)
		:
		m_running(false),
		m_thread(nullptr),	
		m_function(func),
		m_duration(duration)
	{}


	void Start()
	{
		m_running = true;
		m_thread.reset(new std::thread([this]()
			{
				auto start_time = std::chrono::steady_clock::now();
				while (m_running.load(std::memory_order::relaxed))
				{
					auto end_time = std::chrono::steady_clock::now();
					if (std::chrono::duration_cast<decltype(m_duration)>(end_time - start_time) >= m_duration)
					{
						// time is up! execute the function
						m_function();
						m_running = false; // exit
						break;
					}
					else // not yet, keep waiting...
					{
						std::this_thread::yield();
					}
					// void yield () noexcept; Yield to other threads The calling
					// thread yields, offering the implementation the opportunity
					// to reschedule. This function shall be called when a thread waits for other threads to advance without blocking.
				}

			}));
	}


	~TimeoutTimer()
	{
		m_running = false;
		if (m_thread->joinable())
			m_thread->join();
	}

private:
	std::atomic<bool> m_running{}; // < to see if its still running when goes out of scope
	std::unique_ptr<std::thread> m_thread{}; // < worker thread
	std::function<void()> m_function{}; // < work function
	std::chrono::steady_clock::duration m_duration{}; // < interval duration to wait until calling work function

	// Todo: try another impl with condition_variable and unique lock
	//std::condition_variable m_cv{};
	//std::mutex m_mutex{};
	//std::unique_lock<std::mutex> m_lock{ m_mutex };

};