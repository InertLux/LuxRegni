// Public/Presenters/IPresenter.h
#pragma once

class Regnum;

class IPresenter {
public:
    virtual ~IPresenter() = default;
    virtual void Present(const Regnum& game) = 0;
    virtual void HandleInput() = 0;
    virtual bool IsRunning() const = 0;
};
