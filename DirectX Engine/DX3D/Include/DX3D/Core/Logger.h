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
		void log(LogLevel logLevel, const char* message) const; // main function ⭐
		// The "const" here tels the compiler that this function doesn't alter the state of the class i.e. alter attributes or something


	private:
		LogLevel m_logLevel = LogLevel::Error;
	};

}
