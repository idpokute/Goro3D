#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Vector3.h"
#include "Matrix44.h"

class Camera {
    Vector3 m_Position;
    Vector3 m_Target;
    double m_NearClip;
    double m_FarClip;
    double m_FOV;

public:
    Camera();
    virtual ~Camera();

    void SetPos(const Vector3 pos);
    void SetTarget(const Vector3 target);
    void SetNearClip(double near);
    void SetFarClip(double far);
    void SetFov(double fov);

    const Vector3* Position() const;
    const Vector3* Target() const;
    double NearClip() const;
    double FarClip() const;
    double FOV() const;

    void CreateProjViewMatrix(Matrix44* out) const;
};

#endif