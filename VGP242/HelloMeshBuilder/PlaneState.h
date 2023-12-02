#include "GameState.h"

class PlaneState : public GameState
{
public:
    virtual ~PlaneState() = default;

protected:
    void CreateMesh() override;
};