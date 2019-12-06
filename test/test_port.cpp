#include "zio/port.hpp"
#include "zio/peer.hpp"

#include <iostream>
using namespace std;

#include <czmq.h>

int main()
{
    // this test generally pretends to be the guts of a node.

    // create many ports
    zio::Port p("name1", ZMQ_PUB, {"127.0.0.1", 42});
    p.bind();
    // p.connect("name2", "portA");

    // bind all ports first, collecting their headers
    auto hh = p.do_binds();
    for (const auto& one : hh) {
        cerr << "test: not advertising bind: " << one.first << " = " << one.second << endl;
    }

    // advertise those
    zio::Peer peer("test_port", hh);

    // tell all ports to go online and give the peer so they can resovle any connects
    p.online(peer);

    p.send(zio::level::info, zio::TEXT("Hello world!"));

    // for completeness
    p.offline();

    return 0;
}
