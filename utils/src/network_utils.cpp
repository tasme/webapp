#include "network_utils.hpp"

using boost::asio::ip::tcp;

namespace asio =  boost::asio;

HostInetInfo NetworkUtils::queryHostInetInfo() {
    asio::io_service ios;
    tcp::resolver resolver(ios);
    tcp::resolver::query query(hostName(), "");
    return resolver.resolve(query);
}

std::string NetworkUtils::hostIP(unsigned short family) {
    auto hostInetInfo = queryHostInetInfo();
    tcp::resolver::iterator end;
    while(hostInetInfo != end) {
        tcp::endpoint ep = *hostInetInfo++;
        sockaddr sa = *ep.data();
        if (sa.sa_family == family) {
            return ep.address().to_string();
        }
    }
    return nullptr;
}
