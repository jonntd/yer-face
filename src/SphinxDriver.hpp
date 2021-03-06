#pragma once

#include "Logger.hpp"
#include "FrameDerivatives.hpp"
#include "FFmpegDriver.hpp"

namespace PocketSphinx {
extern "C" {
#include <pocketsphinx.h>
}
} //Namespace PocketSphinx

using namespace std;

namespace YerFace {

class SphinxAudioFrame {
public:
	uint8_t *buf;
	int pos;
	int audioSamples;
	int audioBytes;
	int bufferSize;
	double timestamp;
	bool inUse;
};

class SphinxPhoneme {
public:
	string symbol;
	bool used;
	PocketSphinx::int32 startFrame, endFrame;
	double startTime, endTime;
	int utteranceIndex;
};

class SphinxDriver {
public:
	SphinxDriver(string myHiddenMarkovModel, string myAllPhoneLM, FrameDerivatives *myFrameDerivatives, FFmpegDriver *myFFmpegDriver);
	~SphinxDriver();
	void advanceWorkingToCompleted(void);
	void renderPreviewHUD(void);
private:
	void initializeRecognitionThread(void);
	void destroyRecognitionThread(void);
	void updateRecognizedPhonemes(void);
	static int runRecognitionLoop(void *ptr);
	SphinxAudioFrame *getNextAvailableAudioFrame(int desiredBufferSize);
	static void FFmpegDriverAudioFrameCallback(void *userdata, uint8_t *buf, int audioSamples, int audioBytes, int bufferSize, double timestamp);
	
	string hiddenMarkovModel, allPhoneLM;
	FrameDerivatives *frameDerivatives;
	FFmpegDriver *ffmpegDriver;

	Logger *logger;

	PocketSphinx::ps_decoder_t *pocketSphinx;
	PocketSphinx::cmd_ln_t *pocketSphinxConfig;
	
	SDL_mutex *myWrkMutex, *myCmpMutex;
	SDL_cond *myWrkCond;
	SDL_Thread *recognizerThread;

	bool recognizerRunning;
	bool utteranceRestarted, inSpeech;
	int utteranceIndex;
	double timestampOffset;
	bool timestampOffsetSet;

	list<SphinxAudioFrame *> audioFrameQueue;
	list<SphinxAudioFrame *> audioFramesAllocated;

	list<SphinxPhoneme *> recognizedPhonemes;
};

}; //namespace YerFace
