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
	inline PipeMesh* GetMesh() { return rail_mesh_; }	//TEMP.
	~TrackMesh();
private:
	PipeMesh* rail_mesh_;
	std::vector<MeshInstance*> rails_;
};