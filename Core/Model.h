#ifndef __MODEL_H__
#define __MODEL_H__

#include "Vector3.h"
#include "Matrix44.h"

class Batch;

class Model{
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;
    const Batch* m_Batch;

public:
    Model(const Batch* batch);
    virtual ~Model();

    void Draw(const Matrix44& matProjView) const;
    void SetPos(const Vector3& pos);
    void SetRotation(const Vector3& rot);
    void SetScale(const Vector3& scale);
};

#endif