#include "neurona.h"

    Neurona::Neurona(){

    }

    void Neurona::setup(float _visEvent_height){

        visEvent_height = _visEvent_height;
        vis_circle_radio0 = visEvent_height*0.3;

        visEvent_width = ofGetWindowWidth()*.4;



        sp_bufferSize = 8192;
        for (int i=0;i < sp_bufferSize;i++)
            sp_buff.push_back(0.0f);

        sp_buff.assign(sp_bufferSize,0.0);
        //cout <<"SETUP_size= "<< sp_buff.size() << endl;

        vis_circle_radio0 = visEvent_height/8.0;
        vis_circle_radio0 = MAX(4,vis_circle_radio0);
        vis_circle_radio = vis_circle_radio0 ;

        event_pos = 0;
        event_vel = 1;
        event_vis_width = 1;
        event_vis_height = visEvent_height*0.9;
        event = false;

        Vscope.setup();
        Vscope.color = &color;

        FRscope.setup();
        FRscope.color = &color;

        dt = 0.01;
        dc = 0;
        syn_type = -1;

        fr.Fs = 1/dt;
        FRset(.1,1);

        reset();
    }

    bool Neurona::update(){

        I = dc + Ibuf;

        float maxIdt = 50;

        if (I*dt > maxIdt)
            I = maxIdt/dt;

        V = V + (0.04*V*V + 5*V + 140 - u + I)*dt;
        u = u + a*(b*V-u)*dt;

        Vscope.update(ofMap(V,minV,maxV,0,1));

        event = false;

        if (V > maxV)
        {
            //cout << "event" << "\n";
            event = true;
            event_draw = true;
            V = c;
            u = u + d;
            s0 = syn_type;
        }

        FRcalc();
        FRscope.update(ofMap(FR,0,5,0,1));

        sp = sp - sp*dt/tau;
        sp = sp + s0;

        //if (sp<0.00001)
         //   sp = 0.0;

        for(int i = 0; i<sp_bufferSize-1;i++)
            sp_buff[i]=sp_buff[i+1];
        sp_buff[sp_bufferSize-1] = sp;

        //cout << "UPDATE_size=" << sp_buff.size() << endl;

        if(ofGetKeyPressed(OF_KEY_PAGE_UP))
        {
            cout << "sp=" << sp << "\tSP_BUFF ";

            for(int i =sp_bufferSize; i > sp_bufferSize-10;i--)
            {
                cout << sp_buff[i] << "\t";
            }
            cout << endl;

        }

        s0 = 0;
        Ibuf = 0;

        return event;
    }

    void Neurona::currentBuffer(float w, float d, vector<float>* buff){

        if(ofGetKeyPressed(OF_KEY_PAGE_DOWN))
        {
            cout << "w=" << w << "\td=" << d << endl;
            cout << "dpos=" << sp_bufferSize - MIN(sp_bufferSize, d) -1;
            cout << "\t at(end)"<< buff->at(buff->size()-1);
            cout << "\t size"<< buff->size();

            cout << "\t buff=" << buff->at((size_t)(sp_bufferSize - MIN(sp_bufferSize, d )-1))  << endl;
        }

        Ibuf += w * buff->at((size_t)(sp_bufferSize - MIN(sp_bufferSize, d) - 1 ));
    }

    void Neurona::reset(){

        //Iz parameters
        t=0;
        maxV = 30;
        minV = -80;


        a = 0.02;
        b = 0.2;
        c = -65;
        d = 8;
        V = -65;
        u = b*V;

        //Synaptic variables
        sp = 0;
        s0 = 0;
        tau = 1;

        // The neuron only behaves as excitatory or inhibotry if true. If false, it can behave both ways
        fix_syn_type = true;

        fr.v.assign(4, 0.0);

        event_vector.clear();
        sp_buff.assign(sp_bufferSize,0);

        Vscope.reset();
        FRscope.reset();
        }

    void Neurona::OSCevent(ofxOscSender* sender){
        ofxOscMessage m;
		m.setAddress("/neuron");
		m.addIntArg(instance);
		sender->sendMessage(m);
    }

    void Neurona::FRset(float Fc,float Q){

        //Set low pass filter parameters
        fr.Fc = Fc;
        fr.W = tan(PI*Fc/fr.Fs);
        fr.N = 1/(pow(fr.W,2) + fr.W/Q + 1);
        fr.B_0 = fr.N*pow(fr.W,2);
        fr.B1 = 2*fr.B_0;
        fr.B2 = fr.B_0;
        fr.A1 = 2*fr.N*(pow(fr.W,2) - 1);
        fr.A2 = fr.N*(pow(fr.W,2) - fr.W/Q + 1);

 //  cout << fr.W << ",  " << fr.N << ",  " << fr.B_0 << ",  " << fr.B1 << ",  " << fr.B2 << ",  " << fr.A1 << ",  " << fr.A2 << ",  " << Fc << "\n";
    }

    void Neurona::FRcalc(){

        //Calculate FR

        float out;
        float in;
        in = (float) event;

        //Low pass filter 2nd order
        out = 100*in*fr.B_0 + fr.v[0]*fr.B1 + fr.v[1]*fr.B2 - fr.v[2]*fr.A1 - fr.v[3]*fr.A2;
        fr.v[3] = fr.v[2];
        fr.v[2] = out;
        fr.v[1] = fr.v[0];
        fr.v[0] = in;

        FR = out;
//        if (fr.v[3] < fr.v[2]) FRset(fr.Fc*=1.1,0.5);
//        else FRset(fr.Fc*=0.9,0.5);

        //cout << in <<  ",  "<< out << "\n";

    }

    void Neurona::drawCircle(){

        ofFill();
        ofSetColor(color, 255*ofNormalize(V,-100,30) );
        vis_circle_radio = 0.95f * vis_circle_radio + ofMap(V,-65,30,0,visEvent_height/2.0f) * 0.05f;
        //cout << tamanio << "\n";
        ofCircle(visCircle_pos.x, visCircle_pos.y, vis_circle_radio+vis_circle_radio0);
        //ofCircle(vis_pos.x, vis_pos.y, 10);
    }

    void Neurona::drawEvent(){

        ofFill();
        ofSetColor(color);

        event_pos += event_vel;

        if(event_pos>visEvent_width){
            event_pos = 0;
            event_vector.clear();
            //cout << "clearMaxvis_pos" << "\n";
        }

        if(event_draw){

         //   cout << xvis_pos + vis_pos.x << "\n";

            event_vector.push_back (event_pos + visEvent_pos.x);
           // cout << "hola" <<"\n";
            //cout << "size, " << event_vector.size() << "\n";

        }


        for(size_t i=0; i< event_vector.size(); i++){
            ofRect(event_vector[i], visEvent_pos.y, event_vis_width , event_vis_height);
        }

        event_draw = false;
        //ofCircle(vis_pos.x, vis_pos.y, 10);
    }
