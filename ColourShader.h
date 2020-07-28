// Colour shader.h
// Simple shader example.
#ifndef _COLOURSHADER_H_
#define _COLOURSHADER_H_

#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;

struct ColourBufferType
{
	XMFLOAT4 colour;
};

class ColourShader : public BaseShader
{
private:
	

public:

	ColourShader(ID3D11Device* device, HWND hwnd);
	~ColourShader();

	virtual void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetColour(float r, float g, float b);

private:
	void initShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* colour_buffer_;
	XMFLOAT4 colour_;

};

#endif