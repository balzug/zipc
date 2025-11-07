#include <unistd.h>
#include <cstddef>
#include <vector>
#include <map>
#include <string>
#include <mutex>

using namespace std;

byte byteok;

namespace zipc {

class broker {
private:
	broker () = delete;
    static broker instance;

    map<string, pid_t> proc_map;
    mutex proc_map_mutex;


public:
    static broker& get_instance () {
        return instance;
    }

    int send_message (const vector<byte> &buffer);
    int receive (vector<byte> &buffer);
    int register_proc (const string &id);
    int deregister_proc ();
};

};	// namespace zipc
