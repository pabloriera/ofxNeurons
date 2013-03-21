 #ifndef SINAPSIS
    #define SINAPSIS

    #include "ofMain.h"

    class Sinapsis {
    public:
        Sinapsis();

        void update(float i, float j);

        void random_weigth(float min, float max);

        void draw();

        ofColor color;

        float weigth, delay;


    };
    #endif
