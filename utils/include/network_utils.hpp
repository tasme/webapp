#pragma once

#include <boost/asio.hpp>
#include <string>


using HostInetInfo = boost::asio::ip::tcp::resolver::iterator;

class NetworkUtils {
private:
    static HostInetInfo queryHostInetInfo();
    static std::string hostIP(unsigned short family);
public:
    // gets the host IP4 string formatted
    static std::string hostIP4() {
        return hostIP(AF_INET);
    }

    // gets the host IP6 string formatted
    static std::string hostIP6() {

        return hostIP(AF_INET6);
    }
    static std::string hostName() {
        return boost::asio::ip::host_name();
    }
};
