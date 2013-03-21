 #include "sinapsis.h"

    Sinapsis::Sinapsis(){
        weigth = 0;
        delay = 0;
    }

    void Sinapsis::update(float i, float j){

//        nn[i].corrBuf(nn[j].sp);

    }


    void Sinapsis::random_weigth(float _min,float _max){

        weigth = ofRandom(_min,_max);

    }
