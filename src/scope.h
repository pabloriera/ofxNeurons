 #ifndef SCOPE
    #define SCOPE

    #include "ofMain.h"
    #include <vector>


    class scope {
    public:
        scope();

        void reset();

        void setup();
        void update(float value);

        void draw();
        ofColor* color;

        ofVec2f pos;

        float width;
        float height;

        int bufferSize;
        //vector buffers
        vector<float> buff;

        int buff_downsample_val;
        int buff_downsample_c;

    };
    #endif
