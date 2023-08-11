
#ifndef IPinStateMock_h
#define IPinStateMock_h

#include "IPinState.h"
#include <gmock/gmock.h>

class IPinStateMock : public IPinState {
public:
    MOCK_METHOD( void, setPinState, ( const std::string& pin, int state ), ( override ));
    MOCK_METHOD( int, getPinState, ( const std::string& pin ), ( override ));
    MOCK_METHOD( void, clear, (), ( override ));
    MOCK_METHOD(( std::map<std::string, int >), getMap, (), ( override ));
};

#endif
