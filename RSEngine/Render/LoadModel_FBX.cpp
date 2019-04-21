/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: LoadModel_FBX.cpp

*/

#include <RSEngine.h>

#if USE_FBXSDK == 1
namespace rs {
    bool FbxLoader::Initialize() {
        if (g_pFbxSdkManager == nullptr) {
            g_pFbxSdkManager = FbxManager::Create();
            
            FbxIOSettings* pIOSettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT);
            g_pFbxSdkManager->SetIOSettings(pIOSettings);
        }
        else {
            //Already initialized
            return false;
        }
        return true;
    }
    
    bool FbxLoader::LoadFbxIntoBuffer(const char* filename, MeshData mesh) {
        // Create importer and scene
        FbxImporter* fImporter = FbxImporter::Create(g_pFbxSdkManager, "");
        FbxScene* fFbxScene = FbxScene::Create(g_pFbxSdkManager, "");
        
        // Either invalid file or improper format
        if (!fImporter->Initialize(filename, -1, g_pFbxSdkManager->GetIOSettings()))
            return false;
        if (!fImporter->Import(fFbxScene))
            return false;
        
        fImporter->Destroy();
        
        FbxNode* fFbxRootNode = fFbxScene->GetRootNode();
        if (fFbxRootNode) {
            for (int i = 0; i < fFbxRootNode->GetChildCount(); i++) {
                FbxNode* fFbxChildNode = fFbxRootNode->GetChild(i);
                
                if (fFbxChildNode->GetNodeAttribute() == NULL)
                    continue;
                
                FbxMesh* fMesh = (FbxMesh*)fFbxChildNode->GetNodeAttribute();
                FbxVector4* fVertices = fMesh->GetControlPoints();
                
                for (int j = 0; j < fMesh->GetPolygonCount(); j++) {
                    int iNumVertices = fMesh->GetPolygonSize(j);
                    assert(iNumVertices == 3);
                    for (int k = 0; k < iNumVertices; k++) {
                        int iControlPointIndex = fMesh->GetPolygonVertex(j, k);
                        
                        MeshData::vertex myVertex;
                        myVertex.vertexPosition[0] = (float)fVertices[iControlPointIndex].mData[0];
                        myVertex.vertexPosition[1] = (float)fVertices[iControlPointIndex].mData[1];
                        myVertex.vertexPosition[2] = (float)fVertices[iControlPointIndex].mData[2];

                        // Fill in false UV data for right now
                        myVertex.vertexColor[0] = 0.0f;
                        myVertex.vertexColor[1] = 0.0f;
                        myVertex.vertexColor[2] = 0.0f;
                        myVertex.vertexColor[3] = 0.0f;

                        mesh.vertexMap.push_back(myVertex);
                    }
                }

                fMesh->Destroy();
                fFbxChildNode->Destroy();
            }
        }
        
        fFbxRootNode->Destroy();
        fFbxScene->Destroy();
        
        return true;
    }
    
    void FbxLoader::Shutdown() {
        g_pFbxSdkManager->Destroy();
    }
    
} // namespace rs

#endif // USE_FBXSDK
