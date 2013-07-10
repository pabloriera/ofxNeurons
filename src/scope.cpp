#include "scope.h"

    scope::scope(){

    }

    void scope::setup(){

        height = ofGetHeight();
        width = ofGetWidth();

        buff_downsample_c = 0;
        buff_downsample_val = 0;

       //Visualizations
        bufferSize = 1024;
        buff.assign(bufferSize, 0.0);

    }

    void scope::reset(){

        buff.assign(bufferSize, 0.0);

    }

    void scope::update(float value){

        buff_downsample_c++;
        if(buff_downsample_c > buff_downsample_val)
        {
            buff.push_back(value);
            if( buff.size() >= (size_t) bufferSize )
                buff.erase(buff.begin(), buff.begin()+1);

            buff_downsample_c=0;
        }

    }

    void scope::draw(){

        //ofSetColor(vis_color, 255*ofNormalize(V,-65,30));
        int auxS = buff.size();

        ofSetColor(*color);

        ofNoFill();

        // draw the left channel:
        ofPushStyle();
            ofPushMatrix();
            ofTranslate(pos.x, pos.y, 0);

            ofSetLineWidth(1);

                ofBeginShape();

                for (int i = 0; i < auxS; i++){

                    ofVertex(((float) i/(float)auxS) * width,( 1 - buff[i] ) * height );
                }
                ofEndShape(false);

            ofPopMatrix();
        ofPopStyle();


    }
