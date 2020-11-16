#pragma once

#include "PipeMesh.h"
#include "MeshInstance.h"
#include "DefaultShader.h"
//#include "SplineMesh.h"
#include "CrossTieMesh.h"

#include "../Spline-Library/vector.h"


//	Contains all components of the track's mesh. Responsible for mesh instance logic.
class TrackMesh
{
public:
	TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader);

	std::vector<MeshInstance*> GetTrackMeshInstances();
	XMMATRIX GetWorldMatrix();
	void SetTranslation(float x, float y, float z);
	//SL::Vector GetTranslation();
	void StorePoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddSupport(XMVECTOR from, XMVECTOR to, XMVECTOR forward, XMVECTOR right, XMVECTOR up);
	void StorePreviewPoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddPreviewCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void UpdateSimulatingMesh();
	void UpdateSupportMesh();
	//void UpdateBuildingMesh(SL::CRSplineController* spline_controller);
	void UpdatePreviewMesh();
	void SetPreviewActive(bool preview);
	void Clear();
	void ClearPreview();
	void ClearSupport();
	unsigned int GetCrossTieFrequency();

	//	Texture:
	void SetSmallRailTexture(ID3D11ShaderResourceView* texture);
	void SetLargeRailTexture(ID3D11ShaderResourceView* texture);
	void SetCrossTieTexture(ID3D11ShaderResourceView* texture);
	//void SetSimulatingState();
	//void SetBuildingState();

	~TrackMesh();
private:
	std::vector<PipeMesh*> rail_meshes_;
	std::vector<CrossTieMesh*> cross_ties_meshes_;
	PipeMesh* support_mesh_;
	//std::vector<MeshInstance*> rails_;
	std::vector<MeshInstance*> simulating_instances_;
	//std::vector<MeshInstance*> building_instances_;
	std::vector<MeshInstance*> preview_instances_;
	//SplineMesh* spline_mesh_;
	//SL::Vector translation_;

	ID3D11ShaderResourceView* small_rail_texture_;
	ID3D11ShaderResourceView* large_rail_texture_;
	ID3D11ShaderResourceView* cross_tie_texture_;
};