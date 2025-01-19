#include <math.h>
#include <cstdint>
#ifndef WAVETABLE_H
  class WaveTable {
    public: 
    enum WaveType {
          WAVE_SIN,
          WAVE_TRI,
          WAVE_SAW,
          WAVE_RAMP,
          WAVE_SQUARE,
          WAVE_LAST
    };

    float Process();
    WaveTable ();
    ~WaveTable();

    void Init(float sample_rate);
    void Reset();
    void SetAmp(const float a);
    void SetFreq(const float freq);
    void SetWaveform(int w);

    private:
    static const int num_samples = 256;
    float _sr;
    uint8_t sample[num_samples];
    int _index;
    int _step;
    float _amp = 1.0;
    void SetSinWave();
    void SetTriWave();
    void SetSawWave();
    void SetRampWave();
    void SetSquareWave();
  };
  #define WAVETABLE_H
#endif
