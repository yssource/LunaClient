#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <cstdint>
#include <memory>

#include <wrl.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "samplebuffer.h"

class AudioCapture {
public:
    AudioCapture();
    ~AudioCapture();

    void configure(unsigned outputChannels);
    uint32_t sampleRate() const;
    uint32_t readSamples(SampleBuffer * buffer);
private:
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> mDevEnum;
    Microsoft::WRL::ComPtr<IMMDevice> mAudioDevice;
    Microsoft::WRL::ComPtr<IAudioClient> mAudioClient;
    Microsoft::WRL::ComPtr<IAudioCaptureClient> mAudioCaptureClient;
    typedef std::unique_ptr<WAVEFORMATEX, decltype(&CoTaskMemFree)> formatPtr_t;
    formatPtr_t mFormat;
};

#endif // AUDIOCAPTURE_H
