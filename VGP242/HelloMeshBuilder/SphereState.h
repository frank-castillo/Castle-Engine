#include "GameState.h"

class SphereState : public GameState
{
public:
    virtual ~SphereState() = default;

protected:
    void CreateMesh() override;
};