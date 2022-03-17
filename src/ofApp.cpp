#include "ofApp.h"
#include "mandelbulbUtils.h"

void ofApp::setup() {
  ofSetFrameRate(60);
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWindowWidth() / 2,
                      ofGetScreenHeight() / 2 - ofGetWindowHeight() / 2);
  easyCam.setPosition(0, 0, 220);  // initial cam position
  auto n = constants::exponential;

  for (int i = 0; i < constants::dimension; ++i) {
    for (int j = 0; j < constants::dimension; ++j) {
      bool isEdge{false};
      for (int k = 0; k < constants::dimension; ++k) {
        auto cx = ofMap(i, 0, constants::dimension, -1, 1);
        auto cy = ofMap(j, 0, constants::dimension, -1, 1);
        auto cz = ofMap(k, 0, constants::dimension, -1, 1);

        glm::vec3 cTriplex{cx, cy, cz};

        glm::vec3 zTriplex{0, 0, 0};

        int iteration{0};

        while (true) {
          auto spherical = mandelbulbUtils::spherical(zTriplex.x, zTriplex.y, zTriplex.z);

          auto newX = pow(spherical.r, n) * sin(spherical.theta * n) * cos(spherical.phi * n);
          auto newY = pow(spherical.r, n) * sin(spherical.theta * n) * sin(spherical.phi * n);
          auto newZ = pow(spherical.r, n) * cos(spherical.theta * n);

          glm::vec3 zTriplexPowerN = {newX, newY, newZ};

          zTriplex = zTriplexPowerN + cTriplex;

          ++iteration;

          if (spherical.r > 2) {
            if (isEdge)
              isEdge = false;
            break;
          } else if (iteration > constants::maxIteration) {
            if (!isEdge) {
              isEdge = true;
              mandelbulb.push_back(cTriplex);
            }
            break;
          }
        }
      }
    }
  }
  cout << "No. of points: " << mandelbulb.size() << '\n';
}

void ofApp::update() {}

void ofApp::draw() {
  easyCam.begin();
  for (auto &vec : mandelbulb) {
    glm::vec3 point{vec.x, vec.y, vec.z};
    point *= constants::vectorScale;
    ofDrawSphere(point, constants::pointRadius);
  }
  easyCam.end();
}

void ofApp::keyPressed(int key) {}

void ofApp::keyReleased(int key) {}

// void ofApp::mouseMoved(int x, int y) {}

// void ofApp::mouseDragged(int x, int y, int button) {}

// void ofApp::mousePressed(int x, int y, int button) {}

// void ofApp::mouseReleased(int x, int y, int button) {}

// void ofApp::mouseEntered(int x, int y) {}

// void ofApp::mouseExited(int x, int y) {}

// void ofApp::windowResized(int w, int h) {}

// void ofApp::gotMessage(ofMessage msg) {}

// void ofApp::dragEvent(ofDragInfo dragInfo) {}
