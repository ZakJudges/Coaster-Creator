#pragma once

#include "PipeMesh.h"
#include "MeshInstance.h"
#include "DefaultShader.h"
#include "SplineMesh.h"


//	Contains all components of the track's mesh. Responsible for mesh instance logic.
class TrackMesh
{
public:
	TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader);
	int GetInstanceCount();
	MeshInstance* GetMeshInstance(int element);
	void AddPipeMeshCircle(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis);
	void Update();
	void SetSimulatingState();
	void SetBuildingState();
	inline SplineMesh* GetSplineMesh() { return spline_mesh_; }	//TEMP.
	~TrackMesh();
private:
	std::vector<PipeMesh*> rail_meshes_;
	//std::vector<MeshInstance*> rails_;
	std::vector<MeshInstance*> simulating_instances_;
	std::vector<MeshInstance*> building_instances_;
	SplineMesh* spline_mesh_;
};