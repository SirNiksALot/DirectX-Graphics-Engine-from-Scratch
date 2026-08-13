#include <DX3D/Core/Logger.h>
#include <iostream>

dx3d::Logger::Logger(LogLevel logLevel):m_logLevel(logLevel)
{
}

void dx3d::Logger::log(LogLevel level, const char* message) const
{
	auto logLevelToString = [](LogLevel logLevel) {
		switch (logLevel) {
			case LogLevel::Error: return "Error";
			case LogLevel::Warning: return "Warning";
			case LogLevel::Info: return "Info";
			default: return "Uknown";
		}
		};
	if (level > m_logLevel) return;

	std::clog << "[DX3D " << logLevelToString(level) << "]: " << message << "\n";

}
