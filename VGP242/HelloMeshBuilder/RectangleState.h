#include "GameState.h"

class RectangleState : public GameState
{
public:
    virtual ~RectangleState() = default;

protected:
    void CreateMesh() override;
};