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


//Here 👇 logLevel "type" arg is in parenthesis to avoid unexpected behaviors , it doesn't mean anything else important


#define DX3DLog(logger,type,message)\
logger.log((type),message)	


#define DX3DLogThrow(logger,exception,type,message)\
{\
DX3DLog(logger,type,message);\
throw exception(message);\	
}