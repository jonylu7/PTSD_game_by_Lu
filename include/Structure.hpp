//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"

class Structure : public Util::GameObject {

public:
    enum class updateMode { Invisidable, Moveable, Fixed };
    Structure(){};
    ~Structure(){};

    void Update(const Util::Transform &transform = Util::Transform()) override;
    // test
    void UpdateUsingCamera(CameraClass camera) {
        Util::Transform transform;
        transform.scale = glm::vec2(camera.getCameraZoom());
        Core::Matrices data = {
            // where is this function ??? Util::TransformToMat4(transform, 0),
            {},
            camera.getProjectionMatrix() * camera.getViewMatrix(),
        };


    }
    void Start() override{};
    updateMode GetCurrentUpdateMode() const { return m_CurrentState; };
    void SetCurrentUpdateMode(updateMode mode) { m_CurrentState = mode; };
    void SetObjectLocation(glm::vec2 location) { ObjectLocation = location; }

private:
    updateMode m_CurrentState = updateMode::Invisidable;
    glm::vec2 ObjectLocation;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
