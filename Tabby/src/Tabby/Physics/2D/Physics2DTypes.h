#pragma once

#include <Tabby/Scene/Components.h>
#include <Tabby/Scene/Entity.h>

namespace Tabby {

namespace Utils {

    inline b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
    {
        switch (bodyType) {
        case Rigidbody2DComponent::BodyType::Static:
            return b2_staticBody;
        case Rigidbody2DComponent::BodyType::Dynamic:
            return b2_dynamicBody;
        case Rigidbody2DComponent::BodyType::Kinematic:
            return b2_kinematicBody;
        }

        TB_CORE_ASSERT(false, "Unknown body type");
        return b2_staticBody;
    }

    inline Rigidbody2DComponent::BodyType Rigidbody2DTypeFromBox2DBody(b2BodyType bodyType)
    {
        switch (bodyType) {
        case b2_staticBody:
            return Rigidbody2DComponent::BodyType::Static;
        case b2_dynamicBody:
            return Rigidbody2DComponent::BodyType::Dynamic;
        case b2_kinematicBody:
            return Rigidbody2DComponent::BodyType::Kinematic;
        }

        TB_CORE_ASSERT(false, "Unknown body type");
        return Rigidbody2DComponent::BodyType::Static;
    }

}

// TODO: More collider types
enum ColliderType2D : uint8_t {
    Box = 0,
    Circle = 1
};

// Callback Data Structs
struct ContactCallback {
    Entity entity;
    Tabby::TransformComponent* transform;
    Tabby::Rigidbody2DComponent* rigidbody;
};

struct RaycastHit2D {
    Entity entity;
    Tabby::TransformComponent* transform;
    Tabby::Rigidbody2DComponent* rigidbody;
    glm::vec2 point = { 0.0f, 0.0f };
    glm::vec2 normal = { 0.0f, 0.0f };
    float distance;
    float fraction;
};

struct BodyInfo2D {
    Entity entity;
};

struct FixtureInfo2D {
    Entity entity;
    ColliderType2D colliderType;
};

}
