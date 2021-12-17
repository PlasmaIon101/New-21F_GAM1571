#pragma once

#include "Framework.h"
#include "DataTypes.h"

class GameObject;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void Init();
    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    fw::Mesh* GetMesh(std::string name) { return m_Meshes[name]; }
    fw::ShaderProgram* GetShader(std::string name) { return m_Shaders[name]; }
    fw::Texture* GetTexture(std::string name) { return m_Textures[name]; }

protected:
    fw::FWCore& m_FWCore;
    fw::ImGuiManager* m_pImGuiManager;

    float m_TimePassed;

    std::map<std::string, fw::Mesh*> m_Meshes;
    std::map<std::string, fw::ShaderProgram*> m_Shaders;
    std::map<std::string, fw::Texture*> m_Textures;

    vec2 m_ProjectionScale;
    vec2 m_CameraPosition;

    GameObject* m_pGameObject;
};
