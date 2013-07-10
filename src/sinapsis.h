 #ifndef SINAPSIS
    #define SINAPSIS

    #include "ofMain.h"

    class Sinapsis {
    public:
        Sinapsis();

        void set(float w, float d);
        void update(float i, float j);

        void random_weigth(float min, float max);

        ofColor color;

        float weigth, delay;
    };
    #endif
