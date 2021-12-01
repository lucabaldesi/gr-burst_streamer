/* -*- c++ -*- */
/*
 * Copyright 2021 luca baldesi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BURST_STREAMER_BURST_STREAMER_H
#define INCLUDED_BURST_STREAMER_BURST_STREAMER_H

#include <gnuradio/block.h>
#include <burst_streamer/api.h>

namespace gr {
namespace burst_streamer {

/*!
 * \brief Stream data at constant rate. If there is input, stream from it. Stream zeros otherwise.
 * \ingroup burst_streamer
 *
 */
class BURST_STREAMER_API burst_streamer : virtual public gr::block
{
public:
    typedef std::shared_ptr<burst_streamer> sptr;

    static sptr make(double samp_rate, int max_outputs = -1, int zero_burst_len = 1);
};

} // namespace burst_streamer
} // namespace gr

#endif /* INCLUDED_BURST_STREAMER_BURST_STREAMER_H */
