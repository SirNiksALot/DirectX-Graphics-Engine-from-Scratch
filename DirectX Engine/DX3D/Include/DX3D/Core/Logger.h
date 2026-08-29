#pragma once
namespace dx3d {
	class Logger
	{
	public:
		enum class LogLevel {
			Error = 0,
			Warning,
			Info
		};
		explicit Logger(LogLevel logLevel = LogLevel::Error); //default parameters to contructor
		
		~Logger();

		void log(LogLevel logLevel, const char* message) ; // main function ⭐
		// The "const" here tels the compiler that this function doesn't alter the state of the class i.e. alter attributes or something


	private:
		LogLevel m_logLevel = LogLevel::Error;

	protected:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator = (const Logger&) = delete;
		Logger& operator = (Logger&&) = delete;
	};

#define DX3DLogError(message)\
	getLogger().log((Logger::LogLevel::Error), message ); 
// logLevel arg is in parenthesis to avoid unexpected behaviors , it doesn't mean anything else important

#define DX3DLogInfo(message)\
	getLogger().log((Logger::LogLevel::Info), message ); 

#define DX3DLogWarning(message)\
	getLogger().log((Logger::LogLevel::Warning), message ); 


#define DX3DLogErrorAndThrowException(message)\
	 {\
	DX3DLogError(message) ;\
	throw std::runtime_error(message);\
	}

}
