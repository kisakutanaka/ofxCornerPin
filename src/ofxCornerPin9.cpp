//
//  ofxCornerPin.cpp
//  example
//
//  Created by 田中喜作 on 2018/10/01.
//

#include "ofxCornerPin9.h"

void ofxCornerPin9::setup(int w,int h,int _u,int _v){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            vertices[j*3+i]={w/2.f*i,h/2.f*j};
        }
    }

    u=_u;
    v=_v;
    setMesh();
}

void ofxCornerPin9::setMesh(){
    mesh.clear();
    points.clear();
    
    for(int i1=0;i1<2;i1++){
        for(int j1=0;j1<2;j1++){
            float a,b,c,d;
            float w=ofGetWidth();
            float h=ofGetHeight();
            float vl,vr,vt,vb;
            ofPoint ip;
            ofPoint cp;
            ofPoint mp;
            ofPoint lt,rt,rb,lb;
            lt=vertices[j1*3+i1];
            rt=vertices[j1*3+(i1+1)];
            rb=vertices[(j1+1)*3+(i1+1)];
            lb=vertices[(j1+1)*3+i1];
            
            ofLineSegmentIntersection(lt,rb,rt,lb,cp);
            
            if(lt.x==lb.x){
                if(rt.x==rb.x){
                    vt=vb=(cp.x-lt.x)/(rb.x-lt.x);
                }
                else{
                    c=(rb.y-rt.y)/(rb.x-rt.x);
                    d=-c*rt.x+rt.y;
                    ip={lt.x,c*lt.x+d};
                    ofLineSegmentIntersection(ip, ip+(cp-ip)*h, lt, rt, mp);
                    vt=(mp.x-lt.x)/(rt.x-lt.x);
                    ofLineSegmentIntersection(ip, ip+(cp-ip)*h, lb, rb, mp);
                    vb=(mp.x-lb.x)/(rb.x-lb.x);
                }
            }
            else if(rt.x==rb.x){
                a=(lb.y-lt.y)/(lb.x-lt.x);
                b=-a*lt.x+lt.y;
                ip={rt.x,a*rt.x+b};
                ofLineSegmentIntersection(ip, ip+(cp-ip)*h, lt, rt, mp);
                vt=(mp.x-lt.x)/(rt.x-lt.x);
                ofLineSegmentIntersection(ip, ip+(cp-ip)*h, lb, rb, mp);
                vb=(mp.x-lb.x)/(rb.x-lb.x);
            }
            else{
                a=(lb.y-lt.y)/(lb.x-lt.x);
                b=-a*lt.x+lt.y;
                c=(rb.y-rt.y)/(rb.x-rt.x);
                d=-c*rt.x+rt.y;
                if(a!=c){
                    ip={-(b-d)/(a-c),-(b-d)/(a-c)*a+b};
                    ofLineSegmentIntersection(ip, ip+(cp-ip)*h, lt, rt, mp);
                    vt=(mp.x-lt.x)/(rt.x-lt.x);
                    ofLineSegmentIntersection(ip, ip+(cp-ip)*h, lb, rb, mp);
                    vb=(mp.x-lb.x)/(rb.x-lb.x);
                }
                else{
                    vt=vb=(cp.x-lt.x)/(rb.x-lt.x);
                }
            }
            
            a=(rt.y-lt.y)/(rt.x-lt.x);
            b=-a*lt.x+lt.y;
            c=(rb.y-lb.y)/(rb.x-lb.x);
            d=-c*lb.x+lb.y;
            
            if(a!=c){
                ip={-(b-d)/(a-c),-(b-d)/(a-c)*a+b};
                ofLineSegmentIntersection(ip, ip+(cp-ip)*w, lt, lb, mp);
                vl=(mp.y-lt.y)/(lb.y-lt.y);
                ofLineSegmentIntersection(ip, ip+(cp-ip)*w, rt, rb, mp);
                vr=(mp.y-rt.y)/(rb.y-rt.y);
            }
            else{
                vr=vl=(cp.y-lt.y)/(rb.y-lt.y);
            }
            
            vector<float>xts=vector<float>(11);
            vector<float>xbs=vector<float>(11);
            vector<float>yls=vector<float>(11);
            vector<float>yrs=vector<float>(11);
            
            for(int i=0;i<11;i++){
                float x=i/10.f;
                float xt,xb;
                if(vt>0.5001||vt<0.4999){
                    float bx=(1-vt)/(1-2*vt);
                    float cx=-(vt)/(1-2*vt);
                    float ax=bx*cx;
                    xt=ax/(x-bx)+cx;
                }
                else{
                    xt=x;
                }
                if(vb>0.5001||vb<0.4999){
                    float bx=(1-vb)/(1-2*vb);
                    float cx=-(vb)/(1-2*vb);
                    float ax=bx*cx;
                    xb=ax/(x-bx)+cx;
                }
                else{
                    xb=x;
                }
                xts[i]=xt;
                xbs[i]=xb;
                float y=i/10.f;
                float yl,yr;
                if(vl>0.5001||vl<0.4999){
                    float by=(1-vl)/(1-2*vl);
                    float cy=-(vl)/(1-2*vl);
                    float ay=by*cy;
                    yl=ay/(y-by)+cy;
                }
                else{
                    yl=y;
                }
                if(vr>0.5001||vr<0.4999){
                    float by=(1-vr)/(1-2*vr);
                    float cy=-(vr)/(1-2*vr);
                    float ay=by*cy;
                    yr=ay/(y-by)+cy;
                }
                else{
                    yr=y;
                }
                yls[i]=yl;
                yrs[i]=yr;
            }
            
            ofPoint l1s,l1e,l2s,l2e,p;
            for(int j=0;j<10+j1;j++){
                for(int i=0;i<10+i1;i++){
                    if(i==0){
                        p=(lb-lt)*yls[j]+lt;
                        mesh.addVertex(p);
                        mesh.addTexCoord(ofVec2f(u/2*i1+u/2/10.f*i,v/2*j1+v/2/10.f*j));
                    }
                    else if(i==10){
//                        if(i1==1){
                            p=(rb-rt)*yrs[j]+rt;
                            mesh.addVertex(p);
                            mesh.addTexCoord(ofVec2f(u/2*i1+u/2/10.f*i,v/2*j1+v/2/10.f*j));
//                        }
                    }
                    else if(j==0){
                        p=(rt-lt)*xts[i]+lt;
                        mesh.addVertex(p);
                        mesh.addTexCoord(ofVec2f(u/2*i1+u/2/10.f*i,v/2*j1+v/2/10.f*j));
                    }
                    else if(j==10){
//                        if(j1==1){
                            p=(rb-lb)*xbs[i]+lb;
                            mesh.addVertex(p);
                            mesh.addTexCoord(ofVec2f(u/2*i1+u/2/10.f*i,v/2*j1+v/2/10.f*j));
//                        }
                    }
                    else{
                        l1s=(lb-lt)*yls[j]+lt;
                        l1e=(rb-rt)*yrs[j]+rt;
                        l2s=(rt-lt)*xts[i]+lt;
                        l2e=(rb-lb)*xbs[i]+lb;
                        ofLineSegmentIntersection(l1s, l1e, l2s, l2e, p);
                        mesh.addVertex(p);
                        mesh.addTexCoord(ofVec2f(u/2*i1+u/2/10.f*i,v/2*j1+v/2/10.f*j));
                    }
                }
            }

        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<20;j++){
            mesh.addIndex(j*10+i);
            mesh.addIndex(j*10+i+1);
            mesh.addIndex((j+1)*10+i);
            mesh.addIndex(j*10+i+1);
            mesh.addIndex((j+1)*10+i);
            mesh.addIndex((j+1)*10+i+1);
        }
    }
    for(int i=0;i<20;i++){
        mesh.addIndex(9+i*10);
        mesh.addIndex(210+i*11);
        mesh.addIndex(9+(i+1)*10);
        mesh.addIndex(210+i*11);
        mesh.addIndex(9+(i+1)*10);
        mesh.addIndex(210+(i+1)*11);
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            mesh.addIndex(210+j*11+i);
            mesh.addIndex(210+j*11+i+1);
            mesh.addIndex(210+(j+1)*11+i);
            mesh.addIndex(210+j*11+i+1);
            mesh.addIndex(210+(j+1)*11+i);
            mesh.addIndex(210+(j+1)*11+i+1);
        }
    }
    
    ofLog()<<mesh.getVertices().size();
}

void ofxCornerPin9::setCorners(vector<ofPoint> _corners){
    if(_corners.size()!=9){
        ofLogError()<<"inappropriate";
    }
    else{
        vertices=_corners;
        this->setMesh();
    }
}

void ofxCornerPin9::setV1(float _v1){
    v1=_v1;
    setMesh();
}

void ofxCornerPin9::setV2(float _v2){
    v2=_v2;
    setMesh();
}

vector<ofPoint> ofxCornerPin9::getCorners(){
    return vertices;
}

void ofxCornerPin9::draw(){
    mesh.draw();
}

void ofxCornerPin9::drawGuide(){
    ofPushStyle();
    mesh.drawWireframe();
    for(int i=0;i<mesh.getVertices().size();i++){
        ofDrawBitmapString(i, mesh.getVertices()[i]);
    }
    ofSetColor(0,0,255);
    ofDrawCircle(center, 5);
    ofPopStyle();
}
