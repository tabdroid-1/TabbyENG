#pragma once

#include <Tabby/Renderer/VertexArray.h>

namespace Tabby {

class NullAPIVertexArray : public VertexArray {
public:
    NullAPIVertexArray();
    virtual ~NullAPIVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
    virtual const Shared<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

private:
    uint32_t m_RendererID;
    uint32_t m_VertexBufferIndex = 0;
    std::vector<Shared<VertexBuffer>> m_VertexBuffers;
    Shared<IndexBuffer> m_IndexBuffer;
};

}