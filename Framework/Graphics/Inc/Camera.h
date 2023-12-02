#pragma once

namespace CASTLEEngine::Graphics
{
    // This camera assumes YAxis as up direction. You
    // cannot look straight up nor straight down.
    class Camera
    {
    public:
        enum class ProjectionMode
        {
            Perspective,
            Orthographic
        };

        void SetMode(ProjectionMode mode);

        void SetPosition(const CEMath::Vector3& position);
        void SetDirection(const CEMath::Vector3& direction);
        void SetLookAt(const CEMath::Vector3& target);

        // Perspective params
        void SetFov(float fov);
        void SetAspectRatio(float ratio);

        // Orthographic params
        void SetSize(float width, float height);

        void SetNearPlane(float nearPlane);
        void SetFarPlane(float farPlane);

        // 3 degrees of freedom for translations
        void Walk(float distance);
        void Strafe(float distance);
        void Rise(float distance);

        // 2 degrees of freedom for rotations
        void Yaw(float radian);
        void Pitch(float radian);

        // 1 degree of freedom for field of view
        void Zoom(float amount);

        const CEMath::Vector3& GetPosition() const;
        const CEMath::Vector3& GetDirection() const;

        CEMath::Matrix4 GetViewMatrix() const;
        CEMath::Matrix4 GetProjectionMatrix() const;

        CEMath::Matrix4 GetPerspectiveMatrix() const;
        CEMath::Matrix4 GetOrthographicMatrix() const;

    private:
        ProjectionMode mProjectionMode = ProjectionMode::Perspective;

        CEMath::Vector3 mPosition = CEMath::Vector3::Zero;
        CEMath::Vector3 mDirection = CEMath::Vector3::ZAxis;

        // 0 aspect ratio = use back buffer dimension
        float mFov = 60.0f * CEMath::Constants::kDegToRad;
        float mAspectRatio = 0.0f;

        // 0 width or height = use back buffer dimension
        float mWidth = 0.0f;
        float mHeight = 0.0f;

        float mNearPlane = 0.01f;
        float mFarPlane = 10000.0f;
    };
}