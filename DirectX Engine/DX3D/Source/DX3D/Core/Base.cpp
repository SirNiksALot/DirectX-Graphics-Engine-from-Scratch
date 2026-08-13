#include <DX3D/Core/Base.h>
using namespace dx3d;

dx3d::Base::Base(const BaseDesc& desc):m_logger(desc.logger)
{

}

dx3d::Base::~Base()
{
}

Logger& dx3d::Base::getLogger() const noexcept
{
	return m_logger;
}
