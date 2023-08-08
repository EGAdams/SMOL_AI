#include "IHistory.h"

class IHistoryMock : public IHistory
{
public:
    IHistoryMock() {}
    ~IHistoryMock() {}

    void add(std::string event) override
    {
        // Mock implementation here
    }

    std::string get(int i) override
    {
        // Mock implementation here
        return "";
    }

    int size() override
    {
        // Mock implementation here
        return 0;
    }

    void clear() override
    {
        // Mock implementation here
    }

    std::vector<std::string> getHistory() override
    {
        // Mock implementation here
        return std::vector<std::string>();
    }
};