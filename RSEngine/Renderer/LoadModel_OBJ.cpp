/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: LoadModel_OBJ.cpp

*/

#include <Renderer/LoadModel_OBJ.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <Renderer/tiny_obj_loader.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace rs {

    bool ObjLoader::LoadModel(MeshData* meshData, const char* filename) {
        Assimp::Importer imp;

        unsigned int NumMeshes;

        const aiScene* pScene = imp.ReadFile(filename,
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_SplitLargeMeshes |
            aiProcess_ConvertToLeftHanded |
            aiProcess_SortByPType |
            aiProcess_PreTransformVertices);

        if (pScene == NULL)
            return false;

        NumMeshes = pScene->mNumMeshes;

        for (unsigned int i = 0; i < NumMeshes; i++)
        {
            aiMesh* mesh = pScene->mMeshes[i];

            for (unsigned int j = 0; j < mesh->mNumVertices; j++)
            {
                rs::vertex vertexData;

                vertexData.position.x = mesh->mVertices[j].x;
                vertexData.position.y = mesh->mVertices[j].y;
                vertexData.position.z = mesh->mVertices[j].z;

                vertexData.normal.x = mesh->mNormals[j].x;
                vertexData.normal.y = mesh->mNormals[j].y;
                vertexData.normal.z = mesh->mNormals[j].z;

                if (mesh->HasTextureCoords(0))
                {
                    vertexData.texCoord.u = mesh->mTextureCoords[0][j].x;
                    vertexData.texCoord.v = mesh->mTextureCoords[0][j].y;
                }

                meshData->vertexMap.push_back(vertexData);
            }

            for (unsigned int c = 0; c < mesh->mNumFaces; c++)
                for (unsigned int e = 0; e < mesh->mFaces[c].mNumIndices; e++)
                    meshData->vertexIndices.push_back(mesh->mFaces[c].mIndices[e]);

        }

        return true;

    }

} // namespace rs
