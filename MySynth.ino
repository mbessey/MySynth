// An 8-bit wavetable (sort of) synth voice

#include "DaisyDuino.h"
#include "WaveTable.h"

static DaisyHardware pod;
static MoogLadder flt;
static AdEnv ad;
static WaveTable waveTable;
static Oscillator osc;
static float sample_rate, callback_rate;
static int wave;

float NextSample() {
  float ad_out = ad.Process();
  float sig = waveTable.Process();
  // sig = flt.Process(sig);
  sig *= ad_out;
  return sig;
}

void setWaveLED(const int wave) {
  switch (wave) {
    case WaveTable::WAVE_SIN: // RED
      pod.leds[0].Set(true, false, false);
      break;
    case WaveTable::WAVE_TRI: // GREEN
      pod.leds[0].Set(false, true, false);
      break;
    case WaveTable::WAVE_SAW: // BLUE
      pod.leds[0].Set(false, false, true);
      break;
    case WaveTable::WAVE_RAMP: // PURPLE
      pod.leds[0].Set(true, false, true);
      break;
    case WaveTable::WAVE_SQUARE: // ORANGE
      pod.leds[0].Set(true, true, false);
      break;
    default:
      pod.leds[0].Set(true, true, true);
      break;
  }
}

void ProcessButtons() {
    if (pod.buttons[0].RisingEdge()) {
      ad.Trigger();
    }
    if (pod.buttons[1].RisingEdge()) {      
      wave = (wave +1) % WaveTable::WAVE_LAST;
      waveTable.SetWaveform(wave);
      osc.SetWaveform(wave);
      setWaveLED(wave);
    }
}

void ProcessControls() {
    pod.ProcessAllControls();
    ProcessButtons();
}

void MyCallback(float **in, float **out, size_t size) {
  ProcessControls();
  
  for (size_t i = 0; i < size; i++) {
    float sig = NextSample();

    out[0][i] = sig;
    out[1][i] = sig;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  wave = WaveTable::WAVE_SIN;

  pod = DAISY.init(DAISY_POD, AUDIO_SR_48K); 
  setWaveLED(wave);
  pod.leds[1].Set(true, false, false);
  sample_rate = DAISY.get_samplerate();
  callback_rate = DAISY.get_callbackrate();

  //Init everything
  osc.Init(sample_rate);
    osc.SetWaveform(wave);
    osc.SetFreq(440);
    osc.SetAmp(1);
  waveTable.Init(sample_rate);
    waveTable.SetWaveform(wave);
    waveTable.SetFreq(440);
    waveTable.SetAmp(1);
  flt.Init(sample_rate);
  ad.Init(sample_rate);

  //Set filter parameters
  flt.SetFreq(10000);
  flt.SetRes(0.8);

  //Set envelope parameters
  ad.SetTime( ADENV_SEG_ATTACK, 0.01);
  ad.SetTime( ADENV_SEG_DECAY, .2);
  ad.SetMax(1);
  ad.SetMin(0);
  ad.SetCurve(0.5);
  
  //start the audio callback
  DAISY.begin(MyCallback);
}

void loop() {
  // put your main code here, to run repeatedly:
  // nothing here - Daisy does it all in the Daisy callback...
  if (pod.encoder.RisingEdge()) {
    waveTable.DumpWave();
  }
}
