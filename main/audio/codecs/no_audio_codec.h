#ifndef _NO_AUDIO_CODEC_H
#define _NO_AUDIO_CODEC_H

#include "audio_codec.h"

#include <driver/gpio.h>
#include <driver/i2s_pdm.h>
#include <atomic>
#include <mutex>

class NoAudioCodec : public AudioCodec {
protected:
    std::mutex data_if_mutex_;

    // Software playback reference used by AFE AEC on boards without a
    // hardware echo-reference path. It stores the samples that are actually
    // sent to the speaker and interleaves them with the microphone data.
    std::mutex reference_mutex_;
    std::vector<int16_t> reference_buffer_;
    size_t reference_read_pos_ = 0;
    size_t reference_write_pos_ = 0;

    virtual int Write(const int16_t* data, int samples) override;
    virtual int Read(int16_t* dest, int samples) override;
    virtual void EnableInput(bool enable) override;
    virtual void EnableOutput(bool enable) override;

    std::atomic<int64_t> last_reference_write_us_{0};
    bool reference_primed_ = false;

    void AppendReference(const int16_t* data, int samples, int32_t volume_factor);
    void PopReference(int16_t* dest, size_t samples, size_t stride);
    size_t GetReferenceBacklog();

public:
    explicit NoAudioCodec(bool input_reference = false);
    virtual ~NoAudioCodec();
    bool has_software_reference() const override { return input_reference_; }
    bool is_playback_active() override;
};

class NoAudioCodecDuplex : public NoAudioCodec {
public:
    NoAudioCodecDuplex(int input_sample_rate, int output_sample_rate, gpio_num_t bclk, gpio_num_t ws, gpio_num_t dout, gpio_num_t din, bool input_reference = false);
};

class NoAudioCodecSimplex : public NoAudioCodec {
public:
    NoAudioCodecSimplex(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, bool input_reference = false);
    NoAudioCodecSimplex(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, i2s_std_slot_mask_t spk_slot_mask, gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, i2s_std_slot_mask_t mic_slot_mask, bool input_reference = false);
};

class NoAudioCodecSimplexPdm : public NoAudioCodec {
public:
    NoAudioCodecSimplexPdm(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mic_sck,  gpio_num_t mic_din);
    NoAudioCodecSimplexPdm(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, i2s_std_slot_mask_t spk_slot_mask, gpio_num_t mic_sck,  gpio_num_t mic_din);
    int Read(int16_t* dest, int samples);
};

#endif // _NO_AUDIO_CODEC_H
