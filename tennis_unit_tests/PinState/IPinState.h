
#ifndef IPinState_h
#define IPinState_h

#include <map>
#include <string>

class IPinState {
public:
    virtual ~IPinState() = default;

    virtual void setPinState(const std::string& pin, int state) = 0;
    virtual int getPinState(const std::string& pin) = 0;
    virtual void clear() = 0;
    virtual std::map<std::string, int> getMap() = 0;
};

#endif
