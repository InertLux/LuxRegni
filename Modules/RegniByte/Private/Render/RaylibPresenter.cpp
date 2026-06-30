// Private/Render/RaylibPresenter.cpp
#include "RaylibPresenter.h"
#include "AsciiScene.h"
#include <raylib.h>

RaylibPresenter::RaylibPresenter() {
    InitWindow(1280, 720, "LuxRegni");
    SetTargetFPS(60);
}

RaylibPresenter::~RaylibPresenter() {
    CloseWindow();
}

Texture2D RaylibPresenter::ResolveAsset(const std::string& assetPath) {
    auto it = textureCache.find(assetPath);
    if (it != textureCache.end()) return it->second;
    
    Texture2D tex = LoadTexture(assetPath.c_str());
    if (tex.id == 0) tex = {0, 0, 0, 1, 1}; // fallback blank
    textureCache[assetPath] = tex;
    return tex;
}

void RaylibPresenter::Present(const Regnum& game) {
    BeginDrawing();
    ClearBackground(BLACK);
    
//    for (const auto& tile : game.GetScene().GetTiles()) {
//        Texture2D sprite = ResolveAsset(tile.assetPath);
//        
//        if (sprite.id != 0) {
//            DrawTexturePro(sprite,
//                {0, 0, (float)sprite.width, (float)sprite.height},
//                {tile.x * 16.f, tile.y * 16.f, 16.f, 16.f},
//                {0, 0}, 0, WHITE);
//        } else {
//            DrawText(tile.glyphFallback, tile.x * 16, tile.y * 16, 16, tile.color);
//        }
//    }
    
//    for (const auto& particle : game.GetShard().GetParticles()) {
//        DrawCircle(particle.x, particle.y, 2, particle.color);
//    }
    
    EndDrawing();
}

void RaylibPresenter::HandleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) running = false;
}
