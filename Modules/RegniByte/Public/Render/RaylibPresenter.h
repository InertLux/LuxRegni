// Public/Presenters/RaylibPresenter.h
#pragma once
#include "RenderTypes.hpp"
#include <map>
#include <string>
#include <raylib.h>

class RaylibPresenter : public IPresenter {
private:
    std::map<std::string, Texture2D> textureCache;
    bool running = true;

    Texture2D ResolveAsset(const std::string& assetPath);
    
public:
    RaylibPresenter();
    ~RaylibPresenter();
    
    void Present(const Regnum& game) override;
    void HandleInput() override;
    bool IsRunning() const override { return running; }
};
