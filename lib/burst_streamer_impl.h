/* -*- c++ -*- */
/*
 * Copyright 2021 luca baldesi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BURST_STREAMER_BURST_STREAMER_IMPL_H
#define INCLUDED_BURST_STREAMER_BURST_STREAMER_IMPL_H

#include <burst_streamer/burst_streamer.h>

namespace gr {
namespace burst_streamer {

class burst_streamer_impl : public burst_streamer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> d_start;
    double d_sample_rate;
    uint64_t d_total_samples;
    std::chrono::duration<double> d_sample_period;
    int d_max_outputs;
    int d_zero_burst_len;

public:
    burst_streamer_impl(double samp_rate, int max_outputs, int zero_burst_len);
    ~burst_streamer_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace burst_streamer
} // namespace gr

#endif /* INCLUDED_BURST_STREAMER_BURST_STREAMER_IMPL_H */
