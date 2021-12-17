#include "Framework.h"

#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerController.h"
#include "Enemy.h"

#include "../Libraries/rapidjson/document.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
    , m_pImGuiManager( nullptr )
    , m_TimePassed( 0.0f )
    , m_pBasicShader( nullptr )
    , m_pTexture( nullptr )
    , m_pPlayer( nullptr )
    , m_pEnemy( nullptr )
    , m_pPlayerController( nullptr )
{
    const char* jsonString = fw::LoadCompleteFile("Data/Textures/Sokoban.json", nullptr);
    rapidjson::Document document;
    document.Parse(jsonString);
    delete[] jsonString;
    
    rapidjson::Value& spriteToolVersion = document["SpriteTool"];
    int version = spriteToolVersion.GetInt();

    int width = document["Width"].GetInt();

    rapidjson::Value& spriteArray = document["Sprites"];
    for (int i = 0; i < spriteArray.Size(); i++)
    {
        rapidjson::Value& sprite = spriteArray[i];

        int x = sprite["X"].GetInt();
    }

    int bp = 1;
}

Game::~Game()
{
    delete m_pPlayer;
    delete m_pEnemy;

    delete m_pPlayerController;

    delete m_pTexture;
    delete m_pBasicShader;

    for( auto& it : m_Meshes )
    {
        delete it.second;
    }

    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );
    m_pImGuiManager->Init();

    glPointSize( 10 );

    //std::vector<float> triangleVerts = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f   };
    //std::vector<float> diamondVerts = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f,    0.0f,1.0f,0.5f };
    std::vector<fw::VertexFormat> spriteVerts =
    {
        { vec2( 0.0f,1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
        { vec2( 0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
        { vec2( 1.0f,1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
        { vec2( 1.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    };

    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_STRIP, spriteVerts );

    m_pBasicShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );

    m_pTexture2 = new fw::Texture( "Data/Textures/mario.png" );
    m_pTexture = new fw::Texture( "Data/Textures/numbers.png" );

    m_pPlayerController = new PlayerController();

    m_pPlayer = new Player( m_Meshes["Sprite"], m_pBasicShader, m_pTexture, vec2(0.0f, 0.0f), m_pPlayerController );
    m_pEnemy = new Enemy( m_Meshes["Sprite"], m_pBasicShader, m_pTexture2, vec2(0.0f, 2.0f) );
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();

    m_TimePassed += deltaTime;

    m_pPlayer->Update( deltaTime );
    m_pEnemy->Update( deltaTime );

    CheckForCollisions();
}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    static vec2 camPos = vec2(-1,0);
    ImGui::DragFloat2( "Cam Pos", &camPos.x, 0.01f );

    m_pPlayer->Draw( vec2(1/3.0f, 1/3.0f), camPos );
    m_pEnemy->Draw( vec2(1/3.0f, 1/3.0f), camPos );

    m_pImGuiManager->EndFrame();
}

void Game::CheckForCollisions()
{
    //if( m_pPlayer->IsCollidingWith( m_pEnemy ) )
    //{
    //    ImGui::Text( "Colliding" );
    //}
}
