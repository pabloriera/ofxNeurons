#ifndef RED_NEURONAS
    #define RES_NEURONAS

    #include "neurona.h"
    #include <vector>
    #include "sinapsis.h"

    float drand();
    float random_normal();

    class Red_Neuronas {
    public:
        Red_Neuronas();

        void setup(int TOTAL);
        void update();
        void reset();
        void draw();

        void set_dts(float dt);
        void set_currents(float dc_mean, float dc_std);

        void set_syn_w_matrix(float type_prop,float syn_w_mean, float syn_w_weigth);
        void set_syn_d_matrix(float syn_d_mean, float syn_d_weigth);

        void togg_syn_matrix();

        void set_osc_server(ofxOscSender* _sender);
        bool osc_enable;

        vector <Neurona> Neuronas;
        vector<vector<Sinapsis> > Matrix_Sinapsis;

        int TOTAL;
        bool drawVoltage;
        bool drawEvent;
        bool drawFR;
        bool drawCircle;
        bool bool_syn_matrix;

        ofxOscSender sender;
    };
#endif
