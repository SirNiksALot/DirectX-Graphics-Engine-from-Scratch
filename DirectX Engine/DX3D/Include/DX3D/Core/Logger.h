#pragma once
#include <DX3D/Core/Core.h>

namespace dx3d {
	class Logger
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

		void log(LogLevel logLevel, const char* message); // main function ⭐
		// The "const" here tels the compiler that this function doesn't alter the state of the class i.e. alter attributes or something


	private:
		LogLevel m_logLevel = LogLevel::Error;

	};


}
//Here 👇 logLevel "type" arg is in parenthesis to avoid unexpected behaviors , it doesn't mean anything else important


#define DX3DLog(logger,type,message)\
  logger.log((type),message)	


#define DX3DLogThrow(logger,exception,type,message)\
{\
DX3DLog(logger,type,message);\
throw exception(message);\
}

#define DX3DLogError(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Error, message)

#define DX3DLogInfo(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Info, message)


#define DX3DLogWarning(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Warning, message)

#define DX3DLogThrowError(message)\
	DX3DLogThrow(getLogger(),std::runtime_error,Logger::LogLevel::Error, message)

#define DX3DLogThrowInvalidArg(message)\
	DX3DLogThrow(getLogger(),std::invalid_argument ,Logger::LogLevel::Error, message)