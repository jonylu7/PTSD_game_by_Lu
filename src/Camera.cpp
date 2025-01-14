//
// Created by 盧威任 on 2/17/24.
//

#include "Camera.hpp"

glm::vec2 CameraClass::m_Position(glm::vec2(0,0));
float CameraClass::m_Zoom=1.F;

void CameraClass::Start() {}

void CameraClass::Update() {
    UpdateWhenCursorAtBoarder();
    UpdateWhenCursorScroll();
}

void CameraClass::UpdateWhenCursorAtBoarder() {
    // TODO: where to put is cursor at boarder??
    int cursorAtBoarder = Core::Context::IsCurosrAtBoarder();
    glm::vec2 CameraPosition = getPosition();
    float CameraMovingSpeed = getMovingSpeed();
    switch (cursorAtBoarder) {
    case (0):
        CameraPosition.y += CameraMovingSpeed;
        break;
    case (1):
        CameraPosition.x += CameraMovingSpeed;
        break;
    case (2):
        CameraPosition.y -= CameraMovingSpeed;
        break;
    case (3):
        CameraPosition.x -= CameraMovingSpeed;
        break;
    case (4):
        break;
    }
    setPosition(CameraPosition);
}

void CameraClass::UpdateWhenCursorScroll() {
    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        addCameraZoom(delta.y * getZoomingSpeed());
        // LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
}

void CameraClass::addCameraZoom(float add) {

    if (m_Zoom + add < 5 && m_Zoom + add > 0) {
        m_Zoom += add;
    }
}