#include "ofApp.h"

int spacing = 45;
int totallines = 0;
int textX = 125;
int textY = 50;
int fontSize = 120;
string str;
string msg;

ofColor *colors;


//--------------------------------------------------------------
void ofApp::setup(){

    colors = new ofColor[60];

    colors[1].r = ofRandom(180);
    colors[1].g = ofRandom(180);
    colors[1].b = ofRandom(180);

    ofSetVerticalSync(true);
    bSendSerialMessage = false;
    ofBackground(255, 250, 245);

    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup("/dev/ttyACM0", baud);

    fabric.load("images/fabric.jpg");
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){

    str.clear();
    myfont.load("home sweet home outline.ttf", fontSize);

    while (serial.available()) {

        int c = serial.readByte();
            str.push_back(c);

        if (c=='\n')
	{
            break;
        }
    }


    if (str[0]=='[' && str.back()=='\n')
        {
            draw();
        }
        else
        {
	    ofSleepMillis(100);
            update();
        }

    }

//--------------------------------------------------------------
void ofApp::draw(){

    fabric.draw(0,0,ofGetWidth(),ofGetWidth());

    vector<string> splitmessage = ofSplitString(str," ");

    totallines = 0;


    //cout<<str<<endl;
    //cout<<splitmessage.size()<<endl;

    if (splitmessage.size() > 36) {
        fontSize = 40;
    }

    else if (splitmessage.size() > 21) {
        fontSize = 59;
    }

    else if (splitmessage.size() > 11) {
        fontSize = (splitmessage.size()+155)/2.2;
    }

    else if (splitmessage.size() > 7) {
        fontSize = (splitmessage.size()+160)/1.6;
    }
    else if (splitmessage.size() > 5){
        fontSize = (splitmessage.size()+160)/1.4;
    }
    else if (splitmessage.size() > 3){
        fontSize = (splitmessage.size()+130)/1.3;
    }else{
         fontSize = (splitmessage.size()+120);
    }

    myfont.load("home sweet home outline.ttf", fontSize);

        for (unsigned  int i=2;i<splitmessage.size();i++){
            ofPushStyle();
            if (str != msg){
                colors[i].r = ofRandom(180);
                colors[i].g = ofRandom(180);
                colors[i].b = ofRandom(180);
            }else{
                ofSetColor(colors[i].r,colors[i].g,colors[i].b);
            }


            if (textX+(myfont.stringWidth(splitmessage[i]))>(ofGetWidth()-95)){
                    textY+=(myfont.stringHeight(splitmessage[i])*1.2);
                    textX= 145;
                    totallines++;
            }
             myfont.drawString(splitmessage[i],textX,textY);
             textX+=(myfont.stringWidth(splitmessage[i])+spacing);

            ofPopStyle();
        }


    textY =  ((ofGetWindowHeight()/2) - totallines*40);
    textX =  135;

    ofPushStyle();

    ofSetColor(colors[1].r,colors[1].g,colors[1].b);

    fontSize = 120;
    myfont.load("home sweet home outline.ttf", fontSize);

    myfont.drawString("*",20,120);
    myfont.drawString("*",ofGetWindowWidth()-150,120);
    myfont.drawString("*",20,ofGetWindowHeight()-20);
    myfont.drawString("*",ofGetWindowWidth()-150,ofGetWindowHeight()-20);

    for (int i=210;i<ofGetWindowWidth()-240;i+=85){
    myfont.drawString("-",i,100);
    }
    for (int i=210;i<ofGetWindowWidth()-240;i+=85){
        myfont.drawString("-",i,ofGetWindowHeight()-25);
    }
    for (int i=260;i<ofGetWindowHeight()-120;i+=120){
        myfont.drawString("|",60,i);
    }
    for (int i=260;i<ofGetWindowHeight()-120;i+=120){
        myfont.drawString("|",ofGetWindowWidth()-95,i);
    }
    ofPopStyle();
    msg = str;

   
 }




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
