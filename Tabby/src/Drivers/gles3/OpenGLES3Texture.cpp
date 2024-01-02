#include "Drivers/gles3/OpenGLES3Texture.h"
#include "Drivers/gles3/GLES3.h"
#include "tbpch.h"
#include <glad/gles3.h>

#include <stb_image.h>

namespace Tabby {

namespace Utils {

    static GLenum TabbyImageFormatToGLDataFormat(ImageFormat format)
    {
        switch (format) {
        case ImageFormat::RGB8:
            return GL_RGB;
        case ImageFormat::RGBA8:
            return GL_RGBA;
        }

        TB_CORE_ASSERT(false);
        return 0;
    }

    static GLenum TabbyImageFormatToGLInternalFormat(ImageFormat format)
    {
        switch (format) {
        case ImageFormat::RGB8:
            return GL_RGB8;
        case ImageFormat::RGBA8:
            return GL_RGBA8;
        }

        TB_CORE_ASSERT(false);
        return 0;
    }

}

OpenGLES3Texture2D::OpenGLES3Texture2D(const TextureSpecification& specification)
    : m_Specification(specification)
    , m_Width(m_Specification.Width)
    , m_Height(m_Specification.Height)
{
    // TB_PROFILE_FUNCTION();

    m_InternalFormat = Utils::TabbyImageFormatToGLInternalFormat(m_Specification.Format);
    m_DataFormat = Utils::TabbyImageFormatToGLDataFormat(m_Specification.Format);

    // Create and bind a texture
    GLES3::GL()->GenTextures(1, &m_RendererID);
    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);

    // Allocate storage for the texture using glTexImage2D
    GLES3::GL()->TexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Set texture parameters
    GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    // glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
    //
    // glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    // glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLES3Texture2D::OpenGLES3Texture2D(const std::string& path)
    : m_Path(path)
{
    // TB_PROFILE_FUNCTION();

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = nullptr;
    {
        // TB_PROFILE_SCOPE("stbi_load - OpenGLES3Texture2D::OpenGLES3Texture2D(const std::string&)");
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    }

    if (data) {
        m_IsLoaded = true;

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        TB_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        // Generate and bind a texture
        GLES3::GL()->GenTextures(1, &m_RendererID);
        GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);

        GLES3::GL()->TexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        // Set texture filtering and wrapping options
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glGenerateMipmap(GL_TEXTURE_2D);

        // glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        // glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
        //
        // glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //
        // glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //
        // glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
}

OpenGLES3Texture2D::~OpenGLES3Texture2D()
{
    // TB_PROFILE_FUNCTION();

    GLES3::GL()->DeleteTextures(1, &m_RendererID);
}

void OpenGLES3Texture2D::SetData(void* data, uint32_t size)
{
    // TB_PROFILE_FUNCTION();

    // uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    // TB_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
    // glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

    uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    // Ensure that the provided size matches the expected size
    TB_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be the entire texture!");

    // Update the texture data using glTexSubImage2D
    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
    GLES3::GL()->TexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLES3Texture2D::Bind(uint32_t slot) const
{
    // TB_PROFILE_FUNCTION();

    // Activate a texture unit
    GLES3::GL()->ActiveTexture(GL_TEXTURE0 + slot);

    // Bind the texture to the active texture unit
    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);

    // glBindTextureUnit(slot, m_RendererID);
}
}