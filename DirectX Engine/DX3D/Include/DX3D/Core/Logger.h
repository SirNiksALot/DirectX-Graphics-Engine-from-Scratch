#pragma once
#include <DX3D/Core/Core.h>
#include <format>
#include <stdarg.h>

namespace dx3d {
	class Logger final
	{
		dx3d_disable_copy_and_move(Logger);

	public:
		enum class LogLevel {
			Error = 0,
			Warning,
			Info
		};
		explicit Logger(LogLevel logLevel = LogLevel::Error); //default parameters to contructor

		~Logger();


		template<typename... Args>
		void log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
		{
			auto str = std::format(fmt, std::forward<Args>(args)...);
			_log(level,
				str.c_str()
			);
		}


	private:
		LogLevel m_logLevel = LogLevel::Error;
		void _log(LogLevel level, const char* message);
		// The "const" here tels the compiler that this function doesn't alter the state of the class i.e. alter attributes or something



	};


}
//Here 👇 logLevel "type" arg is in parenthesis to avoid unexpected behaviors , it doesn't mean anything else important


#define DX3DLog(logger,type,message, ... )\
  logger.log((type),{message} __VA_OPT__(,) __VA_ARGS__);	


#define DX3DLogThrow(logger,exception,type,message,...)\
{\
DX3DLog(logger,type,message, __VA_ARGS__)\
throw exception(message);\
}

#define DX3DLogError(message,...)\
	DX3DLog(getLogger(),Logger::LogLevel::Error,message, __VA_ARGS__)

#define DX3DLogInfo(message,...)\
	DX3DLog(getLogger(),Logger::LogLevel::Info, message, __VA_ARGS__)


#define DX3DLogWarning(message,...)\
	DX3DLog(getLogger(),Logger::LogLevel::Warning, message, __VA_ARGS__)

#define DX3DLogThrowError(message,...)\
	DX3DLogThrow(getLogger(),std::runtime_error,Logger::LogLevel::Error, message, __VA_ARGS__)

#define DX3DLogThrowInvalidArg(message,...)\
	DX3DLogThrow(getLogger(),std::invalid_argument ,Logger::LogLevel::Error, message, __VA_ARGS__)