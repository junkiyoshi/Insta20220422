#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	ofColor color;
	for (int i = 0; i < 5; i++) {

		this->radius_list.push_back(100);
		this->speed_list.push_back(ofRandom(0.5, 1.5));
		this->deg_list.push_back(ofRandom(360));
		this->deg_speed_list.push_back(ofRandom(1, 2));
		color.setHsb(ofRandom(255), 130, 255);
		this->color_list.push_back(color);
	}

	for (int i = this->radius_list.size() - 1; i >= 0; i--) {

		this->radius_list[i] += this->speed_list[i];
		this->deg_list[i] += this->deg_speed_list[i];

		this->mesh.addVertex(glm::vec3(this->radius_list[i] * cos(this->deg_list[i] * DEG_TO_RAD), this->radius_list[i] * sin(this->deg_list[i] * DEG_TO_RAD), 0));
		this->mesh.addColor(this->color_list[i]);

		if (this->radius_list[i] > 450) {

			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->deg_list.erase(this->deg_list.begin() + i);
			this->deg_speed_list.erase(this->deg_speed_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			auto distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < 13) {

				this->mesh.addIndex(i); this->mesh.addIndex(k);
			}

			auto alpha = distance < 10 ? 255 : ofMap(distance, 10, 13, 255, 0);
			if (this->mesh.getColor(i).a < alpha) {

				this->mesh.setColor(i, ofColor(this->mesh.getColor(i), alpha));
			}

			if (this->mesh.getColor(k).a < alpha) {

				this->mesh.setColor(k, ofColor(this->mesh.getColor(k), alpha));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(0);
	ofDrawSphere(glm::vec3(), 100);

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {
		
		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 1);
	}

	this->mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
