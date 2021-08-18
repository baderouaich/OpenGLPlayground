#pragma once
#include <chrono>
#include <functional>
#include <thread>
#include <atomic>

// Calls a function at a specified interval (similar to setInterval in Javascript)
// it will continue calling the function until Stop() is called or it goes out of scope
// Example: print "Hello World" every 3 seconds:
// 	IntervalTimer timer(std::chrono::seconds(3), []()
//		{
//			std::cout << "Hello World\n";
//		});
//	timer.Start(); // start the timer
//	std::cin.get(); // timer stops when goes out of scope, 
//	timer.Stop(); // stop the timer
// 
//	Note: timer will be stopped when goes out of scope.

class IntervalTimer
{
public:
	IntervalTimer()
		:
		m_running(false),
		m_thread(nullptr),
		m_start_time(std::chrono::steady_clock::time_point::min()),
		m_end_time(std::chrono::steady_clock::time_point::min()),
		m_function(nullptr),
		m_duration(0)
	{

	}
	IntervalTimer(const std::chrono::steady_clock::duration& duration, const std::function<void()>& func)
		:
		m_running(false),
		m_thread(nullptr),
		m_start_time(std::chrono::steady_clock::time_point::min()),
		m_end_time(std::chrono::steady_clock::time_point::min()),
		m_function(func),
		m_duration(duration)
	{
	}

	void Start()
	{
		m_running = true;
		m_thread.reset(new std::thread([this]()
			{
				m_function(); // first run, then run each interval. (to avoid first delay
				m_start_time = std::chrono::steady_clock::now();
				while (m_running.load(std::memory_order::relaxed))
				{
					m_end_time = std::chrono::steady_clock::now();
					if (std::chrono::duration_cast<decltype(m_duration)>(m_end_time - m_start_time) >= m_duration)
					{
						m_function();
						m_start_time = m_end_time;
					}
				}
			}));
	}

	void Stop()
	{
		if (m_running)
		{
			m_running = false;
			if(m_thread->joinable())
				m_thread->join();
		}
	}

	bool IsRunning() const noexcept
	{
		return m_running.load(std::memory_order::relaxed);
	}

	~IntervalTimer()
	{
		this->Stop();
	}

private:
	std::atomic<bool> m_running{}; // < to stop, start timer thread
	std::unique_ptr<std::thread> m_thread{}; // < worker thread
	std::chrono::steady_clock::time_point m_start_time{}, m_end_time{}; // < to calculate interval, using sleep will be a problem when interval is long and we want to stop the timer immediately..
	std::function<void()> m_function{}; // < work function
	std::chrono::steady_clock::duration m_duration{}; // < interval duration
};