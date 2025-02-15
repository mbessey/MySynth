#include <math.h>
#include "WaveTable.h"

float WaveTable::Process() {
  // to figure out where you are in the waveform:
  // total sample count / sample rate == time
  // each run through the table is one wave, so 
  // time * freq = number of cycles
  // (cycles * 256) % 256 = position in cycle
  int index = (int)floor((_sample++ / _sr) * _freq * num_samples) % 256;
  float val = (sample[index] - 127.0)/128.0;
  return val * _amp;
}

WaveTable::WaveTable () {
  
}

WaveTable::~WaveTable() {

}

void WaveTable::Init(float sample_rate) {
  _sr = sample_rate;
  _sample = 0;
  SetSinWave();
}

void WaveTable::Reset() {
  _sample = 0;
}

void WaveTable::SetAmp(float a) {
  _amp = a;
}

void WaveTable::SetFreq(const float freq) {
  _freq = freq;
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
    sample[i] = sin(i*M_PI*2/num_samples) * 127 + 127;
  }
}

void WaveTable::SetTriWave() {
  for (int i = 0; i < num_samples/2; i++) {
    sample[i] = 255-i*2; 
    sample[i+num_samples/2] = i*2;
  }
}

void WaveTable::SetSawWave() {
  for (int i = 0; i < num_samples; i++) {
    sample[i] = 255 - i;
  }
}

void WaveTable::SetRampWave() {
  for (int i = 0; i < num_samples; i++) {
    sample[i] = i;
  }
}

void WaveTable::SetSquareWave() {
  for (int i = 0; i < num_samples/2; i++) {
    sample[i] = 255;
  }
  for (int i = num_samples/2; i < num_samples; i++) {
    sample[i] = 0;
  }
}
