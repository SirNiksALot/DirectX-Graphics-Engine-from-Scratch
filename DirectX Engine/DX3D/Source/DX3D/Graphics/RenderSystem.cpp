#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
using namespace dx3d;

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc):Base(desc.base)
{
	// -----------------------------Creating D3D11 Device --------------------------------------
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // bitwise or operator to sent this flag 
#endif // _DEBUG

	auto hr  = D3D11CreateDevice(
		NULL, // IDXGI Adapter ( represents GPU installed on the system ) .
		D3D_DRIVER_TYPE_HARDWARE, // This combined with the NULL as IDXGI Adap. selects the default primary GPU
		NULL, // handle to custom software rasterizer ( which we wont be doing ) 
		createDeviceFlags, // flags
		NULL,// pointer to an array of feature level ( by setting NULL Dx3D will pick the best feature level supported by the system
		0, // size of the previous ( feature level ) array . 0 since we passed NULL
		D3D11_SDK_VERSION, // SDK version : safety check by microsfot to prevent version mismatches
		&m_d3dDevice, // ⭐ The D3D11 "Device" double pointer . The device helps us create and manage GPU resources
		&featureLevel, // Feature level
		&m_d3dContext // ⭐ The D3D11 "Device Context"
	);
	
	DX3DGraphicsLogErrorAndThrow(hr, "D3D11CreateDevice Failed.");

	
	// ---------------------------------Initialization for Creating Swap chain ------------------------------------
	DX3DGraphicsLogErrorAndThrow(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface failed to retrieve IDXGI interface"
		);

	DX3DGraphicsLogErrorAndThrow(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGI Adapter"
	);

	DX3DGraphicsLogErrorAndThrow(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGI Factory"
	);

	
}


dx3d::RenderSystem::~RenderSystem()
{
}

SwapChainPtr dx3d::RenderSystem::createSwapChain(const SwapChainDesc& desc)
{
	return std::make_shared<SwapChain>(desc,getGraphicsResourceDesc());
}

GraphicsResourceDesc dx3d::RenderSystem::getGraphicsResourceDesc()
{
	return {m_logger , *m_d3dDevice.Get() , *m_dxgiFactory.Get()};
}
