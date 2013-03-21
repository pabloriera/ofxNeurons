#include "testApp.h"

void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(100);

    sender.setup(HOST, PORT);

   // int mm = 20;
    int wh = ofGetWindowHeight()*.4;

    for(int i = 0; i < TOTAL; i++)
    {
//            p.push_back(new Neurona);
        //nn[i].pos.set(100,100+30*i);
        //nn[i].pos.set( ofRandom(0,1)*ofGetWindowWidth() , ofRandom(0,1)*ofGetWindowHeight() );
        //nn[i].pos.set( (i / mm)*25+100, (i % mm)*25+100  );

        //nn[i].pos.set( (i / mm)*30+10, (i % mm)*30+100  );



        nn[i].visEvent_height=wh/TOTAL;
        nn[i].visEvent_width=ofGetWindowWidth()*.5;
        nn[i].visEvent_pos.set( 100, 10+i*wh/TOTAL*1.01);

        nn[i].vis_circle_radio0 =wh/TOTAL*0.5;
        nn[i].visCircle_pos.set( 50, 10+i*wh/TOTAL*1.01+wh/TOTAL*0.5);

        nn[i].visVoltaje_height=wh/TOTAL*.5;
        nn[i].visVoltaje_width=ofGetWindowWidth()*.45;
        nn[i].visVoltaje_pos.set( 400, 10+i*wh/TOTAL*.5*1.01);

        nn[i].visFR_height=wh/TOTAL*.5;
        nn[i].visFR_width=ofGetWindowWidth()*.45;
        nn[i].visFR_pos.set(400, 200+i*wh/TOTAL*.5*1.01);

        nn[i].instance = i;

        nn[i].reset();

        cout <<"a" << "\n";


//        for(int j = 0; j < TOTAL; j++)
//        {
//            ss[i][j].weigth = ofRandom(-1,1)/10;
//        }

    }

    DT = 1.0/44100.0;
    //DT = 0;
}


void testApp::update(){

    float tim = timer.getElapsedSeconds();
//    float tim = timer.getSecondsSinceLastCall();

    if(tim>DT)
    {
        //cout << tim << "\n";
        for(int i = 0; i < TOTAL; i++)
            if(nn[i].update())
                    nn[i].OSCevent(&sender);



        for(int i = 0; i < TOTAL; i++)
            for(int j = 0; j < TOTAL; j++)
                {
                    if (i!=j)
                        nn[i].currentBuffer(ss[i][j].weigth*nn[j].sp);
                }
                //ss[i][j].update(i,j);

//        cout << nn[0].sp<<"\n";

        timer.setStartTime();


    }

}


void testApp::draw(){
    ofBackground(0);

    for(int i = 0; i < TOTAL; i++){
        nn[i].drawEvent();
        nn[i].drawVoltage();
        nn[i].drawFR();
        nn[i].drawCircle();

    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if(key=='r')
        for(int i = 0; i < TOTAL; i++)
            nn[i].reset();


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

//
        float auxX = (float)x*1/ofGetWindowWidth();
        //float auxY = (float)y*1/ofGetWindowHeight();

        //cout << aux << "\n";

        for(int i = 0; i < TOTAL; i++){
            nn[i].dc = auxX + ofSignedNoise(nn[i].visEvent_pos.x * 0.8f, nn[i].visEvent_pos.y *0.8f);
            //nn[i].FRset(auxY*0.1,0.5);
        }
        //nn[0].dc = auxX*10;

//        nn[0].tau = auxY;

//            nn[i].I = aux;

 //cout << ss[0][0].weigth << ",  " <<nn[0].I   << "\n";
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
        float auxX = (float)x*10/ofGetWindowWidth();
        float auxY = (float)y*10/ofGetWindowHeight();
        cout << auxX << " " << auxY << "\n";

        cout << "V = ";
        for(int i = 0; i < TOTAL; i++)
            cout << nn[i].V << ",";

        cout << "\n";

        cout << "I = ";
        for(int i = 0; i < TOTAL; i++)
            cout << nn[i].I << ",";

        cout << "\n";

        cout << "FR = ";
        for(int i = 0; i < TOTAL; i++)
            cout << nn[i].fr.v[2]<< ",";

        cout << "\n";


//        for(int i = 0; i < TOTAL; i++){
//
//            nn[i].reset();
//                nn[i].random_dc(0,auxY);
//
//            for(int j = 0; j < TOTAL; j++)
//                ss[i][j].random_weigth(-auxX,auxX*.1);
//        }


}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
