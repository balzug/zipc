#include <unistd.h>
#include <cstddef>

using namespace std;

byte byteok;

namespace zipc {

class registry {
private:
    registry() = delete;
    static registry instance;
public:
    registry& get_instance () {
        return instance;
    }
}

};	// namespace zipc
