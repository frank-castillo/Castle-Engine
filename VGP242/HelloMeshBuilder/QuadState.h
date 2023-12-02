#include "GameState.h"

class QuadState : public GameState
{
public:
    virtual ~QuadState() = default;

protected:
    void CreateMesh() override;
};