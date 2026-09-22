#pragma once
#include <DX3D/Core/Common.h>

namespace dx3d {
	class Base
	{
		dx3d_disable_copy_and_move(Base)

		public:
			explicit Base(const BaseDesc& desc); // we are injecting an "aggregated" object with all the required dependencies into the constructor . "Dependency aggregation" method for constructor
			virtual ~Base();
			virtual Logger& getLogger() noexcept final;


		protected:
			Logger& m_logger;

	};

}



