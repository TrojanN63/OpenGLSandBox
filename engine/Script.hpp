#pragma once
#include <memory>
class gameObject;

class Script {
  protected:
    gameObject* object;
  public:
    Script(gameObject* obj)
      : object(obj) {}
    virtual ~Script() = default;
    virtual void Step() = 0;
};
