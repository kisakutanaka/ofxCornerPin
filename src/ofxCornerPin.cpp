//
//  ofxCornerPin.cpp
//  example
//
//  Created by 田中喜作 on 2018/10/01.
//

#include "ofxCornerPin.h"

void ofxCornerPin::setup(int w,int h,int _u,int _v){
    lt={0,0};
    rt={(float)w,0};
    rb={(float)w,(float)h};
    lb={0,(float)h};
    u=_u;
    v=_v;
    setMesh();
}

void ofxCornerPin::setMesh(){
    mesh.clear();
    
    float a,b,c,d;
    float w=ofGetWidth();
    float h=ofGetHeight();
    float vl,vr,vt,vb;
    ofPoint ip;
    ofPoint cp;
    ofPoint mp;
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
    
    vector<float>xts=vector<float>(21);
    vector<float>xbs=vector<float>(21);
    vector<float>yls=vector<float>(21);
    vector<float>yrs=vector<float>(21);

    for(int i=0;i<21;i++){
        float x=i/20.f;
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
        float y=i/20.f;
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
    for(int i=0;i<21;i++){
        for(int j=0;j<21;j++){
            if(i==0){
                p=(lb-lt)*yls[j]+lt;
            }
            else if(i==20){
                p=(rb-rt)*yrs[j]+rt;
            }
            else if(j==0){
                p=(rt-lt)*xts[i]+lt;
            }
            else if(j==20){
                p=(rb-lb)*xbs[i]+lb;
            }
            else{
                l1s=(lb-lt)*yls[j]+lt;
                l1e=(rb-rt)*yrs[j]+rt;
                l2s=(rt-lt)*xts[i]+lt;
                l2e=(rb-lb)*xbs[i]+lb;
                ofLineSegmentIntersection(l1s, l1e, l2s, l2e, p);
            }
            mesh.addVertex(p);
            mesh.addTexCoord(ofVec2f(u*i/20.f,v*j/20.f));
        }
        center=mesh.getVertices()[21*10+10];
    }
    
    for(int i=1;i<21;i++){
        for(int j=1;j<21;j++){
            mesh.addIndex((j-1)*21+i-1);
            mesh.addIndex((j-1)*21+i);
            mesh.addIndex(j*21+i-1);
            mesh.addIndex((j-1)*21+i);
            mesh.addIndex(j*21+i-1);
            mesh.addIndex(j*21+i);
        }
    }
}

void ofxCornerPin::setLeftTop(ofPoint _lt){
    lt=_lt;
    setMesh();
}

void ofxCornerPin::setRightTop(ofPoint _rt){
    rt=_rt;
    setMesh();
}

void ofxCornerPin::setRightBottom(ofPoint _rb){
    rb=_rb;
    setMesh();
}

void ofxCornerPin::setLeftBottom(ofPoint _lb){
    lb=_lb;
    setMesh();
}

void ofxCornerPin::setCorners(vector<ofPoint> _corners){
    if(_corners.size()!=4){
        ofLogError()<<"inappropriate";
    }
    else{
        lt=_corners[0];
        rt=_corners[1];
        rb=_corners[2];
        lb=_corners[3];
        this->setMesh();
    }
}

void ofxCornerPin::setV1(float _v1){
    v1=_v1;
    setMesh();
}

void ofxCornerPin::setV2(float _v2){
    v2=_v2;
    setMesh();
}

vector<ofPoint> ofxCornerPin::getCorners(){
    vector<ofPoint> p=vector<ofPoint>(4);
    p[0]=lt;
    p[1]=rt;
    p[2]=rb;
    p[3]=lb;
    return p;
}

void ofxCornerPin::draw(){
    mesh.draw();
}

void ofxCornerPin::drawGuide(){
    ofPushStyle();
    mesh.drawWireframe();
    ofSetColor(0,0,255);
    ofDrawCircle(center, 5);
    ofSetColor(255,0,0);
    ofDrawLine(lt, rb);
    ofDrawLine(rt, lb);
    ofPopStyle();
}
