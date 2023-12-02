#pragma once

namespace CASTLEEngine::Graphics
{
    class Texture
    {
    public:
        static void UnbindPS(uint32_t slot); // Unbind Pixel Shader

    public:
        enum class Format
        {
            RGBA_U8,
            RGBA_U32
        };

        Texture() = default;
        virtual ~Texture();

        // Prohibit Copying
        Texture(const Texture&) = delete; // Copy constructor
        Texture& operator=(const Texture&) = delete; // Assign operator

        Texture(Texture&& rhs) noexcept;
        Texture& operator=(Texture&& rhs) noexcept;

        virtual void Initialize(const std::filesystem::path& fileName);
        virtual void Initialize(uint32_t width, uint32_t height,Format format);
        virtual void Terminate();

        void BindVS(uint32_t slot) const; // We have to bind them to the graphics in order to render
        void BindPS(uint32_t slot) const; // We have to bind them to the graphics in order to render

        void* GetRawData() const { return mShaderResourceView; }

    protected:
        DXGI_FORMAT GetDXGIFormat(Format format);
        ID3D11ShaderResourceView* mShaderResourceView = nullptr;
    };
}
