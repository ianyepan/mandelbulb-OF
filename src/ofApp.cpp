#include "ofApp.h"
#include "mandelbulbUtils.h"

void ofApp::setup() {
  ofSetFrameRate(60);
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWindowWidth() / 2,
                      ofGetScreenHeight() / 2 - ofGetWindowHeight() / 2);
  easyCam.setPosition(30, 0, 220);  // initial cam position
  auto n = constants::exponential;

  for (int i = 0; i < constants::dimension; ++i) {
    for (int j = 0; j < constants::dimension; ++j) {
      bool isEdge{false};
      for (int k = 0; k < constants::dimension; ++k) {
        auto x = ofMap(i, 0, constants::dimension, -1, 1);
        auto y = ofMap(j, 0, constants::dimension, -1, 1);
        auto z = ofMap(k, 0, constants::dimension, -1, 1);

        glm::vec3 zeta{0, 0, 0};

        int iteration{0};

        while (true) {
          auto spherical = mandelbulbUtils::spherical(zeta.x, zeta.y, zeta.z);

          auto newX = pow(spherical.r, n) * sin(spherical.theta * n) * cos(spherical.phi * n);
          auto newY = pow(spherical.r, n) * sin(spherical.theta * n) * sin(spherical.phi * n);
          auto newZ = pow(spherical.r, n) * cos(spherical.theta * n);

          zeta = glm::vec3{newX + x, newY + y, newZ + z};

          ++iteration;

          if (spherical.r > 2) {
            if (isEdge)
              isEdge = false;
            break;
          } else if (iteration > constants::maxIteration) {
            if (!isEdge) {
              isEdge = true;
              mandelbulb.emplace_back(x, y, z);
            }
            break;
          }
        }
      }
    }
  }
  cout << "No. of points: " << mandelbulb.size() << '\n';
}

void ofApp::update() {
  // for (auto &vec : mandelbulb) {
  //   vec.x -= 0.005;
  //   vec.y += 0.005;
  //   vec.z += 0.05;
  // }
}

void ofApp::draw() {
  easyCam.begin();
  // ofTranslate(300,300);
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  // ofRotateXRad(constants::pi / 4);
  // ofRotateYRad(-constants::pi / 3);
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
