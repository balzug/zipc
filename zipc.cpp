#include "zipc.h"

int f () { 
    return 0; 
}

int zipc::broker::send_message (const vector<byte> &buffer) {
    return 0;
}

int zipc::broker::receive (vector<byte> &buffer) {
    return 0;
}

int zipc::broker::register_proc (const string &id) {
    lock_guard<mutex> lock (this->proc_map_mutex);

    const pid_t pid = getpid();
    this->proc_map[id] = pid;

    return 0;
}

int zipc::broker::deregister_proc () {
    lock_guard<mutex> lock (this->proc_map_mutex);

    const pid_t pid = getpid();
//    this-proc_map.erase(pid);  pid -> id

    return 0;
}
