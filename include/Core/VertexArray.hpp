#ifndef CORE_VERTEX_ARRAY_HPP
#define CORE_VERTEX_ARRAY_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Core/IndexBuffer.hpp"
#include "Core/VertexBuffer.hpp"

namespace Core {
/**
 * @brief Wrapper for OpenGL Vertex Array Object
 */
class VertexArray {
    /**
     * I dislike the way `VertexBuffer` and `IndexBuffer` are handled here. This
     * breaks RAII principles
     *
     * TODO: Maybe find an alternative solution
     */
public:
    VertexArray();
    VertexArray(const VertexArray &) = delete;
    VertexArray(VertexArray &&other);

    ~VertexArray();

    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray &operator=(VertexArray &&other);

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer);
    void AddVertexBufferWithCustomizableAttribute() {}
    /**
     * Index buffer must be set or else there will be a segfault
     */
    void SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);

    void DrawTriangles() const;
    void DrawRectangles() const;
    void DrawLines(int count) const;
    template <class T>
    void modifyVertexBuffersByIndex(int index, int size, std::vector<T> data) {
        m_VertexBuffers[index]->ModifyBufferData(size, data);
    }

private:
    GLuint m_ArrayId;
    std::vector<std::unique_ptr<VertexBuffer>> m_VertexBuffers;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
};
} // namespace Core
#endif
