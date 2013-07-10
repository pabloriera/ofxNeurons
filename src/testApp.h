#pragma once

#include "ofMain.h"
#include "red_neuronas.h"
#include "ofxOsc.h"
#include "controlFloat.h"

//#define HOST "127.0.0.1"
#define HOST "10.42.0.46"
#define PORT_SEND 12345
#define PORT_RECEIVE 54321

class testApp : public ofBaseApp{
public:
        void setup();
        void update();
        void draw();

        void keyPressed  (int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

        void audioOut(float * input, int bufferSize, int nChannels);

        Red_Neuronas Red;

        float DT;

        int aux;
        int TOTAL;
        float dc_mean;
        float dc_std;

        float type_prop;
        float syn_w_mean;
        float syn_w_std;
        float syn_d_mean;
        float syn_d_std;
        float global_dt;

        ofxOscSender sender;
        ofxOscReceiver receiver;

        int sampleRate;
        int bufferSize;

        ofSoundStream soundStream;

        bool verbose;


};
