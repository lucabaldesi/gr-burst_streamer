/* -*- c++ -*- */
/*
 * Copyright 2021 luca baldesi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "burst_streamer_impl.h"
#include <gnuradio/io_signature.h>
#include <thread>

namespace gr {
namespace burst_streamer {

using data_type = gr_complex;
burst_streamer::sptr burst_streamer::make(double samp_rate, int max_outputs, int zero_burst_len)
{
    return gnuradio::make_block_sptr<burst_streamer_impl>(samp_rate, max_outputs, zero_burst_len);
}


/*
 * The private constructor
 */
burst_streamer_impl::burst_streamer_impl(double samp_rate, int max_outputs, int zero_burst_len)
    : gr::block("burst_streamer",
                gr::io_signature::make(
                    1 /* min inputs */, 1 /* max inputs */, sizeof(data_type)),
                gr::io_signature::make(
                    1 /* min outputs */, 1 /*max outputs */, sizeof(data_type)))
{
    d_start = std::chrono::steady_clock::now();
    d_sample_rate = samp_rate;
    d_total_samples = 0;
    d_sample_period = std::chrono::duration<double>(1 / samp_rate);
    d_max_outputs = max_outputs;
    d_zero_burst_len = zero_burst_len;
}

/*
 * Our virtual destructor.
 */
burst_streamer_impl::~burst_streamer_impl() {}

void burst_streamer_impl::forecast(int noutput_items,
                                   gr_vector_int& ninput_items_required)
{
    ninput_items_required[0] = 0;
}

int burst_streamer_impl::general_work(int noutput_items,
                                      gr_vector_int& ninput_items,
                                      gr_vector_const_void_star& input_items,
                                      gr_vector_void_star& output_items)
{
    const data_type* in = reinterpret_cast<const data_type*>(input_items[0]);
    data_type* out = reinterpret_cast<data_type*>(output_items[0]);

    if (d_max_outputs > 0 && d_total_samples >= d_max_outputs)
        return WORK_DONE;

    if (ninput_items[0] > 0) {
        noutput_items = ninput_items[0];
        std::memcpy(out, in, noutput_items * sizeof(data_type));
        consume_each(noutput_items);
    } else {
        noutput_items = d_zero_burst_len;
        std::memset(out, 0, noutput_items * sizeof(data_type));
        consume_each(0);
    }

    d_total_samples += noutput_items;
    auto now = std::chrono::steady_clock::now();
    auto expected_time = d_start + d_sample_period * d_total_samples;

    if (expected_time > now) {
        auto limit_duration =
            std::chrono::duration<double>(std::numeric_limits<long>::max());
        if (expected_time - now > limit_duration) {
            GR_LOG_ALERT(d_logger,
                         "WARNING: Throttle sleep time overflow! You "
                         "are probably using a very low sample rate.");
        }
        std::this_thread::sleep_until(expected_time);
    }

    return noutput_items;
}

} /* namespace burst_streamer */
} /* namespace gr */
