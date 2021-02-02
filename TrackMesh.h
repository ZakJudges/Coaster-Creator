#pragma once

#include "PipeMesh.h"
#include "MeshInstance.h"
#include "DefaultShader.h"
//#include "SplineMesh.h"
#include "CrossTieMesh.h"
#include "SupportMesh.h"
#include "../DXFramework/SphereMesh.h"
#include "../Spline-Library/vector.h"

//	each time the support structures are generated, the old ones should be discarded.
//	if undo is called, the support structures should be discarded.

//	Contains all components of the track's mesh. Responsible for mesh instance logic.
class TrackMesh
{
public:
	TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader);

	std::vector<MeshInstance*> GetTrackMeshInstances();
	inline bool HasNewInstances() { return update_instances_; }
	std::vector<MeshInstance*> GetInstancesForRemoval();
	bool InstancesPendingRemoval();
	std::vector<MeshInstance*> GetNewInstances();
	XMMATRIX GetWorldMatrix();
	void SetTranslation(float x, float y, float z);
	//SL::Vector GetTranslation();
	void StorePoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddSupportVertical(XMVECTOR from, XMVECTOR to);
	void AddSupportSegmented(XMVECTOR vertical_from_, XMVECTOR vertical_to_,
		XMVECTOR angled_from_, XMVECTOR angled_to_, XMVECTOR angled_x_, XMVECTOR angled_z_);
	//void AddSupportElbow(XMVECTOR location, XMVECTOR forward, XMVECTOR right);
	//void AddSupport(XMVECTOR from, XMVECTOR to, XMVECTOR forward, XMVECTOR up);
	void StorePreviewPoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void AddPreviewCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis);
	void UpdateSimulatingMesh();
	//void UpdateSupportMesh();
	//void UpdateBuildingMesh(SL::CRSplineController* spline_controller);
	void UpdatePreviewMesh();
	void SetPreviewActive(bool preview);
	void Clear();
	void ClearPreview();
	void ClearSupports();
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
	//PipeMesh* support_mesh_;
	
	//std::vector<MeshInstance*> rails_;
	std::vector<MeshInstance*> simulating_instances_;
	//std::vector<MeshInstance*> building_instances_;
	std::vector<MeshInstance*> preview_instances_;
	//SplineMesh* spline_mesh_;
	//SL::Vector translation_;

	ID3D11ShaderResourceView* small_rail_texture_;
	ID3D11ShaderResourceView* large_rail_texture_;
	ID3D11ShaderResourceView* cross_tie_texture_;

	BaseShader* shader_;

	ID3D11Device* device_;
	ID3D11DeviceContext* device_context_;

	std::vector<MeshInstance*> support_instances_;
	SphereMesh* sphere_mesh_;

	std::vector<MeshInstance*> instances_for_removal_;

	bool update_instances_;
};