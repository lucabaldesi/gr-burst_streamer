#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 luca baldesi.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

import time
from gnuradio import gr, gr_unittest
from gnuradio import blocks
try:
    from burst_streamer import burst_streamer
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from burst_streamer import burst_streamer

class qa_burst_streamer(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        instance = burst_streamer(1e-9, -1, 1)

    def test_with_enough_data(self):
        src_data = [1, 2, 3]
        src = blocks.vector_source_c(src_data)
        thr = burst_streamer(10, 3, 1)
        dst = blocks.vector_sink_c()
        self.tb.connect(src, thr, dst)

        start_time = time.perf_counter()
        self.tb.run()
        end_time = time.perf_counter()

        total_time = end_time - start_time
        self.assertGreater(total_time, 0.29)
        self.assertLess(total_time, 0.45)

        dst_data = dst.data()


        self.assertTrue([0]+src_data == dst_data or src_data == dst_data)

    def test_without_enough_data(self):
        src_data = [1, 2, 3]
        src = blocks.vector_source_c(src_data)
        thr = burst_streamer(10, 10, 1)
        dst = blocks.vector_sink_c()
        self.tb.connect(src, thr, dst)

        start_time = time.perf_counter()
        self.tb.run()
        end_time = time.perf_counter()

        total_time = end_time - start_time
        self.assertGreater(total_time, 0.9)
        self.assertLess(total_time, 1.1)

        dst_data = dst.data()

        self.assertTrue([0]+src_data+[0]*6 == dst_data or src_data+[0]*7 == dst_data)


if __name__ == '__main__':
    gr_unittest.run(qa_burst_streamer)
