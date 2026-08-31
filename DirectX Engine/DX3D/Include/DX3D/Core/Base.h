#pragma once
#include <DX3D/Core/Common.h>

namespace dx3d {
	class Base
	{
		public:
			explicit Base(const BaseDesc& desc); // we are injecting an "aggregated" object with all the required dependencies into the constructor . "Dependency aggregation" method for constructor
			virtual ~Base();
			virtual Logger& getLogger() noexcept final;

	protected:
		Base(const Base&) = delete;
		Base(Base&&) = delete;
		Base& operator = (const Base&) = delete;
		Base& operator = (Base&&) = delete;

	protected:
		Logger& m_logger;

	};

}

#define DX3DLogError(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Error, message)

#define DX3DLogInfo(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Info, message)


#define DX3DLogWarning(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Warning, message)

#define DX3DLogThrowError(message)\
	DX3DLogThrow(getLogger(),std::runtime_error,Logger::LogLevel::Error, message)



