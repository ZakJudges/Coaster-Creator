#pragma once

#include "PipeMesh.h"
#include "MeshInstance.h"
#include "DefaultShader.h"
#include "SplineMesh.h"
#include "CrossTieMesh.h"


//	Contains all components of the track's mesh. Responsible for mesh instance logic.
class TrackMesh
{
public:
	TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader);
	int GetInstanceCount();
	MeshInstance* GetMeshInstance(int element);
	void StorePoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void UpdateSimulatingMesh();
	void UpdateBuildingMesh(SL::CRSplineController* spline_controller);
	void Clear();
	void SetSimulatingState();
	void SetBuildingState();
	unsigned int GetCrossTieFrequency();
	inline SplineMesh* GetSplineMesh() { return spline_mesh_; }	//TEMP.
	~TrackMesh();
private:
	std::vector<PipeMesh*> rail_meshes_;
	CrossTieMesh* cross_ties_mesh_;
	//std::vector<MeshInstance*> rails_;
	std::vector<MeshInstance*> simulating_instances_;
	std::vector<MeshInstance*> building_instances_;
	SplineMesh* spline_mesh_;
};