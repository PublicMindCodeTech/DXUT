//-----------------------------------------------------------------------------
// File: DXUTMesh.h
//
// Desc: Support code for loading DirectX .X files.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

namespace_DXUT

//-----------------------------------------------------------------------------
// Name: class CDXUTMesh
// Desc: Class for loading and rendering file-based meshes
//-----------------------------------------------------------------------------
class DXUTAPI CDXUTMesh
{
public:
	WCHAR                   m_strName[512];

	LPD3DXMESH              m_pSysMemMesh;    // SysMem mesh, lives through resize
	LPD3DXMESH              m_pLocalMesh;     // Local mesh, rebuilt on resize

	DWORD                   m_dwNumMaterials; // Materials for the mesh
	D3DMATERIAL9*           m_pMaterials;
	ID3D11Resource**		m_pTextures;
	bool                    m_bUseMaterials;

public:
	// Rendering
	HRESULT Render(ID3D11DeviceContext* pd3dDeviceContext,
		bool bDrawOpaqueSubsets = true,
		bool bDrawAlphaSubsets = true);
	HRESULT Render(ID3DX11Effect *pEffect,
		D3DXHANDLE hTexture = nullptr,
		D3DXHANDLE hDiffuse = nullptr,
		D3DXHANDLE hAmbient = nullptr,
		D3DXHANDLE hSpecular = nullptr,
		D3DXHANDLE hEmissive = nullptr,
		D3DXHANDLE hPower = nullptr,
		bool bDrawOpaqueSubsets = true,
		bool bDrawAlphaSubsets = true);

	// Mesh access
	LPD3DXMESH GetSysMemMesh() { return m_pSysMemMesh; }
	LPD3DXMESH GetLocalMesh()  { return m_pLocalMesh; }

	// Rendering options
	void    UseMeshMaterials(bool bFlag) { m_bUseMaterials = bFlag; }
	HRESULT SetFVF(ID3D11Device* pd3dDevice, DWORD dwFVF);
	HRESULT SetVertexDecl(ID3D11Device* pd3dDevice, const D3DVERTEXELEMENT9 *pDecl);

	// Initializing
	HRESULT RestoreDeviceObjects(ID3D11Device* pd3dDevice);
	HRESULT InvalidateDeviceObjects();

	// Creation/destruction
	HRESULT Create(ID3D11Device* pd3dDevice, LPCWSTR strFilename);
	HRESULT Create(ID3D11Device* pd3dDevice, LPD3DXFILEDATA pFileData);
	HRESULT CreateMaterials(LPCWSTR strPath, ID3D11Device *pd3dDevice, ID3D11Buffer *pAdjacencyBuffer, ID3D11Buffer *pMtrlBuffer);
	HRESULT Destroy();

	CDXUTMesh(LPCWSTR strName = L"CDXUTMeshFile_Mesh");
	virtual ~CDXUTMesh();
};

//-----------------------------------------------------------------------------
// Name: class CDXUTMeshFrame
// Desc: Class for loading and rendering file-based meshes
//-----------------------------------------------------------------------------
class DXUTAPI CDXUTMeshFrame
{
public:
	WCHAR		m_strName[512];
	XMMATRIX	m_mat;
	CDXUTMesh*  m_pMesh;

	CDXUTMeshFrame* m_pNext;
	CDXUTMeshFrame* m_pChild;

public:
	// Matrix access
	void      SetMatrix(XMMATRIX* pmat) { m_mat = *pmat; }
	XMMATRIX* GetMatrix()               { return &m_mat; }

	CDXUTMesh*		FindMesh(LPCWSTR strMeshName);
	CDXUTMeshFrame*	FindFrame(LPCWSTR strFrameName);
	bool			EnumMeshes(bool(*EnumMeshCB)(CDXUTMesh*, void*), void* pContext);

	HRESULT Destroy();
	HRESULT RestoreDeviceObjects(ID3D11Device* pd3dDevice);
	HRESULT InvalidateDeviceObjects();
	HRESULT Render(ID3D11Device* pd3dDevice, bool bDrawOpaqueSubsets = true, bool bDrawAlphaSubsets = true, XMMATRIX* pmatWorldMatrix = nullptr);

	CDXUTMeshFrame(LPCWSTR strName = L"CDXUTMeshFile_Frame");
	virtual ~CDXUTMeshFrame();
};

//-----------------------------------------------------------------------------
// Name: class CDXUTMeshFile
// Desc: Class for loading and rendering file-based meshes
//-----------------------------------------------------------------------------
class DXUTAPI CDXUTMeshFile : public CDXUTMeshFrame
{
	HRESULT LoadMesh(ID3D11Device* pd3dDevice, LPD3DXFILEDATA pFileData,
	CDXUTMeshFrame* pParentFrame);
	HRESULT LoadFrame(ID3D11Device* pd3dDevice, LPD3DXFILEDATA pFileData,
		CDXUTMeshFrame* pParentFrame);
public:
	HRESULT Create(ID3D11Device* pd3dDevice, LPCWSTR strFilename);
	HRESULT CreateFromResource(ID3D11Device* pd3dDevice, LPCWSTR strResource, LPCWSTR strType);
	// For pure devices, specify the world transform. If the world transform is not
	// specified on pure devices, this function will fail.
	HRESULT Render(ID3D11Device* pd3dDevice, FXMMATRIX* pmatWorldMatrix = nullptr);

	CDXUTMeshFile() : CDXUTMeshFrame(L"CDXUTMeshFile_Root") {}
};

namespace_DXUT_end

#ifdef __cplusplus
EXTERN_CC_END
#endif
