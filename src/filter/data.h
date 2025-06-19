#include <vector>

struct data {
    int protocol;
    int src_ip_1;
    int src_ip_2;
    int src_ip_3;
    int src_ip_4;
    int src_port;
    int dst_ip_1;
    int dst_ip_2;
    int dst_ip_3;
    int dst_ip_4;
    int dst_port;

    data() {}

    data(int p, int s1, int s2, int s3, int s4, int sp, int d1, int d2, int d3, int d4, int dp)
        : protocol(p), src_ip_1(s1), src_ip_2(s2), src_ip_3(s3), src_ip_4(s4), 
          src_port(sp), dst_ip_1(d1), dst_ip_2(d2), dst_ip_3(d3), dst_ip_4(d4), dst_port(dp) {}

    data(const std::vector<int>& v) {
        if (v.size() >= 11) {
            protocol = v[0];
            src_ip_1 = v[1];
            src_ip_2 = v[2];
            src_ip_3 = v[3];
            src_ip_4 = v[4];
            src_port = v[5];
            dst_ip_1 = v[6];
            dst_ip_2 = v[7];
            dst_ip_3 = v[8];
            dst_ip_4 = v[9];
            dst_port = v[10];
        }
    }

    std::vector<int> return_as_vector() {
        std::vector<int> res = {protocol, src_ip_1, src_ip_2, src_ip_3, src_ip_4, 
                               src_port, dst_ip_1, dst_ip_2, dst_ip_3, dst_ip_4, dst_port};
        return res;
    }
};