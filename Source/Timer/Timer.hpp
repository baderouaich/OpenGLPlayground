#pragma once
#include <chrono>

// Basic Timer class
// Example: see how many ms took to execute a block of code
//	Timer timer;
//	timer.Start();
//	std::size_t N = 13;
//	for (std::size_t i = 1; i <= 1'000'000'000; ++i)
//	{
//		N = N ^ i;
//	}
//	auto ms_diff = timer.Stop<std::chrono::milliseconds>().count();
//	std::cout << "Code took " << ms_diff << " milliseconds to execute!\nN: " << N;
//
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void Start() noexcept
	{
		Restart();
	}

	void Restart() noexcept
	{
		m_start_time = std::chrono::steady_clock::now();
	}

	template<typename ChronoDuration>
	ChronoDuration Stop() noexcept
	{
		return std::chrono::duration_cast<ChronoDuration>(std::chrono::steady_clock::now() - m_start_time);
	}

private:
	std::chrono::steady_clock::time_point m_start_time{};
};
