#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include <linkbot/linkbot.hpp>


namespace barobo {

void _buttonCallbackHelper(LinkbotButton button, LinkbotButtonState state, int timestamp, void* user_data)
{
    auto linkbot = static_cast<Linkbot *>(user_data);
    if(linkbot->buttonEventCallback != nullptr) {
        linkbot->buttonEventCallback(button, state, timestamp);
    }
}

int _connect_n = 0;

std::string daemonHostName () {
    return "127.0.0.1";
}

uint16_t daemonPortNo () {
    return 42000;
}

Linkbot::Linkbot (const std::string& serialId) {
    m = rs::linkbotFromSerialId(serialId.c_str());
}

Linkbot::Linkbot() {
    // Get the serial id from the environment
    auto env_str = std::getenv("ROBOTMANAGER_IDS");
    if(!env_str) {
        throw Error("Environment variable ROBOTMANAGER_IDS not set.");
    }
    std::string env{env_str};
    std::istringstream ss{env};
    std::string token;
    _connect_n++;
    for(int i = 0; i < _connect_n; i++) {
        std::getline(ss, token, ',');
    }
    if ( token.length() != 4 ) {
        throw Error("Insufficient number of robots connected in robot manager.");
    }
    m = rs::linkbotFromSerialId(token.c_str());
}

Linkbot::~Linkbot() {
    rs::linkbotDelete(m);
}

/* GETTERS */
// Member functions take angles in degrees.
// All functions are non-blocking. Use moveWait() to wait for non-blocking
// movement functions.
void Linkbot::getAccelerometer (double& x, double& y, double& z){
    rs::linkbotGetAccelerometer(m, &x, &y, &z);
}

std::vector<int> Linkbot::getAdcRaw(){
    /*FIXME*/ throw std::exception();
}

void Linkbot::getBatteryVoltage(double& voltage){
    /*FIXME*/ throw std::exception();
}

void Linkbot::getFormFactor(LinkbotFormFactor& form){
    rs::linkbotGetFormFactor(m, &form);
}

void Linkbot::getJointAngles (int& timestamp, double& a1, double& a2, double& a3){
    rs::linkbotGetJointAngles(m, &timestamp, &a1, &a2, &a3);
}

void Linkbot::getJointSpeeds(double& s1, double& s2, double& s3){
    rs::linkbotGetJointSpeeds(m, &s1, &s2, &s3);
}

void Linkbot::getJointStates(int& timestamp,
                    LinkbotJointState& s1,
                    LinkbotJointState& s2,
                    LinkbotJointState& s3){
    /*FIXME*/ throw std::exception();
}

void Linkbot::getLedColor (int& r, int& g, int& b){
    rs::linkbotGetLedColor(m, &r, &g, &b);
}

void Linkbot::getVersionString (std::string& v){
    /*FIXME*/ throw std::exception();
}

void Linkbot::getSerialId(std::string& serialId){
    /*FIXME*/ throw std::exception();
}

void Linkbot::getJointSafetyThresholds(int&, int&, int&){
    /*FIXME*/ throw std::exception();
}

void Linkbot::getJointSafetyAngles(double&, double&, double&){
    /*FIXME*/ throw std::exception();
}

/* SETTERS */
void Linkbot::resetEncoderRevs(){
    rs::linkbotResetEncoderRevs(m);
}

void Linkbot::setBuzzerFrequency (double f){
    rs::linkbotSetBuzzerFrequency(m, float(f));
}

void Linkbot::setJointAccelI(int mask, double, double, double){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setJointAccelF(int mask, double, double, double){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setJointSpeeds (int mask, double s1, double s2, double s3){
    rs::linkbotSetJointSpeeds(m, mask, s1, s2, s3);
}

void Linkbot::setJointStates(
    int mask,
    LinkbotJointState s1, double d1,
    LinkbotJointState s2, double d2,
    LinkbotJointState s3, double d3)
{
    rs::linkbotSetJointStates(m, mask,
            s1, d1,
            s2, d2,
            s3, d3);
}
void Linkbot::setJointStates(
    int mask,
    LinkbotJointState s1, double d1, double timeout1, LinkbotJointState end1,
    LinkbotJointState s2, double d2, double timeout2, LinkbotJointState end2,
    LinkbotJointState s3, double d3, double timeout3, LinkbotJointState end3
    )
{
    rs::linkbotSetJointStatesTimed(m, mask,
            s1, d1, timeout1, end1,
            s2, d2, timeout2, end2,
            s3, d3, timeout3, end3);
}

void Linkbot::setJointSafetyThresholds(int mask, int t1, int t2, int t3){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setJointSafetyAngles(int mask, double t1, double t2, double t3){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setLedColor(int r, int g, int b) {
    rs::linkbotSetLedColor(m, r, g, b);
}

/* MOVEMENT */
// Member functions take angles in degrees.
// All functions are non-blocking. Use moveWait() to wait for non-blocking
// movement functions.
void Linkbot::drive (int mask, double a1, double a2, double a3){
    rs::linkbotDrive(m, mask, a1, a2, a3);
}

void Linkbot::driveTo (int mask, double a1, double a2, double a3){
    rs::linkbotDriveTo(m, mask, a1, a2, a3);
}

void Linkbot::move (int mask, double a1, double a2, double a3){
    rs::linkbotMove(m, mask, a1, a2, a3);
}

// moveContinuous takes three angular speed coefficients. Use -1 to move
// a motor backward, +1 to move it forward.
void Linkbot::moveAccel(int mask, int relativeMask,
    double omega0_i, double timeout0, LinkbotJointState endstate0,
    double omega1_i, double timeout1, LinkbotJointState endstate1,
    double omega2_i, double timeout2, LinkbotJointState endstate2)
{
    rs::linkbotMoveAccel(m, mask, relativeMask,
            omega0_i, timeout0, endstate0,
            omega1_i, timeout1, endstate1,
            omega2_i, timeout2, endstate2);
}

void Linkbot::moveContinuous (int mask, double a1, double a2, double a3){
    rs::linkbotMoveContinuous(m, mask, a1, a2, a3);
}

void Linkbot::moveTo (int mask, double a1, double a2, double a3){
    rs::linkbotMoveTo(m, mask, a1, a2, a3);
}

void Linkbot::moveSmooth(int mask, int relativeMask, double a0, double a1, double a2){
    rs::linkbotMoveSmooth(m, mask, relativeMask, a0, a1, a2);
}

void Linkbot::moveWait(int mask){
    rs::linkbotMoveWait(m, mask);
}

void Linkbot::motorPower(int mask, int m1, int m2, int m3){
    rs::linkbotMotorPower(m, mask, m1, m2, m3);
}

void Linkbot::stop (int mask){
    rs::linkbotStop(m, mask);
}

// Passing a null pointer as the first parameter of those three functions
// will disable its respective events.
void Linkbot::setButtonEventCallback (LinkbotButtonEventCallback cb, void* userData){
    rs::linkbotSetButtonEventCallback(m, cb, userData);
}
// cb function params: button, button state, timestamp(millis)
void Linkbot::setButtonEventCallback (std::function<void(LinkbotButton, LinkbotButtonState, int)> callback){
    buttonEventCallback = callback;
    if(callback) {
        rs::linkbotSetButtonEventCallback(m, _buttonCallbackHelper, this);
    } else {
        rs::linkbotSetButtonEventCallback(m, nullptr, nullptr);
    }
}

void Linkbot::setEncoderEventCallback (LinkbotEncoderEventCallback, double granularity, void* userData){
    /*FIXME*/ throw std::exception();
}
// cb function params: joint number, angle, timestamp
void Linkbot::setEncoderEventCallback (std::function<void(int, double, int)>, double granularity){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setAccelerometerEventCallback (LinkbotAccelerometerEventCallback, void* userData){
    /*FIXME*/ throw std::exception();
}
// cb function params: x, y, z, timestamp
void Linkbot::setAccelerometerEventCallback (std::function<void(double, double, double, int)>){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setJointEventCallback(LinkbotJointEventCallback, void* userData){
    /*FIXME*/ throw std::exception();
}
void Linkbot::setJointEventCallback(std::function<void(int, LinkbotJointState, int)>){
    /*FIXME*/ throw std::exception();
}

void Linkbot::setConnectionTerminatedCallback (LinkbotConnectionTerminatedCallback, void* userData){
    /*FIXME*/ throw std::exception();
}

/* MISC */
void Linkbot::writeEeprom(uint32_t address, const uint8_t* data, size_t size){
    /*FIXME*/ throw std::exception();
}
void Linkbot::readEeprom(uint32_t address, size_t recvsize, uint8_t* buffer){
    /*FIXME*/ throw std::exception();
}
void Linkbot::writeTwi(uint32_t address, const uint8_t* data, size_t size){
    /*FIXME*/ throw std::exception();
}
void Linkbot::readTwi(uint32_t address, size_t recvsize, uint8_t* buffer){
    /*FIXME*/ throw std::exception();
}
void Linkbot::writeReadTwi(
    uint32_t address,
    const uint8_t* sendbuf,
    size_t sendsize,
    uint8_t* recvbuf,
    size_t recvsize){
    /*FIXME*/ throw std::exception();
}
void Linkbot::setPeripheralResetMask(int mask, int resetMask){
    /*FIXME*/ throw std::exception();
}
} // namespace barobo