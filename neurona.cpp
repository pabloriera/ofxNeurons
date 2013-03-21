#include "neurona.h"


    Neurona::Neurona(){

        reset();

    }

    bool Neurona::update(){

       // cout << (0.04*V*V+5*V + 140 - u + I)*dt << "\n";
        I = dc + Ibuf;

        V = V + (0.04*V*V + 5*V + 140 - u + I*100)*dt;
        u = u + a*(b*V-u)*dt;


        Vbuff.push_back(ofNormalize(V,-65,40));

        if( (signed) Vbuff.size() >= VbufferSize ){
            Vbuff.erase(Vbuff.begin(), Vbuff.begin()+1);
        }

        event = false;

        if (V > maxV)
            {
                //cout << "event" << "\n";
                event = true;
                V = c;
                u = u + d;
                s0 = 1;
            }

        FRcalc();

        sp = sp - sp*dt/tau;
        sp = sp + s0;

        if (sp<0.00001)
            sp = 0;

        s0 = 0;
        Ibuf = 0;

        return event;

    }

    void Neurona::currentBuffer(float _I){
        Ibuf += _I;
    }

    void Neurona::random_dc(float _min,float _max){
        dc = ofRandom(_min,_max);
    }

    void Neurona::reset(){

        //Iz parameters
        t=0;
        dt = 0.1;
        maxV = 30;

        a = 0.02;
        b = 0.2;
        c = -65;
        d = 8;
        V = -65;
        u = b*V;

        //Synaptic variables
        sp = 0;
        s0 = 0;
        tau = 0.01;

        //Visualizations
        VbufferSize = 256;
        FRbufferSize = 256;

        fr.v.assign(4, 0.0);
        FRbuff.assign(VbufferSize, 0.0);
        Vbuff.assign(VbufferSize, 0.0);

        fr.Fs = 1/dt;
        FRset(.05,1);

        vis_color.set(ofRandom(255),ofRandom(255),ofRandom(255));
        vis_circle_radio0 = visEvent_height/2.0;
        vis_circle_radio = vis_circle_radio0 ;

        event_pos = 0;
        event_vel = .5;
        event_vis_width = 5;
        event_vis_height = visEvent_height*0.9;
        event = false;

        event_vector.clear();

         cout <<"reset" << "\n";

        }

    void Neurona::OSCevent(ofxOscSender* sender){
        ofxOscMessage m;
		m.setAddress("/neuron");
		m.addIntArg(instance);
		//m.addFloatArg(3.5f);
		//m.addStringArg("hello");
		//m.addFloatArg(ofGetElapsedTimef());
		sender->sendMessage(m);
    }

    void Neurona::FRset(float Fc,float Q){

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

        out = in*fr.B_0 + fr.v[0]*fr.B1 + fr.v[1]*fr.B2 - fr.v[2]*fr.A1 - fr.v[3]*fr.A2;
        fr.v[3] = fr.v[2];
        fr.v[2] = out;
        fr.v[1] = fr.v[0];
        fr.v[0] = in;

//        if (fr.v[3] < fr.v[2]) FRset(fr.Fc*=1.1,0.5);
//        else FRset(fr.Fc*=0.9,0.5);

        //cout << in <<  ",  "<< out << "\n";

        FRbuff.push_back(ofNormalize(out,0,0.05));

        if( (signed) FRbuff.size() >= FRbufferSize ){
            FRbuff.erase(FRbuff.begin(), FRbuff.begin()+1);
        }
    }

    void Neurona::drawCircle(){

        ofFill();
        ofSetColor(vis_color, 255*ofNormalize(V,-65,30) );
        vis_circle_radio = vis_circle_radio + (ofNormalize(V,-65,30)*visEvent_height*0.5-vis_circle_radio)*.2;
        //cout << tamanio << "\n";
        ofCircle(visCircle_pos.x, visCircle_pos.y, vis_circle_radio+vis_circle_radio0);
        //ofCircle(vis_pos.x, vis_pos.y, 10);
    }

    void Neurona::drawVoltage(){

        //ofSetColor(vis_color, 255*ofNormalize(V,-65,30));
        int auxS = Vbuff.size();

        ofSetColor(vis_color);

        ofNoFill();

        // draw the left channel:
        ofPushStyle();
            ofPushMatrix();
            ofTranslate(visVoltaje_pos.x, visVoltaje_pos.y, 0);

            ofSetLineWidth(3);

                ofBeginShape();

                for (int i = 0; i < auxS; i++){

                    ofVertex(visVoltaje_pos.x + ((float) i/(float)auxS)*visVoltaje_width, visVoltaje_pos.y + (1-Vbuff[i])*visVoltaje_height);
                }
                ofEndShape(false);

            ofPopMatrix();
        ofPopStyle();


    }

    void Neurona::drawFR(){

        //ofSetColor(vis_color, 255*ofNormalize(V,-65,30));
        int auxS = FRbuff.size();

        ofSetColor(vis_color);

        ofNoFill();

        // draw the left channel:
        ofPushStyle();
            ofPushMatrix();
            ofTranslate(visFR_pos.x, visFR_pos.y, 0);

            ofSetLineWidth(3);

                ofBeginShape();

                for (int i = 0; i < auxS; i++){

                    ofVertex(visFR_pos.x + ((float) i/(float)auxS)*visFR_width, visFR_pos.y + (1-FRbuff[i])*visFR_height);
                }
                ofEndShape(false);

            ofPopMatrix();
        ofPopStyle();


    }

    void Neurona::drawEvent(){

        ofFill();
        ofSetColor(vis_color);

        event_pos += event_vel;

        if(event_pos>visEvent_width){
            event_pos = 0;
            event_vector.clear();
            //cout << "clearMaxvis_pos" << "\n";
        }

        if(event){

         //   cout << xvis_pos + vis_pos.x << "\n";

            event_vector.push_back (event_pos + visEvent_pos.x);
           // cout << "hola" <<"\n";
            //cout << "size, " << event_vector.size() << "\n";

        }


        for(unsigned i=0; i< event_vector.size(); i++){
            ofRect(event_vector[i], visEvent_pos.y, event_vis_width , event_vis_height);
        }


        //ofCircle(vis_pos.x, vis_pos.y, 10);
    }



