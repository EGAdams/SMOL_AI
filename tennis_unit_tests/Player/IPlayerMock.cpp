#include <gmock/gmock.h>
#include "IPlayer.h"

class IPlayerMock : public IPlayer {
public:
    MOCK_METHOD0( getPoints, int());
    MOCK_METHOD1( setPoints, void(int)); };