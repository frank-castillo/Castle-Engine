#include "Precompiled.h"
#include "TransformComponent.h"

#include "GameObject.h"

void TransformComponent::DebugUI()
{
    Graphics::SimpleDraw::AddTransform(GetMatrix4());
}

void TransformComponent::EditorUI()
{
    ImGui::LabelText("Transform", "");

    auto uniqueId = GetOwner().GetUniqueId();
    std::string positionStr = "Position##" + std::to_string(uniqueId);
    std::string rotationStr = "Rotation##" + std::to_string(uniqueId);
    std::string scaleStr = "Scale##" + std::to_string(uniqueId);

    ImGui::DragFloat3(positionStr.c_str(), &position.x);
    ImGui::DragFloat3(rotationStr.c_str(), &rotation.x);
    ImGui::DragFloat3(scaleStr.c_str(), & scale.x);
}

void TransformComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
    rapidjson::Value componentValue(rapidjson::kObjectType);

    rapidjson::Value posArray(rapidjson::kArrayType);
    posArray.PushBack(position.x, doc.GetAllocator());
    posArray.PushBack(position.y, doc.GetAllocator());
    posArray.PushBack(position.z, doc.GetAllocator());
    componentValue.AddMember("Position", posArray, doc.GetAllocator());

    rapidjson::Value rotArray(rapidjson::kArrayType);
    posArray.PushBack(rotation.x, doc.GetAllocator());
    posArray.PushBack(rotation.y, doc.GetAllocator());
    posArray.PushBack(rotation.z, doc.GetAllocator());
    posArray.PushBack(rotation.w, doc.GetAllocator());
    componentValue.AddMember("Rotation", rotArray, doc.GetAllocator());

    rapidjson::Value scaleArray(rapidjson::kArrayType);
    posArray.PushBack(scale.x, doc.GetAllocator());
    posArray.PushBack(scale.y, doc.GetAllocator());
    posArray.PushBack(scale.z, doc.GetAllocator());
    componentValue.AddMember("Scale", scaleArray, doc.GetAllocator());

    value.AddMember("TransformComponent", componentValue, doc.GetAllocator());
}
