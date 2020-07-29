// texture shader.cpp
#include "colourshader.h"


ColourShader::ColourShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"colour_vs.cso", L"colour_ps.cso");
	//SHADER_TYPE = SHADERTYPE::COLOUR;
	colour_ = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
}

ColourShader::~ColourShader()
{
	// Release the matrix constant buffer.
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	if (colour_buffer_)
	{
		colour_buffer_->Release();
		colour_buffer_ = 0;
	}

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	//Release base shader components
	BaseShader::~BaseShader();
}


void ColourShader::initShader(WCHAR* vsFilename, WCHAR* psFilename)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC colour_buffer_desc;

	
	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	colour_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	colour_buffer_desc.ByteWidth = sizeof(ColourBufferType);
	colour_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	colour_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	colour_buffer_desc.MiscFlags = 0;
	colour_buffer_desc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	renderer->CreateBuffer(&colour_buffer_desc, NULL, &colour_buffer_);
}


void ColourShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	ColourBufferType* colour_ptr;
	unsigned int bufferNumber;
	XMMATRIX tworld, tview, tproj;


	// Transpose the matrices to prepare them for the shader.
	tworld = XMMatrixTranspose(worldMatrix);
	tview = XMMatrixTranspose(viewMatrix);
	tproj = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	// Unlock the constant buffer.
	deviceContext->Unmap(matrixBuffer, 0);
	bufferNumber = 0;
	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrixBuffer);

	result = deviceContext->Map(colour_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);	// may need new D3D11_MAPPED_SUBRESOURCE
	colour_ptr = (ColourBufferType*)mappedResource.pData;
	colour_ptr->colour = colour_;
	colour_ptr->light_ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	colour_ptr->light_diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	colour_ptr->light_direction = XMFLOAT4(2.0f, -2.0f, 1.0f, 0.0f);
	deviceContext->Unmap(colour_buffer_, 0);
	deviceContext->PSSetConstantBuffers(0, 1, &colour_buffer_);

}

void ColourShader::SetTexture(ID3D11ShaderResourceView* texture)
{
	return;
}

void ColourShader::SetColour(float r, float g, float b)
{
	colour_ = XMFLOAT4(r, g, b, 0.0f);
}





