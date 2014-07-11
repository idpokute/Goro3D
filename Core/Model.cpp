#include "Model.h"
#include "Batch.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "Vector3.h"

Model::Model(const Batch* batch) : m_Batch(batch), m_Position(0,0,0), m_Rotation(0,0,0), m_Scale(1,1,1)
{
}

Model::~Model()
{
    m_Batch = 0;
}

void Model::Draw(const Matrix44& matProjView) const
{
    Matrix34 matWorld;
    matWorld.setTranslation(m_Position);
    matWorld.rotateY(m_Rotation.y);
    matWorld.rotateX(m_Rotation.x);
    matWorld.rotateZ(m_Rotation.z);
    matWorld.scale(m_Scale);
    
    Matrix44 transform;
    transform.setMul(matProjView,matWorld);
    m_Batch->Draw(transform);
}

void Model::SetPos(const Vector3& pos)
{
    m_Position = pos;
}

void Model::SetRotation(const Vector3& rot)
{
    m_Rotation = rot;
}

void Model::SetScale(const Vector3& scale)
{
    m_Scale = scale;
}