//
// Created by 盧威任 on 2/16/24.
//

#include "Grid.hpp"
#include "Core/Drawable.hpp"

void Grid::Start() {

    std::vector<float> vertex = {};
    std::vector<float> color = {};
    for (auto line : m_lineVector) {
        vertex.push_back(line.getlineFrom().x);
        vertex.push_back(line.getlineFrom().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);

        vertex.push_back(line.getlineTo().x);
        vertex.push_back(line.getlineTo().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);
    }
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(vertex, 2));
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(color, 3));
}

void Grid::Update() {
    if (m_Activate == false) {
        return;
    }
    glLineWidth(m_lineWidth);
    const float width = 1280.0F / 2.0F;
    const float height = 720.0F / 2.0F;

    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();

    Matrices data = {
        {
            1.F, 0.F, //
            0.F, 1.F  //
        },
        {
            1.0F / width, 0.0F, //
            0.0F, 1.0F / height //
        },
    };

    std::vector<float> vertex = {};
    std::vector<float> color = {};
    for (auto line : m_lineVector) {
        vertex.push_back(line.getlineFrom().x);
        vertex.push_back(line.getlineFrom().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);

        vertex.push_back(line.getlineTo().x);
        vertex.push_back(line.getlineTo().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);
    }

    // m_Matrices->SetData(0, data);

    m_Matrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);
}

void Grid::StartDrawingGridByWindowSize() {
    float cellWidth = 48.F;
    float cellHeight = 48.F;

    for (int i = (WINDOW_WIDTH / 2); i > int(-(WINDOW_WIDTH / 2));
         i -= cellHeight) {
        // vertical
        m_lineVector.push_back(Line(glm::vec2(i, int(-(WINDOW_HEIGHT / 2))),
                                    glm::vec2(i, int(WINDOW_HEIGHT / 2))));
    }

    for (int i = (WINDOW_HEIGHT / 2); i > int(-(WINDOW_HEIGHT / 2));
         i -= cellWidth) {
        // horz
        m_lineVector.push_back(Line(glm::vec2(int(-(WINDOW_WIDTH / 2)), i),
                                    glm::vec2(int(WINDOW_WIDTH / 2), i)));
    }

    std::vector<Line> test{
        Line(glm::vec2(360, 940), glm::vec2(360, -940)),
        Line(glm::vec2(-(WINDOW_HEIGHT / 2), (WINDOW_WIDTH / 2) - 48),
             glm::vec2((WINDOW_HEIGHT / 2), (WINDOW_WIDTH / 2) - 48))};

    this->Start();
}