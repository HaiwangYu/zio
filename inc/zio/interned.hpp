#ifndef ZIO_EXTERNALS_HPP_SEEN
#define ZIO_EXTERNALS_HPP_SEEN

#include "zio/json.hpp"
#include "zio/zmq.hpp"
#include "zio/zmq_addon.hpp"
#include "zio/zmq_actor.hpp"

namespace zio {
    // The great Nlohmann's JSON.
    using json = nlohmann::json;

    // Dubiously intern cppzmq namespace
    using namespace zmq;

    /// Return the ZeroMQ socket type number for the socket.
    int sock_type(const socket_t& sock);
    std::string sock_type_name(int stype);
}
#endif

