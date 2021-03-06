#ifndef ZIO_DOMO_CLIENT_HPP_SEEND
#define ZIO_DOMO_CLIENT_HPP_SEEND

#include "zio/logging.hpp"
#include "zio/util.hpp"


namespace zio {
namespace domo {

    /*! The ZIO domo client API class
     *
     * Applications may use a Client to simplify participating in the
     * GDP client subprotocol.  The protocol is exercised through
     * calls to Client::send() and Client::recv().
     *
     * The application must arrange to use the "clientish" socket
     * corresponding to what is in use by the broker but otherwise,
     * differences related to the socket type are subsequently erased
     * by this class.
     *
     */

    class Client {
    public:
        /// Create a client requesting service.  Caller keeps socket
        /// eg so to poll it along with others.
        Client(zmq::socket_t& sock, std::string broker_address,
               logbase_t& log);
        ~Client();

        // API methods

        /// Send a request for a service and its associated data.  The
        /// request message should correspond to "Frames 3+ Request
        /// body" of 7/MDP.
        void send(std::string service, zmq::multipart_t& request);

        /// Receive a reply from the last request.  The reply message
        /// holds frames corresponding to "Frames 3+ Reply body" of
        /// 7/MDP.  If an error occurs the reply is empty.
        void recv(zmq::multipart_t& reply);

    private:
        zmq::socket_t& m_sock;
        std::string m_address;
        logbase_t& m_log;
        time_unit_t m_timeout{HEARTBEAT_INTERVAL};
        
    private:
        std::function<void(zmq::socket_t& server_socket,
                           zmq::multipart_t& mmsg)> really_recv;
        std::function<void(zmq::socket_t& server_socket,
                           zmq::multipart_t& mmsg)> really_send;

        void connect_to_broker(bool reconnect = true);
    };
}
}
#endif

