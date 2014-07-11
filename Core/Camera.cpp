#include "GameLib\Framework.h"
#include "Camera.h"
#include "Matrix34.h"
using namespace GameLib;

Camera::Camera() : m_Position(0,0,1), m_Target(0,0,0), m_NearClip(5), m_FarClip(1000), m_FOV(60)
{
}

Camera::~Camera()
{
}

void Camera::SetPos(const Vector3 pos)
{
    m_Position = pos;
}

void Camera::SetTarget(const Vector3 target)
{
    m_Target = target;
}

void Camera::SetNearClip(double near) 
{
    m_NearClip = near;
}

void Camera::SetFarClip(double far)
{
    m_FarClip = far;
}
void Camera::SetFov(double fov)
{
    m_FOV = fov;
}

const Vector3* Camera::Position() const
{
    return &m_Position;
}
const Vector3* Camera::Target() const
{
    return &m_Target;
}
double Camera::NearClip() const
{
    return m_NearClip;
}
double Camera::FarClip() const
{
    return m_FarClip;
}
double Camera::FOV() const
{
    return m_FOV;
}

void Camera::CreateProjViewMatrix(Matrix44* out) const
{
    Framework f = Framework::instance();

    Matrix34 matView;
    matView.setViewTransform( m_Position, m_Target );

    // Projection Matrix
    out->setPerspectiveTransform( m_FOV, f.width(), f.height(), m_NearClip, m_FarClip );
    *out *= matView;       
}