/**
   Functions to manage message data including send and receiving with
   a socket.

 */

#ifndef ZIO_MESSAGE_HPP_SEEN
#define ZIO_MESSAGE_HPP_SEEN

#include <vector>
#include <string>

namespace zio {

    namespace level {
        enum MessageLevel {
            reserved=0,
            trace,verbose,debug,info,summary,warning,error,fatal,
        };

        const char* name(MessageLevel lvl);
    }

    struct PrefixHeader {
        int level{0};
        std::string format{""};
        std::string label{""};

        std::string dumps() const;
    };

    typedef uint64_t origin_t;
    typedef uint64_t granule_t;
    typedef uint64_t seqno_t;

    struct CoordHeader {
        origin_t origin{0};
        granule_t granule{0};
        seqno_t seqno{0};
    };
    struct Header {
        PrefixHeader prefix;
        CoordHeader coord;
    };

    /*!
      @brief a zio message

      A message object may be used to build up the message data and
      serializer to or parse from raw bytes.
     */
    class Message {
    public:
        typedef Header header_t;
        typedef std::vector<std::uint8_t> encoded_t;
        typedef std::vector<std::uint8_t> payload_t;
        typedef std::vector<payload_t> multiload_t;


        Message();
        Message(const encoded_t& data);
        Message(const header_t h, const multiload_t& pl = multiload_t());
        
        void set_level(int level) {
            m_header.prefix.level = level;
        }
        void set_label(const std::string& label) {
            m_header.prefix.label = label;
        }

        /// Reset self to empty message
        void clear();

        /// Encode message to flat array
        encoded_t encode() const;

        /// Set self based on encoded array
        void decode(const encoded_t& dat);

        /// Access header
        const header_t& header() const { return m_header; }

        /// Access payload(s)
        const multiload_t& payload() const { return m_payload; }

        /// Set payload, increment seqno and set granule or if zero
        /// use current system time in microseconds.
        void next(const payload_t& pl, granule_t gran=0);
        void next(const multiload_t& pl, granule_t gran=0);

    private:
        header_t m_header;
        multiload_t m_payload;
        
    };


}

#endif
