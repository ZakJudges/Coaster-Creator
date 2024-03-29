#pragma once

#include "PipeMesh.h"
#include "MeshInstance.h"
#include "DefaultShader.h"
#include "CrossTieMesh.h"
#include "SupportMesh.h"
#include "../DXFramework/SphereMesh.h"
#include "../Spline-Library/vector.h"

//	Contains all components of the track's mesh. Responsible for mesh instance logic.
class TrackMesh
{
public:
	TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader, unsigned int max_segments = 20);
	std::vector<MeshInstance*> GetTrackMeshInstances();
	inline bool HasNewInstances() { return update_instances_; }
	inline unsigned int GetMaxSegments() { return max_segments_; }
	inline std::vector<MeshInstance*> GetInstancesForRemoval() { return instances_for_removal_; }
	void RemoveUnusedInstances();
	bool InstancesPendingRemoval();
	std::vector<MeshInstance*> GetNewInstances();
	XMMATRIX GetWorldMatrix();
	void SetTranslation(float x, float y, float z);
	void StorePoints(const XMVECTOR& centre, const XMVECTOR& x_axis, const XMVECTOR& y_axis, const XMVECTOR& z_axis);
	void AddCrossTie(const XMVECTOR& centre, const XMVECTOR& x_axis, const XMVECTOR& y_axis, const XMVECTOR& z_axis);
	void AddSupportVertical(const XMVECTOR& from, const XMVECTOR& to);
	void AddSupportSegmented(const XMVECTOR& vertical_from_, const XMVECTOR& vertical_to_,
		const XMVECTOR& angled_from_, const XMVECTOR& angled_to_, const XMVECTOR& angled_x_, const XMVECTOR& angled_z_);
	void StorePreviewPoints(const XMVECTOR& centre, const XMVECTOR& x_axis, const XMVECTOR& y_axis, const XMVECTOR& z_axis);
	void AddPreviewCrossTie(const XMVECTOR& centre, const XMVECTOR& x_axis, const XMVECTOR& y_axis, const XMVECTOR& z_axis);
	void UpdateSimulatingMesh();
	void UpdatePreviewMesh();
	void SetPreviewActive(bool preview);
	void Clear();
	void ClearPreview();
	void ClearSupports();
	unsigned int GetCrossTieFrequency();
	void SetSmallRailTexture(ID3D11ShaderResourceView* texture);
	void SetLargeRailTexture(ID3D11ShaderResourceView* texture);
	void SetCrossTieTexture(ID3D11ShaderResourceView* texture);
	~TrackMesh();
private:
	std::vector<PipeMesh*> rail_meshes_;
	std::vector<CrossTieMesh*> cross_ties_meshes_;
	std::vector<MeshInstance*> simulating_instances_;
	std::vector<MeshInstance*> preview_instances_;
	ID3D11ShaderResourceView* small_rail_texture_;
	ID3D11ShaderResourceView* large_rail_texture_;
	ID3D11ShaderResourceView* cross_tie_texture_;
	BaseShader* shader_;
	ID3D11Device* device_;
	ID3D11DeviceContext* device_context_;
	std::vector<MeshInstance*> support_instances_;
	std::vector<SupportMesh*> support_meshes_;
	SphereMesh* sphere_mesh_;
	std::vector<MeshInstance*> instances_for_removal_;
	bool update_instances_;
	unsigned int max_segments_;
	
};