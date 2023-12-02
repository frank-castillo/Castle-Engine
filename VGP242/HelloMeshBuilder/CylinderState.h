#include "GameState.h"

class CylinderState : public GameState
{
public:
    virtual ~CylinderState() = default;

protected:
    void CreateMesh() override;
};