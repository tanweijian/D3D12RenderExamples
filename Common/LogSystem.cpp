#include "LogSystem.h"

#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"

LogSystem::LogSystem()
{
	spdlog::init_thread_pool(8192, 1);

	std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	stdoutSink->set_level(spdlog::level::trace);
	stdoutSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");
	const spdlog::sinks_init_list sink_list = { stdoutSink };
	
	logger = std::make_shared<spdlog::async_logger>("LogSystem", sink_list.begin(), sink_list.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	logger->set_level(spdlog::level::trace);

	spdlog::details::registry::instance().register_logger(std::move(logger));
}

LogSystem::~LogSystem()
{
	logger->flush();
	spdlog::details::registry::instance().drop_all();
}
