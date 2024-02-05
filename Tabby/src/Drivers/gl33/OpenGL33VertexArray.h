#pragma once

#include "Tabby/Renderer/VertexArray.h"

namespace Tabby {

class OpenGL33VertexArray : public VertexArray {
public:
    OpenGL33VertexArray();
    virtual ~OpenGL33VertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

private:
    uint32_t m_RendererID;
    uint32_t m_VertexBufferIndex = 0;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
};

}
