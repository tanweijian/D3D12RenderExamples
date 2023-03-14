#pragma once

#include "spdlog/logger.h"

class LogSystem final
{
public:
	enum class LogLevel : uint8_t
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Critical
	};

public:
	LogSystem();
	~LogSystem();

	template<typename... TARGS>
	void Log(LogLevel level, TARGS&&... args)
	{
		switch (level)
		{
		case LogLevel::Trace:
			logger->trace(std::forward<TARGS>(args)...);
			break;
		case LogLevel::Debug:
			logger->debug(std::forward<TARGS>(args)...);
			break;
		case LogLevel::Info:
			logger->info(std::forward<TARGS>(args)...);
			break;
		case LogLevel::Warn:
			logger->warn(std::forward<TARGS>(args)...);
			break;
		case LogLevel::Error:
			logger->error(std::forward<TARGS>(args)...);
			break;
		case LogLevel::Critical:
			logger->critical(std::forward<TARGS>(args)...);
			break;
		default:
			break;
		}
	}

private:
	std::shared_ptr<spdlog::logger> logger;
};
