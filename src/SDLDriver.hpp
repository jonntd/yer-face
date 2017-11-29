#pragma once

#include "Logger.hpp"
#include "FrameDerivatives.hpp"

namespace YerFace {

#define YERFACE_PREVIEW_DEBUG_DENSITY_MAX 4

enum PreviewPositionInFrame {
	BottomLeft,
	BottomRight,
	TopRight
};

class SDLWindowRenderer {
public:
	SDL_Window *window;
	SDL_Renderer *renderer;
};

class SDLDriver {
public:
	SDLDriver(FrameDerivatives *myFrameDerivatives);
	~SDLDriver();
	SDLWindowRenderer createPreviewWindow(int width, int height);
	SDLWindowRenderer getPreviewWindow(void);
	SDL_Texture *getPreviewTexture(void);
	void doRenderPreviewFrame(void);
	void doHandleEvents(void);
	void onQuitEvent(function<void(void)> callback);
	void onColorPickerEvent(function<void(void)> callback);
	bool getIsRunning(void);
	void setPreviewPositionInFrame(PreviewPositionInFrame newPosition);
	PreviewPositionInFrame getPreviewPositionInFrame(void);
	void setPreviewDebugDensity(int newDensity);
	int getPreviewDebugDensity(void);
private:
	void handleQuitEvent(void);
	void invokeAll(vector<function<void(void)>> callbacks);

	FrameDerivatives *frameDerivatives;

	Logger *logger;

	bool isRunning;
	PreviewPositionInFrame previewPositionInFrame;
	int previewDebugDensity;

	SDLWindowRenderer previewWindow;
	SDL_Texture *previewTexture;

	vector<function<void(void)>> onQuitCallbacks;
	vector<function<void(void)>> onColorPickerCallbacks;
};

}; //namespace YerFace
