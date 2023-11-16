#include "Graphics/Graphics.h"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <Math/Math.h>
#include <cmath>
#include <rcamera.h>

namespace Tabby {

void Graphics::DrawSprite(Matrix mat, Texture2D texture, Rectangle source, Vector3 position, Vector3 rotation, Vector3 origin, Vector2 size, Color tint)
{
    rlPushMatrix();

    // apply just the rotation
    rlMultMatrixf(MatrixToFloat(mat));

    // translate backwards in the inverse rotated matrix to put the item where it goes in world space
    position = Vector3Transform(position, MatrixInvert(mat));
    rlTranslatef(position.x, position.y, position.z);
    rlTranslatef(-origin.x, -origin.y, -origin.z);

    float width = size.x / 2;
    float height = size.y / 2;

    Color color = WHITE;

    rlCheckRenderBatchLimit(16);

    rlSetTexture(texture.id);

    // draw quad
    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer

    rlTexCoord2f((float)source.x / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(-width, -height, 0); // Bottom Left Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(+width, -height, 0); // Bottom Right Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)source.y / texture.height);
    rlVertex3f(+width, +height, 0); // Top Right Of The Texture and Quad

    rlTexCoord2f((float)source.x / texture.width, (float)source.y / texture.height);
    rlVertex3f(-width, +height, 0); // Top Left Of The Texture and Quad

    rlEnd();
    rlSetTexture(0);

    rlPopMatrix();
}

void Graphics::Draw3DBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint)
{
    rlPushMatrix();

    // get the camera view matrix
    Matrix mat = MatrixInvert(MatrixLookAt(camera.position, camera.target, camera.up));

    std::cout << mat.m0 << "  " << mat.m1 << "  " << mat.m2 << "  " << mat.m3 << "\n"
              << mat.m4 << "  " << mat.m5 << "  " << mat.m6 << "  " << mat.m7 << " \n "
              << mat.m8 << "  " << mat.m9 << "  " << mat.m10 << "  " << mat.m11 << " \n "
              << mat.m12 << "  " << mat.m13 << "  " << mat.m14 << "  " << mat.m15 << " \n "
              << "\n";

    // peel off just the rotation
    Quaternion quat = QuaternionFromMatrix(mat);
    mat = QuaternionToMatrix(quat);

    // apply just the rotation
    rlMultMatrixf(MatrixToFloat(mat));

    // translate backwards in the inverse rotated matrix to put the item where it goes in world space
    position = Vector3Transform(position, MatrixInvert(mat));
    rlTranslatef(position.x, position.y, position.z);

    // draw the billboard
    float width = size.x / 2;
    float height = size.y / 2;

    Color color = WHITE;

    rlCheckRenderBatchLimit(6);

    rlSetTexture(texture.id);

    // draw quad
    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer

    rlTexCoord2f((float)source.x / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(-width, -height, 0); // Bottom Left Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(+width, -height, 0); // Bottom Right Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)source.y / texture.height);
    rlVertex3f(+width, +height, 0); // Top Right Of The Texture and Quad

    rlTexCoord2f((float)source.x / texture.width, (float)source.y / texture.height);
    rlVertex3f(-width, +height, 0); // Top Left Of The Texture and Quad

    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();
}

// bool Graphics::IsSphereInFrustum(Camera Camera, Vector3 Position, float Radius)
// {
//
//     Matrix viewMatrix = GetCameraViewMatrix(&Camera);
//     Matrix projectionMatrix = GetCameraProjectionMatrix(&Camera, GetScreenWidth() / GetScreenHeight());
//
//     Vector3 sphereCenterCameraSpace = Vector3Transform(Position, viewMatrix);
//
//     Vector3 sphereCenterClipSpace = Vector3Transform(sphereCenterCameraSpace, projectionMatrix);
//
//     float depthFactor = sphereCenterCameraSpace.z / RL_CULL_DISTANCE_FAR;
//
//     bool isInsideFrustum = (sphereCenterClipSpace.z + Radius >= -1.0f) && (sphereCenterClipSpace.z - Radius <= 1.0f) && (sphereCenterClipSpace.x + Radius >= -1.0f) && (sphereCenterClipSpace.x - Radius <= 1.0f) && (sphereCenterClipSpace.y + Radius >= -1.0f) && (sphereCenterClipSpace.y - Radius <= 1.0f);
//
//     // bool isInsideFrustum = (sphereCenterClipSpace.z - Radius * depthFactor >= -1.0f) && (sphereCenterClipSpace.z + Radius * depthFactor <= 1.0f) && (sphereCenterClipSpace.x - Radius * depthFactor >= -1.0f) && (sphereCenterClipSpace.x + Radius * depthFactor <= 1.0f) && (sphereCenterClipSpace.y - Radius * depthFactor >= -1.0f) && (sphereCenterClipSpace.y + Radius * depthFactor <= 1.0f);
//
//     return isInsideFrustum;
// }

// bool IsBoundingBoxInFrustum(BoundingBox box, Matrix viewProjection)
// {
//     Vector3 corners[8];
//
//     // Get corners of the bounding box
//     corners[0] = (Vector3) { box.min.x, box.min.y, box.min.z };
//     corners[1] = (Vector3) { box.max.x, box.min.y, box.min.z };
//     corners[2] = (Vector3) { box.min.x, box.max.y, box.min.z };
//     corners[3] = (Vector3) { box.max.x, box.max.y, box.min.z };
//     corners[4] = (Vector3) { box.min.x, box.min.y, box.max.z };
//     corners[5] = (Vector3) { box.max.x, box.min.y, box.max.z };
//     corners[6] = (Vector3) { box.min.x, box.max.y, box.max.z };
//     corners[7] = (Vector3) { box.max.x, box.max.y, box.max.z };
//
//     // Check if any corner is inside the frustum
//     for (int i = 0; i < 8; i++) {
//         Vector3 transformedCorner = Vector3Transform(corners[i], viewProjection);
//         if (transformedCorner.z > -transformedCorner.w) {
//             // The corner is inside the frustum
//             return true;
//         }
//     }
//
//     // No corners are inside the frustum
//     return false;
// }

// bool Graphics::IsSphereInFrustum(Camera Camera, Vector3 Position, float Radius)
// {
//
//     Matrix viewMatrix = GetCameraViewMatrix(&Camera);
//     // Matrix viewMatrix = GetCameraProjectionMatrix(&Camera, GetScreenWidth() / GetScreenHeight());
//
//     float frustumPlanes[6][4];
//     // Right plane
//     frustumPlanes[0][0] = viewMatrix.m3 + viewMatrix.m0;
//     frustumPlanes[0][1] = viewMatrix.m7 + viewMatrix.m4;
//     frustumPlanes[0][2] = viewMatrix.m11 + viewMatrix.m8;
//     frustumPlanes[0][3] = viewMatrix.m15 + viewMatrix.m12;
//
//     // Left plane
//     frustumPlanes[1][0] = viewMatrix.m3 - viewMatrix.m0;
//     frustumPlanes[1][1] = viewMatrix.m7 - viewMatrix.m4;
//     frustumPlanes[1][2] = viewMatrix.m11 - viewMatrix.m8;
//     frustumPlanes[1][3] = viewMatrix.m15 - viewMatrix.m12;
//
//     // Top plane
//     frustumPlanes[2][0] = viewMatrix.m3 - viewMatrix.m1;
//     frustumPlanes[2][1] = viewMatrix.m7 - viewMatrix.m5;
//     frustumPlanes[2][2] = viewMatrix.m11 - viewMatrix.m9;
//     frustumPlanes[2][3] = viewMatrix.m15 - viewMatrix.m13;
//
//     // Bottom plane
//     frustumPlanes[3][0] = viewMatrix.m3 + viewMatrix.m1;
//     frustumPlanes[3][1] = viewMatrix.m7 + viewMatrix.m5;
//     frustumPlanes[3][2] = viewMatrix.m11 + viewMatrix.m9;
//     frustumPlanes[3][3] = viewMatrix.m15 + viewMatrix.m13;
//
//     // Near plane
//     frustumPlanes[4][0] = viewMatrix.m3 + viewMatrix.m2;
//     frustumPlanes[4][1] = viewMatrix.m7 + viewMatrix.m6;
//     frustumPlanes[4][2] = viewMatrix.m11 + viewMatrix.m10;
//     frustumPlanes[4][3] = viewMatrix.m15 + viewMatrix.m14;
//
//     // Far plane
//     frustumPlanes[5][0] = viewMatrix.m3 - viewMatrix.m2;
//     frustumPlanes[5][1] = viewMatrix.m7 - viewMatrix.m6;
//     frustumPlanes[5][2] = viewMatrix.m11 - viewMatrix.m10;
//     frustumPlanes[5][3] = viewMatrix.m15 - viewMatrix.m14;
//
//     for (int i = 0; i < 6; i++) {
//
//         // float distance = frustumPlanes[i][5] * Position.x + frustumPlanes[i][1] * Position.y + frustumPlanes[i][2] * Position.z + frustumPlanes[i][3];
//         float distance = frustumPlanes[i][0] * Position.x + frustumPlanes[i][1] * Position.y + frustumPlanes[i][2] * Position.z + frustumPlanes[i][3];
//
//         std::cout << "Distance: " << distance << "  Radius: " << Radius << "\n";
//         if (distance < -Radius || distance > RL_CULL_DISTANCE_FAR + Radius) {
//             return false; // Sphere is entirely behind or in front of this plane
//         }
//     }
//     return true; // Sphere is inside or intersects all planes
// }

// Frustum createFrustumFromCamera(const Camera& cam, float aspect, float fovY,
//     float zNear, float zFar)
// {
//     Frustum frustum;
//     const float halfVSide = zFar * tanf(fovY * .5f);
//     const float halfHSide = halfVSide * aspect;
//     const glm::vec3 frontMultFar = zFar * cam.Front;
//
//     frustum.nearFace = { cam.Position + zNear * cam.Front, cam.Front };
//     frustum.farFace = { cam.Position + frontMultFar, -cam.Front };
//     frustum.rightFace = { cam.Position,
//         glm::cross(frontMultFar - cam.Right * halfHSide, cam.Up) };
//     frustum.leftFace = { cam.Position,
//         glm::cross(cam.Up, frontMultFar + cam.Right * halfHSide) };
//     frustum.topFace = { cam.Position,
//         glm::cross(cam.Right, frontMultFar - cam.Up * halfVSide) };
//     frustum.bottomFace = { cam.Position,
//         glm::cross(frontMultFar + cam.Up * halfVSide, cam.Right) };
//
//     return frustum;
// }

void NormalizePlane(Vector4* plane)
{
    if (plane == NULL)
        return;

    float magnitude = sqrtf(plane->x * plane->x + plane->y * plane->y + plane->z * plane->z);

    plane->x /= magnitude;
    plane->y /= magnitude;
    plane->z /= magnitude;
    plane->w /= magnitude;
}

float DistanceToPlane(const Vector4* plane, const Vector3* position)
{
    return (plane->x * position->x + plane->y * position->y + plane->z * position->z + plane->w);
}

// float DistanceToPlane(const Vector4* plane, float x, float y, float z)
// {
//     return (plane->x * x + plane->y * y + plane->z * z + plane->w);
// }

bool PointInFrustum(Frustum* frustum, Vector3 position)
{
    if (frustum == NULL)
        return false;

    for (int i = 0; i < 6; i++) {
        if (DistanceToPlane(&frustum->Planes[i], &position) <= 0) // point is behind plane
            return false;
    }

    return true;
}

void Graphics::ExtractFrustum(Frustum* frustum)
{
    if (frustum == NULL)
        return;

    Matrix projection = rlGetMatrixProjection();
    Matrix modelview = rlGetMatrixModelview();

    Matrix planes = { 0 };

    planes.m0 = modelview.m0 * projection.m0 + modelview.m1 * projection.m4 + modelview.m2 * projection.m8 + modelview.m3 * projection.m12;
    planes.m1 = modelview.m0 * projection.m1 + modelview.m1 * projection.m5 + modelview.m2 * projection.m9 + modelview.m3 * projection.m13;
    planes.m2 = modelview.m0 * projection.m2 + modelview.m1 * projection.m6 + modelview.m2 * projection.m10 + modelview.m3 * projection.m14;
    planes.m3 = modelview.m0 * projection.m3 + modelview.m1 * projection.m7 + modelview.m2 * projection.m11 + modelview.m3 * projection.m15;
    planes.m4 = modelview.m4 * projection.m0 + modelview.m5 * projection.m4 + modelview.m6 * projection.m8 + modelview.m7 * projection.m12;
    planes.m5 = modelview.m4 * projection.m1 + modelview.m5 * projection.m5 + modelview.m6 * projection.m9 + modelview.m7 * projection.m13;
    planes.m6 = modelview.m4 * projection.m2 + modelview.m5 * projection.m6 + modelview.m6 * projection.m10 + modelview.m7 * projection.m14;
    planes.m7 = modelview.m4 * projection.m3 + modelview.m5 * projection.m7 + modelview.m6 * projection.m11 + modelview.m7 * projection.m15;
    planes.m8 = modelview.m8 * projection.m0 + modelview.m9 * projection.m4 + modelview.m10 * projection.m8 + modelview.m11 * projection.m12;
    planes.m9 = modelview.m8 * projection.m1 + modelview.m9 * projection.m5 + modelview.m10 * projection.m9 + modelview.m11 * projection.m13;
    planes.m10 = modelview.m8 * projection.m2 + modelview.m9 * projection.m6 + modelview.m10 * projection.m10 + modelview.m11 * projection.m14;
    planes.m11 = modelview.m8 * projection.m3 + modelview.m9 * projection.m7 + modelview.m10 * projection.m11 + modelview.m11 * projection.m15;
    planes.m12 = modelview.m12 * projection.m0 + modelview.m13 * projection.m4 + modelview.m14 * projection.m8 + modelview.m15 * projection.m12;
    planes.m13 = modelview.m12 * projection.m1 + modelview.m13 * projection.m5 + modelview.m14 * projection.m9 + modelview.m15 * projection.m13;
    planes.m14 = modelview.m12 * projection.m2 + modelview.m13 * projection.m6 + modelview.m14 * projection.m10 + modelview.m15 * projection.m14;
    planes.m15 = modelview.m12 * projection.m3 + modelview.m13 * projection.m7 + modelview.m14 * projection.m11 + modelview.m15 * projection.m15;

    frustum->Planes[Right] = (Vector4) { planes.m3 - planes.m0, planes.m7 - planes.m4, planes.m11 - planes.m8, planes.m15 - planes.m12 };
    NormalizePlane(&frustum->Planes[Right]);

    frustum->Planes[Left] = (Vector4) { planes.m3 + planes.m0, planes.m7 + planes.m4, planes.m11 + planes.m8, planes.m15 + planes.m12 };
    NormalizePlane(&frustum->Planes[Left]);

    frustum->Planes[Top] = (Vector4) { planes.m3 - planes.m1, planes.m7 - planes.m5, planes.m11 - planes.m9, planes.m15 - planes.m13 };
    NormalizePlane(&frustum->Planes[Top]);

    frustum->Planes[Bottom] = (Vector4) { planes.m3 + planes.m1, planes.m7 + planes.m5, planes.m11 + planes.m9, planes.m15 + planes.m13 };
    NormalizePlane(&frustum->Planes[Bottom]);

    frustum->Planes[Back] = (Vector4) { planes.m3 - planes.m2, planes.m7 - planes.m6, planes.m11 - planes.m10, planes.m15 - planes.m14 };
    NormalizePlane(&frustum->Planes[Back]);

    frustum->Planes[Front] = (Vector4) { planes.m3 + planes.m2, planes.m7 + planes.m6, planes.m11 + planes.m10, planes.m15 + planes.m14 };
    NormalizePlane(&frustum->Planes[Front]);
}

bool SphereInFrustum(Frustum* frustum, Vector3 position, float radius)
{
    if (frustum == NULL)
        return false;

    for (int i = 0; i < 6; i++) {
        if (DistanceToPlane(&frustum->Planes[i], &position) < -radius) // center is behind plane by more than the radius
            return false;
    }

    return true;
}

bool AABBoxInFrustum(Frustum* frustum, Vector3 min, Vector3 max)
{
    // if any point is in and we are good
    if (PointInFrustum(frustum, min))
        return true;

    if (PointInFrustum(frustum, min))
        return true;

    if (PointInFrustum(frustum, max))
        return true;

    if (PointInFrustum(frustum, max))
        return true;

    if (PointInFrustum(frustum, min))
        return true;

    if (PointInFrustum(frustum, min))
        return true;

    if (PointInFrustum(frustum, max))
        return true;

    if (PointInFrustum(frustum, max))
        return true;

    // check to see if all points are outside of any one plane, if so the entire box is outside
    for (int i = 0; i < 6; i++) {
        bool oneInside = false;

        if (DistanceToPlane(&frustum->Planes[i], &min) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (DistanceToPlane(&frustum->Planes[i], &max) >= 0)
            oneInside = true;

        if (!oneInside)
            return false;
    }

    // the box extends outside the frustum but crosses it
    return true;
}

bool Graphics::IsSphereInFrustum(Camera cam, Vector3 center, float size)
{

    Frustum frustum;

    ExtractFrustum(&frustum);

    return SphereInFrustum(&frustum, center, size);
    // Matrix viewProjection = MatrixTranspose(MatrixMultiply(rlGetMatrixModelview(), MatrixTranspose(rlGetMatrixProjection())));
    //
    // Frustum frustum;
    // const float halfVSide = RL_CULL_DISTANCE_FAR * tanf(camera.fovy * 0.5f);
    // const float halfHSide = halfVSide * GetScreenWidth() / GetScreenHeight();
    //
    // Vector3 direction = Vector3Subtract(cam.target, cam.position);
    // Vector3 front = Vector3Normalize(direction);
    //
    // Vector3 frontMultFar = Vector3Scale(cam.front, RL_CULL_DISTANCE_FAR);
    //
    // frustum.nearFace = { Vector3Add(cam.position, Vector3Scale(front, RL_CULL_DISTANCE_NEAR)), front };
    // frustum.farFace = { Vector3Add(cam.position, frontMultFar), Vector3Negate(front) };
    // frustum.rightFace = { cam.position, Vector3CrossProduct(Vector3Subtract(frontMultFar, Vector3Scale(cam.right, halfHSide)), cam.up) };
    // frustum.leftFace = { cam.position, Vector3CrossProduct(cam.up, Vector3Add(frontMultFar, Vector3Scale(cam.right, halfHSide))) };
    // frustum.topFace = { cam.position, Vector3CrossProduct(cam.right, Vector3Subtract(frontMultFar, Vector3Scale(cam.up, halfVSide))) };
    // frustum.bottomFace = { cam.position, Vector3CrossProduct(Vector3Add(frontMultFar, Vector3Scale(cam.up, halfVSide)), cam.right) };
    //
    // return frustum;
}

// bool Graphics::IsSphereInFrustum(Camera camera, Vector3 center, float size)
// {
//
//     Matrix view = GetCameraViewMatrix(&camera);
//     // // Transform the sphere center by the view and projection matrices
//     // Vector3 transformedCenter = Tabby::Math::Vector3Transform(view, center);
//     // Vector2 projectionCenter = { transformedCenter.x / transformedCenter.z, transformedCenter.y / transformedCenter.z };
//     //
//     // // Perspective divide for normalized device coordinates
//     // float scaledRadius = radius / transformedCenter.z;
//     //
//     // // Check against the frustum planes
//     // if (projectionCenter.x + scaledRadius < -1.0f || projectionCenter.x - scaledRadius > 1.0f || projectionCenter.y + scaledRadius < -1.0f || projectionCenter.y - scaledRadius > 1.0f) {
//     //     return false; // Outside the frustum
//     // }
//     //
//     // return true; // Inside the frustum
//     //
//     // Transform each corner of the bounding box by the view and projection matrices
//
//     BoundingBox box = {
//         { center.x - size, center.y - size, center.z - size },
//         { center.x + size, center.y + size, center.z + size }
//     };
//
//     Vector3 corners[8] = {
//         Vector3Transform({ box.min.x, box.min.y, box.min.z }, view),
//         Vector3Transform({ box.min.x, box.min.y, box.max.z }, view),
//         Vector3Transform({ box.min.x, box.max.y, box.min.z }, view),
//         Vector3Transform({ box.min.x, box.max.y, box.max.z }, view),
//         Vector3Transform({ box.max.x, box.min.y, box.min.z }, view),
//         Vector3Transform({ box.max.x, box.min.y, box.max.z }, view),
//         Vector3Transform({ box.max.x, box.max.y, box.min.z }, view),
//         Vector3Transform({ box.max.x, box.max.y, box.max.z }, view),
//     };
//
//     // Check if any corner is inside the frustum
//     for (int i = 0; i < 8; ++i) {
//         // Perspective divide for normalized device coordinates
//         corners[i].x /= corners[i].z;
//         corners[i].y /= corners[i].z;
//
//         // Check against the frustum planes
//         if (corners[i].x < -1.0f || corners[i].x > 1.0f || corners[i].y < -1.0f || corners[i].y > 1.0f) {
//             return false; // Outside the frustum
//         }
//     }
//
//     return true; // Inside the frustum
// }

// void Graphics::TransformCamera(Camera camera, int mode, Vector3 position, Vector3 rotation)
// {
//
//     camera.position = (Vector3) { 2.5f, 2.5f, 3.0f }; // Camera position
//
//     camera.target = (Vector3) { 0.0f, 0.0f, 0.0f }; // Camera looking at point
//
//     camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
//
//     camera.fovy = 65.0f; // Camera field-of-view Y
//
//     camera.projection = CAMERA_PERSPECTIVE; // Camera mode type
//
//     Vector3 direction;
//
//     Vector3 cameraFront;
//
//     Vector3 cameraRight;
//
//     Vector3 cameraUp;
//
//     // this is where magik happened
//
//     float pitch = -0.6; // mouseDelta y
//
//     float yaw = -2.45; // mouseDelta x
//
//     direction.x = cos(yaw) * cos(pitch);
//
//     direction.y = sin(pitch);
//
//     direction.z = sin(yaw) * cos(pitch);
//
//     cameraFront = Vector3Normalize(direction);
//
//     cameraRight = Vector3Normalize(Vector3CrossProduct(camera.up, cameraFront));
//
//     cameraUp = Vector3CrossProduct(direction, cameraRight);
//
//     camera.target = Vector3Add(camera.position, cameraFront);
//
//     // end of magik
//
//     float deltaTime = GetFrameTime();
//
//     if (IsKeyDown(KEY_W)) {
//
//         camera.position = Vector3Add(camera.position, Vector3Scale(cameraFront, deltaTime * 2.0f));
//     }
//
//     if (IsKeyDown(KEY_S)) {
//
//         camera.position = Vector3Subtract(camera.position, Vector3Scale(cameraFront, deltaTime * 2.0f));
//     }
//
//     if (IsKeyDown(KEY_A)) {
//
//         camera.position = Vector3Subtract(camera.position, Vector3Scale(Vector3CrossProduct(cameraFront, cameraUp), deltaTime * 2.0f));
//     }
//
//     if (IsKeyDown(KEY_D)) {
//
//         camera.position = Vector3Add(camera.position, Vector3Scale(Vector3CrossProduct(cameraFront, cameraUp), deltaTime * 2.0f));
//     }
//
//     if (IsKeyDown(KEY_SPACE)) {
//
//         camera.position = Vector3Add(camera.position, Vector3Scale(cameraUp, deltaTime * 2.0f));
//     }
//
//     if (IsKeyDown(KEY_LEFT_SHIFT)) {
//
//         camera.position = Vector3Subtract(camera.position, Vector3Scale(cameraUp, deltaTime * 2.0f));
//     }
//
//     if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
//
//         DisableCursor();
//
//         Vector2 mouseDelta = GetMouseDelta();
//
//         yaw += mouseDelta.x * deltaTime;
//
//         pitch += -mouseDelta.y * deltaTime;
//
//         if (pitch > 1.5) {
//
//             pitch = 1.5;
//
//         } else if (pitch < -1.5) {
//
//             pitch = -1.5;
//         }
//
//     } else {
//
//         EnableCursor();
//     }
//
//     direction.x = cos(yaw) * cos(pitch);
//
//     direction.y = sin(pitch);
//
//     direction.z = sin(yaw) * cos(pitch);
//
//     cameraFront = Vector3Normalize(direction);
//
//     cameraRight = Vector3Normalize(Vector3CrossProduct(camera.up, cameraFront));
//
//     cameraUp = Vector3CrossProduct(direction, cameraRight);
//
//     camera.target = Vector3Add(camera.position, cameraFront);
// }
}
