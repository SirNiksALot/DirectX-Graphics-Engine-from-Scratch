#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/ShaderBinary.h>

using namespace dx3d;

dx3d::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc):Base(desc.base)
{
	// ---------------------------------------Creating D3D11 Device --------------------------------------
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
	
	DX3DGraphicsLogThrowOnFail(hr, "D3D11CreateDevice Failed.");

	
	// ---------------------------------Initialization for Creating Swap chain ------------------------------------
	DX3DGraphicsLogThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface failed to retrieve IDXGI interface"
		);

	DX3DGraphicsLogThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGI Adapter"
	);

	DX3DGraphicsLogThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGI Factory"
	);

	
}


dx3d::GraphicsDevice::~GraphicsDevice()
{
}

SwapChainPtr dx3d::GraphicsDevice::createSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc,getGraphicsResourceDesc());
}

DeviceContextPtr dx3d::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

ShaderBinaryPtr dx3d::GraphicsDevice::compileShader(const ShaderCompileDesc& desc)
{
	return std::make_shared<ShaderBinary>(desc,getGraphicsResourceDesc());

}

void dx3d::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	//------------ STEP 1 : Get Command list from deffered context i.e. m_context<ID3D11DeviceContext> ---------------------
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list), // Extract command list from deffered context, and populate "list"
		"FinishCommandList Failed.");
    

	//------------ STEP 2 : Execute the command list using Immediate context i.e. m_d3dContext<ID3D11DeviceContext> ------------
	// We had initialized this context when we setup our D3D11 Device.
	// This "m_d3dContext" is the Immediate context responsible for executing Commands on GPU
	m_d3dContext->ExecuteCommandList(list.Get(),false);
}

GraphicsResourceDesc dx3d::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return { m_logger , shared_from_this() ,*m_d3dDevice.Get() , *m_dxgiFactory.Get()};
}
