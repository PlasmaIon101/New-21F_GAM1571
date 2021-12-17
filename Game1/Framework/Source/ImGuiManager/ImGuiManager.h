#pragma once

struct ImDrawData;

namespace fw {

class FWCore;

class ImGuiManager
{
public:
    ImGuiManager(FWCore* pFramework);
    virtual ~ImGuiManager();

    void Init();
    void Shutdown();

    void OnFocusLost();

    void StartFrame(float deltaTime);
    void EndFrame();

protected:
    void ClearInput();

    void RenderDrawLists(ImDrawData* draw_data);

    bool CreateFontsTexture();
    bool CreateDeviceObjects();
    void InvalidateDeviceObjects();

protected:
    FWCore* m_pFramework;

    GLuint m_FontTexture;
    int m_ShaderHandle;
    int m_VertHandle;
    int m_FragHandle;
    int m_AttribLocationTex;
    int m_AttribLocationProjMtx;
    int m_AttribLocationPosition;
    int m_AttribLocationUV;
    int m_AttribLocationColor;
    unsigned int m_VBOHandle;
    unsigned int m_VAOHandle;
    unsigned int m_ElementsHandle;
};

} // namespace fw
