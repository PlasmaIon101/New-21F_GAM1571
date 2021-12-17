#include "Framework.h"
#include <functional>

#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "SpriteSheet.h"
#include "Tilemap.h"

#include "../Libraries/rapidjson/document.h"

int Add(int a, int b)
{
    return a + b;
}

int Subtract(int a, int b)
{
    return a - b;
}

//typedef int (MathOperator)(int a, int b);
//typedef std::function<int(int, int)> MathOperator;

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
    , m_pImGuiManager( nullptr )
    , m_TimePassed( 0.0f )
    , m_pBasicShader( nullptr )
    , m_pTexture( nullptr )
    , m_pTexture2( nullptr )
    , m_pPlayer( nullptr )
    , m_pEnemy( nullptr )
    , m_pPlayerController( nullptr )
{
    //MathOperator op = Add;

    //int a = op(3, 6);

    //op = Subtract;

    //int b = op(3, 6);

    //int bp = 1;
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

    for (auto& it : m_Sprites)
    {
        delete it.second;
    }

    delete m_pImGuiManager;

    delete m_TilemapObject;

    delete[] a_firstTilemap;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );
    m_pImGuiManager->Init();

    glPointSize( 10 );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //std::vector<float> triangleVerts = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f   };
    //std::vector<float> diamondVerts = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f,    0.0f,1.0f,0.5f };
    std::vector<fw::VertexFormat> tileVerts =
    {
        //{ vec2( 0.0f,1.0f),  255,255,255,255,  vec2(130 / 512.0f, (62 + 64) / 256.0f) }, // top left
        //{ vec2( 0.0f,0.0f),  255,255,255,255,  vec2(130 / 512.0f, 62 / 256.0f) }, // bottom left
        //{ vec2( 1.0f,1.0f),  255,255,255,255,  vec2((130 + 64) / 512.0f, (62 + 64) / 256.0f) }, // top right
        //{ vec2( 1.0f,0.0f),  255,255,255,255,  vec2((130 + 64) / 512.0f, 62 / 256.0f) }, // bottom right

        { vec2(0.0f,1.0f),  255,255,255,255,  vec2(0.0f, 1.0f) }, // top left
        { vec2(0.0f,0.0f),  255,255,255,255,  vec2(0.0f, 0.0f) }, // bottom left
        { vec2(1.0f,1.0f),  255,255,255,255,  vec2(1.0f, 1.0f) }, // top right
        { vec2(1.0f,0.0f),  255,255,255,255,  vec2(1.0f, 0.0f) }, // bottom right
    };
    std::vector<fw::VertexFormat> playerVerts =
    {
        //{ vec2( 0.0f,1.0f),  255,255,255,255,  vec2(130 / 512.0f, (62 + 64) / 256.0f) }, // top left
        //{ vec2( 0.0f,0.0f),  255,255,255,255,  vec2(130 / 512.0f, 62 / 256.0f) }, // bottom left
        //{ vec2( 1.0f,1.0f),  255,255,255,255,  vec2((130 + 64) / 512.0f, (62 + 64) / 256.0f) }, // top right
        //{ vec2( 1.0f,0.0f),  255,255,255,255,  vec2((130 + 64) / 512.0f, 62 / 256.0f) }, // bottom right

        { vec2(-0.5f,0.5f),  255,255,255,255,  vec2(0.0f, 1.0f) }, // top left
        { vec2(-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f, 0.0f) }, // bottom left
        { vec2(0.5f,0.5f),  255,255,255,255,  vec2(1.0f, 1.0f) }, // top right
        { vec2(0.5f,-0.5f),  255,255,255,255,  vec2(1.0f, 0.0f) }, // bottom right
    };
    m_Meshes["Tiles"] = new fw::Mesh( GL_TRIANGLE_STRIP, tileVerts );
    m_Meshes["Characters"] = new fw::Mesh( GL_TRIANGLE_STRIP, playerVerts);

    m_pBasicShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );

    //m_pTexture2 = new fw::Texture( "Data/Textures/mario.png" );
    m_pTexture = new fw::Texture( "Data/Textures/Sprites.png" );

    m_pPlayerController = new PlayerController();

    m_Sprites["Knockoff"] = new SpriteSheet("Data/Textures/Sprites.json");

    m_pPlayer = new Player( m_Meshes["Characters"], m_pBasicShader, m_pTexture, vec2(-1.0f, -1.0f), m_pPlayerController, m_Sprites["Knockoff"]);
    m_pEnemy = new Enemy( m_Meshes["Characters"], m_pBasicShader, m_pTexture, vec2(0.0f, 2.0f), m_Sprites["Knockoff"]);

    a_firstTilemap = new unsigned char[8 * 8]
    {
        0, 4, 5, 4, 5, 4, 5, 4,
        4, 0, 3, 1, 2, 3, 0, 5,
        5, 3, 3, 2, 1, 3, 3, 4,
        2, 1, 2, 1, 2, 1, 2, 1,
        1, 2, 1, 2, 1, 2, 1, 2,
        4, 3, 3, 1, 2, 3, 3, 5,
        5, 0, 3, 2, 1, 3, 0, 4,
        4, 5, 4, 5, 4, 5, 4, 5,
    };

    m_TilemapObject = new Tilemap(m_Meshes["Tiles"], m_pBasicShader, m_pTexture, m_Sprites["Knockoff"], vec2(1.0,1.0));
    m_TilemapObject->SetTilemap(a_firstTilemap, 8, 8);

    m_pPlayer->SetTilemap(m_TilemapObject);
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();
    ImGui::Text("%d", m_TilemapObject->GetIfWalkable(m_pPlayer->GetPosition()));

    m_TimePassed += deltaTime;

    m_pPlayer->Update( deltaTime );
    m_pEnemy->Update( deltaTime );

    CheckForCollisions();
}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    //static vec2 camPos = vec2(-1,0);
    //ImGui::DragFloat2( "Cam Pos", &camPos.x, 0.01f );

    vec2 cameraPosi = m_pPlayer->GetPosition();

    m_TilemapObject->Draw(vec2(1 / 3.0f, 1 / 3.0f), cameraPosi);
    m_pPlayer->Draw( vec2(1/3.0f, 1/3.0f), cameraPosi);
    //m_pEnemy->Draw( vec2(1/3.0f, 1/3.0f), camPos );

    m_pImGuiManager->EndFrame();
}

void Game::CheckForCollisions()
{
    //if( m_pPlayer->IsCollidingWith( m_pEnemy ) )
    //{
    //    ImGui::Text( "Colliding" );
    //}
}
