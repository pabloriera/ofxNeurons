 #ifndef NEURONA
    #define NEURONA

    #include "ofMain.h"
    #include <vector>
    #include "ofxOsc.h"
    #include "scope.h"

    class Neurona {
    public:
        Neurona();

        void currentBuffer(float w, float d,vector<float>* buff);
        void reset();

        void setup(float visEvent_height);
        bool update();

        void OSCevent(ofxOscSender* sender);

        void drawCircle();
        void drawEvent();

        void FRset(float Fc,float Q);
        void FRcalc();

        int instance;

        scope Vscope;
        scope FRscope;

        //Visualization
        ofColor color;

        ofVec2f visEvent_pos;
        ofVec2f visCircle_pos;

        float visEvent_width;
        float visEvent_height;

        //Izhikevich
        float a,b,c,d;

        float t;
        float dt;
        float V,u;

        //Synaptic variables
        float sp,s0;
        float tau;

        //vector buffers
        vector<float> sp_buff;
        int sp_bufferSize;

        int syn_type;
        bool fix_syn_type;

        float maxV,minV;
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

        float FR;

        //Circle visualization
        float vis_circle_radio;
        float vis_circle_radio0;

        //Event visualization
        float event_pos;
        float event_vel;
        float event_vis_width;
        float event_vis_height;
        bool event;
        bool event_draw;

        vector<float> event_vector;

    };
    #endif
