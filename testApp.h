#pragma once

#include "ofMain.h"
#include "neurona.h"
#include "sinapsis.h"
#include "ofxMSATimer.h"
#include "ofxOsc.h"



#define HOST "127.0.0.1"
#define PORT 12345

#define TOTAL 3

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

        Neurona  nn[TOTAL];
        Sinapsis ss[TOTAL][TOTAL];

        float DT;

        int aux;
        ofxMSATimer timer;
        ofxOscSender sender;

};
