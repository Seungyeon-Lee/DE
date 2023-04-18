#include "VECamera.h"

using namespace Venus;

VECamera::VECamera()
    : near(0.f)
    , far(0.f)
{
}

void VECamera::SetupViewMatrix(const VEVector3& pos,
    const VEVector3& targetPos,
    const VEVector3& worldUpDir)
{
    this->position = pos;

    VEVector3 forward = (targetPos - pos).Normalize();
    VEVector3 right = VEVector3::Cross(worldUpDir, forward).Normalize();
    VEVector3 up = VEVector3::Cross(forward, right);

    float x = VEVector3::Dot(-pos, right);
    float y = VEVector3::Dot(-pos, up);
    float z = VEVector3::Dot(-pos, forward);

    viewMatrix = {
        right.x, up.x, forward.x, 0.0f,
        right.y, up.y, forward.y, 0.0f,
        right.z, up.z, forward.z, 0.0f,
        x, y, z, 1.0f
    };
}

void VECamera::SetPerspective(float fov, float aspect, float near, float far)
{
    this->near = near;
    this->far = far;

    // reversed-Z projection matrix
    float f = 1.0f / tanf(fov / 2.0f);
    float scale = near / (near - far);
    float bias = -far * scale;
    projectionMatrix = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, scale, 1.0f,
        0.0f, 0.0f, bias, 0.0f
    };
}