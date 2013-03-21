 #ifndef NEURONA
    #define NEURONA

    #include "ofMain.h"
    #include <vector>
    #include "ofxOsc.h"


    class Neurona {
    public:
        Neurona();

        void currentBuffer(float _I);
        void reset();

        bool update();  // el update quitará vida y limitará el movimiento
        void random_dc(float _min, float _max);
        void OSCevent(ofxOscSender* sender);

        void drawCircle();
        void drawEvent();
        void drawVoltage();
        void drawFR();

        void FRset(float Fc,float Q);
        void FRcalc();

        int instance;

        //Visualization
        ofColor vis_color;

        ofVec2f visEvent_pos;
        ofVec2f visVoltaje_pos;
        ofVec2f visFR_pos;
        ofVec2f visCircle_pos;

        float visEvent_width;
        float visEvent_height;

        float visFR_width;
        float visFR_height;

        float visVoltaje_width;
        float visVoltaje_height;

        //Izhikevich
        float a,b,c,d;

        float t;
        float dt;
        float V,u;

        //Synaptic variables
        float sp,s0;
        float tau;

        float maxV;
        float dc;
        float I,Ibuf;

        struct s_fr{

            vector<float> v;
            float W;
            float N;
            float B_0;
            float B1;
            float B2;
            float A1;
            float A2;
            float Fs;
            float Fc;

        } fr;

        //Voltage visualization

        unsigned int VbufferSize;
        unsigned int FRbufferSize;

        //vector buffers
        vector<float> Vbuff;
        vector<float> FRbuff;

        float voltaje_vis_height;

        //Circle visualization
        float vis_circle_radio;
        float vis_circle_radio0;

        //Event visualization
        float event_pos;
        float event_vel;
        float event_vis_width;
        float event_vis_height;
        bool event;

        vector<float> event_vector;

    };
    #endif
