/**

   Each format by ZIO has a struct that represents it.

   This struct provides the data in a normalized way (std::string)
   with adapters to the C++ type that best represents the type.

 */

// fixme: add protobuf under conditional compilation

#ifndef ZIO_FORMAT_HPP_SEEN
#define ZIO_FORMAT_HPP_SEEN

#include "zio/types.hpp"

#include <string>
#include <vector>
#include <cstring>

namespace zio {

    // Convert between byte array to native type
    namespace converter {

        // string
        struct text_t {
            typedef std::string native_type;
            const char* format() const { return "TEXT"; }
            std::string operator()(const payload_t& buf);
            payload_t operator()(const std::string& str);
        };

        // JSON in with variants on byte packing
        struct json_t {
            typedef json native_type;
            const char* format() const { return "JSON"; }
            json operator()(const payload_t& buf);
            payload_t operator()(const json& job);
        };
        struct bson_t {
            typedef json native_type;
            const char* format() const { return "BSON"; }
            json operator()(const payload_t& buf);
            payload_t operator()(const json& job);
        };
        struct cbor_t {
            typedef json native_type;
            const char* format() const { return "CBOR"; }
            json operator()(const payload_t& buf);
            payload_t operator()(const json& job);
        };
        struct msgp_t {
            typedef json native_type;
            const char* format() const { return "MSGP"; }
            json operator()(const payload_t& buf);
            payload_t operator()(const json& job);
        };
        struct ubjs_t {
            typedef json native_type;
            const char* format() const { return "UBJS"; }
            json operator()(const payload_t& buf);
            payload_t operator()(const json& job);
        };
            
        /// Protobuf messages.  Provide as templates to leave protobuf
        /// dependency an application level option.  The PB type may be
        /// base ::google::protobuf::Message if actual type is not yet
        /// known.
        template<typename PB>
        struct pbuf_t {
            typedef PB native_type;
            const char* format() const { return "PBUF"; }
            PB operator()(const payload_t& buf) {
                PB msg;
                msg.ParseFromArray(buf.data(), buf.size());
                return msg;
            }
            payload_t operator()(const PB& msg) {
                size_t siz = msg.ByteSize();
                payload_t buf(siz);
                msg.SerializeToArray(buf.data(), siz);
                return buf;
            }
        };
    }
}

#endif
