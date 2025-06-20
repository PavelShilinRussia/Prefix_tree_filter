#include <vector>

struct data {
    int protocol;
    int src_ip;
    int src_port; 
    int dst_ip;
    int dst_port;

    data() {}

    data(int p, int s_ip, int sp, int d_ip, int dp)
        : protocol(p), src_ip(s_ip), 
          src_port(sp), dst_ip(d_ip), dst_port(dp) {}

    data(const std::vector<int>& v) {
        if (v.size() >= 11) {
            protocol = v[0];
            src_ip = v[1];
            src_port = v[5];
            dst_ip = v[6];
            dst_port = v[10];
        }
    }

    std::vector<int> return_as_vector() {
        std::vector<int> res = {protocol, src_ip, 
                               src_port, dst_ip, dst_port};
        return res;
    }
};