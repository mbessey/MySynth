#include <math.h>

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

  float Process() {
    float val = (float)sample[_index] / 128.0;
    _index = (_index + _step) % num_samples;
    return val * _amp;
  }

  WaveTable () {
    
  }

  ~WaveTable() {

  }

  void Init(float sample_rate) {
    _sr = sample_rate;
    _index = 0;
    _step = 1;
    SetSinWave();
  }

  void Reset() {
    _index = 0;
  }

  void SetAmp(float a) {
    _amp = a;
  }

  void SetFreq(const float freq) {
    _step = num_samples / (_sr / freq);
  }

  void SetWaveform(int w) {
    switch (w) {
      case WAVE_SIN:
        SetSinWave();
        break;      
      case WAVE_TRI:
        SetTriWave();
        break;      
      case WAVE_SAW:
        SetSawWave();
        break;      
      case WAVE_RAMP:
        SetRampWave();
        break;      
      case WAVE_SQUARE:
        SetSquareWave();
        break;      
    }
  }

  void DumpWave() {
    for (int i = 0; i < num_samples; i++) {
      float mine = Process();
      for (int j =0; j < 10; j++) {
        Process();
      }
      Serial.print("mine:");
      Serial.println(mine);
    }
  }
  private:
  static const int num_samples = 256;
  float _sr;
  signed char sample[num_samples];
  int _index;
  int _step;
  float _amp = 1.0;

  void SetSinWave() {
    for (int i = 0; i < num_samples; i++) {
      sample[i] = sin(i*M_PI*2/num_samples) * 127;
    }
  }

  void SetTriWave() {
    for (int i = 0; i < num_samples/2; i++) {
      sample[i] = (i*2-127);
      sample[i+num_samples/2] = (127-i*2);
    }
  }

  void SetSawWave() {
    for (int i = 0; i < num_samples; i++) {
      sample[i] = i;
    }
  }

  void SetRampWave() {
    for (int i = 0; i < num_samples; i++) {
      sample[i] = i - 128;
    }
  }

  void SetSquareWave() {
    for (int i = 0; i < num_samples/2; i++) {
      sample[i] = 127;
    }
    for (int i = num_samples/2; i < num_samples; i++) {
      sample[i] = -127;
    }
  }
};
