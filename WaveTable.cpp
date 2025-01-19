#include <math.h>
#include "WaveTable.h"

float WaveTable::Process() {
  float val = (float)sample[_index] / 128.0;
  _index = (_index + _step) % num_samples;
  return val * _amp;
}

WaveTable::WaveTable () {
  
}

WaveTable::~WaveTable() {

}

void WaveTable::Init(float sample_rate) {
  _sr = sample_rate;
  _index = 0;
  _step = 1;
  SetSinWave();
}

void WaveTable::Reset() {
  _index = 0;
}

void WaveTable::SetAmp(float a) {
  _amp = a;
}

void WaveTable::SetFreq(const float freq) {
  _step = num_samples / (_sr / freq);
}

void WaveTable::SetWaveform(int w) {
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

void WaveTable::SetSinWave() {
  for (int i = 0; i < num_samples; i++) {
    sample[i] = sin(i*M_PI*2/num_samples) * 127;
  }
}

void WaveTable::SetTriWave() {
  for (int i = 0; i < num_samples/2; i++) {
    sample[i] = (127-i*2); 
    sample[i+num_samples/2] = (i*2-127);
  }
}

void WaveTable::SetSawWave() {
  for (int i = 0; i < num_samples; i++) {
    sample[i] = 127 - i;
  }
}

void WaveTable::SetRampWave() {
  for (int i = 0; i < num_samples; i++) {
    sample[i] = i - 128;
  }
}

void WaveTable::SetSquareWave() {
  for (int i = 0; i < num_samples/2; i++) {
    sample[i] = 127;
  }
  for (int i = num_samples/2; i < num_samples; i++) {
    sample[i] = -127;
  }
}
