#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->font_size = 100;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<char> charactors = { 'N', 'O', 'I', 'S', 'E' };
	int sample_count = 180;
	for (int charactor_index = 0; charactor_index < charactors.size(); charactor_index++) {

		ofPath path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		ofPoint location = ofPoint(charactor_index * 144 + 72, ofGetHeight() * 0.5);
		ofPushMatrix();
		ofTranslate(location);

		ofNoFill();
		this->font.drawStringAsShapes(string{ charactors[charactor_index] }, this->font_size * -0.5, this->font_size * 0.5);

		ofFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < (int)outline.size(); outline_index++) {

			if (outline_index != 0) {

				ofNextContour(true);
			}

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < (int)vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x - this->font_size * 0.5, vertices[vertices_index].y + this->font_size * 0.5, vertices[vertices_index].z);
				int noise_value = ofMap(ofNoise((location.x + point.x) * -0.01 - ofGetFrameNum() * 0.03), 0, 1, -100, 100);
				noise_value /= 10;
				noise_value *= 10;
				if (noise_value > -20 && noise_value < 20) {

					noise_value = 0;
				}

				ofVertex(point + ofPoint(noise_value, noise_value));
			}
		}
		ofEndShape();
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}