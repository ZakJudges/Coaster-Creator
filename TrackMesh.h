#pragma once

#include "PipeMesh.h"
#include "MeshInstance.h"
#include "DefaultShader.h"



class TrackMesh
{
public:
	TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader);
	int GetInstanceCount();
	MeshInstance* GetMeshInstance(int element);
	void AddPipeMeshCircle(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis);
	void Update();
	~TrackMesh();
private:
	std::vector<PipeMesh*> rail_meshes_;
	std::vector<MeshInstance*> rails_;
};