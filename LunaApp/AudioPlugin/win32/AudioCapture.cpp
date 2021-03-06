#include "AudioCapture.hpp"

#include <stdexcept>

#include "SampleBuffer.hpp"
#include "win32errorhandling.h"

AudioCapture::AudioCapture()
{
    CoInitializeEx(0, COINIT_MULTITHREADED);
}

AudioCapture::~AudioCapture() {
    CoUninitialize();
}

void AudioCapture::configure() {
    HRESULT hr;
    hr = CoCreateInstance(
         __uuidof(MMDeviceEnumerator),
         NULL,
         CLSCTX_ALL,
         __uuidof(IMMDeviceEnumerator),
         (void **)mDevEnum.ReleaseAndGetAddressOf());
    testHR(hr);

    hr = mDevEnum->GetDefaultAudioEndpoint(eRender, eMultimedia,
                                           mAudioDevice.ReleaseAndGetAddressOf());
    testHR(hr);

    mAudioDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL,
                           (void **)mAudioClient.ReleaseAndGetAddressOf());
    testHR(hr);

    WAVEFORMATEX * tempFormat;
    hr = mAudioClient->GetMixFormat(&tempFormat);
    mFormat = formatPtr_t(tempFormat);
    testHR(hr);

    // TODO support non floating point formats
    if (mFormat->wFormatTag != WAVE_FORMAT_IEEE_FLOAT) {
        if (mFormat->wFormatTag != WAVE_FORMAT_EXTENSIBLE) {
            throw std::runtime_error("Unsupported audio format");
        }
        WAVEFORMATEXTENSIBLE * format = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(mFormat.get());
        if (format->SubFormat != KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) {
            throw std::runtime_error("Unsupported audio format (non-float)");
        }
    }

    REFERENCE_TIME length = static_cast<REFERENCE_TIME>(10000000 * 1.2 / 100);
    mAudioClient->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        AUDCLNT_STREAMFLAGS_LOOPBACK,
        length,
        0, mFormat.get(), NULL);
    testHR(hr);

    hr = mAudioClient->GetService(__uuidof(IAudioCaptureClient),
                                  (void **)mAudioCaptureClient.ReleaseAndGetAddressOf());
    testHR(hr);

    hr = mAudioClient->Start();
    testHR(hr);
}

size_t AudioCapture::channels() const
{
	return mFormat->nChannels;
}

uint32_t AudioCapture::sampleRate() const {
    return mFormat->nSamplesPerSec;
}

uint32_t AudioCapture::readSamples(SampleBuffer * buffer) {
    uint32_t total = 0;
    HRESULT hr;
    uint32_t packetSize;
    hr = mAudioCaptureClient->GetNextPacketSize(&packetSize);
    testHR(hr);
    while (packetSize != 0) {
        uint32_t framesAvailable;
        uint8_t * data;
        DWORD flags;
        hr = mAudioCaptureClient->GetBuffer(&data, &framesAvailable, &flags, nullptr, nullptr);

        total += framesAvailable;
        buffer->readFrom(reinterpret_cast<float *>(data), framesAvailable);

        mAudioCaptureClient->ReleaseBuffer(framesAvailable);
        hr = mAudioCaptureClient->GetNextPacketSize(&packetSize);
        testHR(hr);
    }
    return total;
}
