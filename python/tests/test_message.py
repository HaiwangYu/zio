#!/usr/bin/env python3
'''
test zio.Message
'''

import zmq
import unittest

import zio

class TestMessage(unittest.TestCase):

    def setUp(self):
        pass

    def test_ctor_default(self):
        m = zio.Message();
        print (m.origin)
        assert (m.origin == 0)
        assert (m.seqno == 0)
        assert (m.level == zio.MessageLevel.undefined)
        assert (m.label == "")
        assert (m.form == "    ")

    def test_ctor_parts(self):
        ph = zio.PrefixHeader()
        ch = zio.CoordHeader()
        msg = zio.Message(parts=[bytes(ph), bytes(ch), b'Hello', b'World'])
        assert (2 == len(msg.payload))

    def test_ctor_encstr(self):
        msg = zio.Message(payload = 'hello world'.split())
        assert (2 == len(msg.payload))
        enc = msg.encode()

    def test_ctor_headers(self):
        msg = zio.Message(coord = zio.CoordHeader(seqno=100))
        assert(msg.seqno == 100)
        
