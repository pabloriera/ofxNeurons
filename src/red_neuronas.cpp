#include "red_neuronas.h"
#include "neurona.h"
#include "sinapsis.h"

Red_Neuronas::Red_Neuronas(){

}

void Red_Neuronas::setup(int _TOTAL)
{
    TOTAL = _TOTAL;
    Neuronas.assign(TOTAL,Neurona());

    Matrix_Sinapsis.assign(TOTAL, vector<Sinapsis>(TOTAL));

    float wh = ofGetWindowHeight()*.9;

    float visEvent_height = wh/(float)TOTAL;

    for(int i = 0; i < TOTAL; i++)
    {
        Neuronas[i].setup(visEvent_height);

        Neuronas[i].visCircle_pos.set( 50, 10+i*visEvent_height*1.05+visEvent_height*0.5);
        Neuronas[i].visEvent_pos.set( 100, 10 + i*visEvent_height*1.05);

        Neuronas[i].Vscope.pos.set(550, 10 + i*visEvent_height*1.05);
        Neuronas[i].Vscope.width = ofGetWidth() * 0.45;
        Neuronas[i].Vscope.height = visEvent_height;

        Neuronas[i].FRscope.pos.set(550, 10 + i*visEvent_height*1.05);
        Neuronas[i].FRscope.width = ofGetWidth() * 0.45;
        Neuronas[i].FRscope.height = visEvent_height;

        Neuronas[i].instance = i;
    }

    drawVoltage=true;

    drawEvent=true;

    drawCircle=true;

    drawFR=false;

    bool_syn_matrix = true;
}

void Red_Neuronas::update()
{

    for(int i = 0; i < TOTAL; i++)
        if(Neuronas[i].update())
            Neuronas[i].OSCevent(&sender);

    if (bool_syn_matrix)
        for(int i = 0; i < TOTAL; i++)
            for(int j = 0; j < TOTAL; j++)
            {
                if (i!=j)
                    Neuronas[j].currentBuffer( Matrix_Sinapsis[i][j].weigth, Matrix_Sinapsis[i][j].delay, &Neuronas[i].sp_buff );
            }
}

void Red_Neuronas::draw()
{
    for(int i = 0; i < TOTAL; i++){

        if (drawEvent)
            Neuronas[i].drawEvent();

        if (drawVoltage)
            Neuronas[i].Vscope.draw();

        if (drawFR)
            Neuronas[i].FRscope.draw();

        if (drawCircle)
            Neuronas[i].drawCircle();
    }
}

void Red_Neuronas::set_currents(float dc_mean, float dc_std)
{
    for(int i = 0; i < TOTAL; i++)
        Neuronas[i].dc = dc_mean + dc_std*random_normal();
}

void Red_Neuronas::set_dts(float dt)
{
    for(int i = 0; i < TOTAL; i++)
        Neuronas[i].dt = dt;
}

void Red_Neuronas::set_syn_w_matrix(float type_prop, float syn_w_mean, float syn_w_std)
{
    for(int i = 0; i < TOTAL; i++)
    {
        Neuronas[i].syn_type = (i < type_prop*TOTAL)*2-1;

        ofColor aux_color;
        aux_color.setHsb((-Neuronas[i].syn_type+1)/2 * 50.0,(-Neuronas[i].syn_type+1)/2 * 50.0,(Neuronas[i].syn_type+1)/2 * 50.0 + 50.0 );


        Neuronas[i].color = aux_color;

        for(int j = 0; j < TOTAL; j++)
        {
            if (i!=j)
            {
                float aux = syn_w_mean + syn_w_std*random_normal();
                aux = MAX(aux,0);
                Matrix_Sinapsis[i][j].weigth = aux;
                }
        }
    }
}

void Red_Neuronas::set_syn_d_matrix(float syn_d_mean, float syn_d_std)
{
    for(int i = 0; i < TOTAL; i++)
    {
        for(int j = 0; j < TOTAL; j++)
        {
            if (i!=j)
            {
                float aux = syn_d_mean + syn_d_std*random_normal();
                aux = floor( MAX(aux,0) );
                Matrix_Sinapsis[i][j].delay = aux;
            }
        }
    }
}


void Red_Neuronas::togg_syn_matrix()
{
    bool_syn_matrix = !bool_syn_matrix;
}

void Red_Neuronas::reset()
{
    for(int i = 0; i < TOTAL; i++){
        Neuronas[i].reset();
    }
}


void Red_Neuronas::set_osc_server(ofxOscSender* _sender)
{
    sender = *_sender;
}

float drand()   /* uniform distribution, (0..1] */
{    return (rand()+1.0)/(RAND_MAX+1.0);   }

float random_normal()  /* normal distribution, centered on 0, std dev 1 */
{    return sqrt(-2*log(drand())) * cos(2*M_PI*drand());    }

