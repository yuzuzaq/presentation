#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0,0,123);
    ofToggleFullscreen();
    ofEnableAlphaBlending();
    light.setPointLight();
    light.setup();
    ofSetBackgroundAuto(false);
    // 垂直同期
    ofSetVerticalSync(true);
    
    soundPlayer.load ("secert.mp3");
    soundPlayer.setLoop(true);
    soundPlayer.setVolume(1.0);
    soundPlayer.play();

//    soundStream.setup(this,0,1,44100,256,4);
    
    
    r = 15;
    for (int i=0; i<NUM; i++){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        msy[i].setPosition(ofRandom(-500,2000),ofRandom(-500,2000),ofRandom(-500,2000));
        msp[i].setPosition(ofRandom(-500,500),ofRandom(-500,500),ofRandom(-500,500));
        msg[i].setPosition(ofRandom(-500,500),ofRandom(-500,500),ofRandom(-500,500));
        msy[i].set(2*r, 50);
        msp[i].set(r, 50);
        msg[i].set(r/2, 50);
    }
    
    light.enable();
    light.setPosition(-100, 100, 100);
    //環境反射光
    light.setAmbientColor(ofFloatColor(0.3,0.3,0.3,10));
    //拡散反射光
    light.setDiffuseColor(ofFloatColor(2.0,0.2,1.0));
    //鏡面反射光
    light.setSpecularColor(ofFloatColor(1.0,1.0,1.0));

    ofSetFrameRate(30);  //フレームレートは60fps
    ofBackground(0);  //背景は黒
    ofEnableDepthTest();  //深度テストを有効に
    cam.setDistance(120);  //カメラの位置と注目点の距離を120に設定
    this->circle.set(ofRandom(400,400),ofRandom(-500,500));
    this->circle2.set(180,180);//立方体の大きさ(100,100,100)
    this->circle.setResolution(10);
    this->circle2.setResolution(2);  //数値が大きいほど立方体を構成するメッシュの量が増える
    mesh = this->circle.getMesh();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    mesh2 = this->circle2.getMesh();
    //boxの頂点情報群を取得しmeshに格納


    
    glPointSize(3);
    wave = ofSpherePrimitive(10,10).getMesh();
    wave2 = ofSpherePrimitive(60,60).getMesh();
    
    for(int i = 0; i < mesh.getVertices().size(); i++){  //各々の頂点に対して
        mesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));  //色情報初期化
        ofVec3f loc = mesh.getVertices()[i] * ofRandom(0.5,1.0);  //位置情報を0.5~1.0で掛ける
        mesh.setVertex(i, loc);  //新しい位置情報としてセット
        ofColor c;
        c.setHsb(ofRandom(255),255,255);  //HSBで色定義
        mesh.setColor(i,c);  //新しい色情報としてセット
    }

    
    // 垂直同期
    ofSetVerticalSync(false);
    
    for(int i=0; i<500;i++){
        // sphereの位置をランダムにする（X, Y, Z）
        spheres[i].setPosition(ofRandom(-100,500), ofRandom(-500,500), ofRandom(-500,500));
        // sphereのサイズ
        spheres[i].setRadius(21);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    cub = cub*2000;
    volume = ofSoundGetSpectrum(1);
    wave2 = ofSpherePrimitive(volume[0]*1000,80).getMesh();
    for (int i=0; i<wave.getVertices().size(); i++){
        ofVec3f point = wave.getVertices()[i] / 400.0;
        float z = ofNoise(point.x,point.y,ofGetElapsedTimef() * 200,0);
        float z2 = ofNoise(point.x,point.y,ofGetElapsedTimef() * 20,0);
        wave.setVertex(i, ofVec3f(wave.getVertices()[i].x, wave.getVertices()[i].y, z*10));
        //wave2.setVertex(i, ofVec3f(wave.getVertices()[i].x, wave.getVertices()[i].y, z*10));
        }
    //wave2.getVertices()[i].x, wave2.getVertices()[i].y, z2*1000
}

//--------------------------------------------------------------
void ofApp::draw(){//カメラ起動
    //wave.setMode(OF_PRIMITIVE_POINTS);
    //ofDrawCircle(-200, 100, 100);
    //ofPopMatrix();
    

    for (int i=0; i<NUM;i++){
        cam.begin();
        ofSetColor(9);
        ofRotateX(ofGetElapsedTimef()/2);
        ofRotateZ(ofGetElapsedTimef()/1);
        ofSetColor(255, 255, 255,90);
        //        msp[i].draw();
        
        //        ofSetColor(51,255,204,90);
        //        msg[i].draw();
        
               ofSetColor(ofRandom(225),ofRandom(225),ofRandom(225),ofRandom(225));
                msy[i].draw();
    }

    ofSetColor(108,173,119);
    wave2.setMode(OF_PRIMITIVE_LINES_ADJACENCY);
   // wave2.draw();
    ofSetLineWidth(20);
    ofRotateY(ofGetElapsedTimef()/10);
    ofRotateZ(ofGetElapsedTimef()/30);
    mesh.drawWireframe();
    
    ofSetColor(255,255,255);
    ofSetLineWidth(3);

    //mesh2.drawWireframe();

    //ここから　軌
    
    //描画の基準を真ん中に移動する
    //ofPushMatrix();
    //ofTranslate(ofGetWidth()/2+450, ofGetHeight()/2+250);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
  //キャンバスの座標を回転させる

    ofRotateYDeg(ofGetFrameNum()/20);
    ofRotateZDeg(ofGetFrameNum()/1);
    
     //HSBカラーで設定（色相、彩度、明度）
    ofSetColor(ofColor::fromHsb(ofGetFrameNum()%255,225,225));
    //「//ofGetFrameNum()%255」で、時間の経過とともに色を変化させているよ！
     //sphereを描く
//    for(int i=0; i<300; i++){
//        spheres[i].draw();
//    }

    cam.end();


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
