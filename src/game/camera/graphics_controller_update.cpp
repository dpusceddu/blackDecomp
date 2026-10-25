#include "include_asm.h"

#include "game/camera/pad.hpp"

extern "C"{
extern int func_0026C9C0(void *, int);
extern int func_0026C9E0(int, int);
extern int func_0026CA00(void *, void *);
extern float func_0026C030(void *, int, int, int, int);
extern int func_0029CB50(int, int, int);
extern float func_0026C098(void *, int, int, int, int);
extern float func_0026BF60(void *, float, float);
}

void CampaignGraphics::Controller::Update() {
    float *pressure;
    float scaled1;
    float smoothNegative0;
    float scaled3;
    float smoothPositive3;
    float scaledNegative3;
    float step3;
    float smoothNegative3;
    float scaled2;
    float smoothPositive2;
    float scaledNegative2;
    float step2;
    float smoothNegative2;
    float smoothPositive1;
    float scaledNegative1;
    float step1;
    float smoothNegative1;
    float scaled0;
    float smoothPositive0;
    float scaledNegative0;
    float step0;
    float axis1;
    float negative1;
    float axis0;
    float negative0;
    float axis3;
    float negative3;
    float axis2;
    float negative2;
    int packet;
    int packetStatus;
    int backendHandle;
    int buttonIndex;
    unsigned char *state;
    unsigned char connectedNow;

    backendHandle = this->backend;
    if (backendHandle != 0) {
        connectedNow = func_0026C9C0((void *) backendHandle, this->port) == 4;
        this->connected = connectedNow;
        if (!Connected()) {
            this->initialized = 0;
            return;
        }
        packet = func_0026C9E0(this->backend, this->port);
        packetStatus = func_0026CA00((void *) this->backend, (void *) this->port);
        func_0026C030(this, 0, 0x18, packet, packetStatus);
        func_0026C030(this, 1, 0x1B, packet, packetStatus);
        func_0026C030(this, 2, 0x1A, packet, packetStatus);
        func_0026C030(this, 3, 0x19, packet, packetStatus);
        func_0026C030(this, 4, 0x16, packet, packetStatus);
        func_0026C030(this, 5, 0x17, packet, packetStatus);
        func_0026C030(this, 6, 0x15, packet, packetStatus);
        func_0026C030(this, 7, 0x14, packet, packetStatus);
        func_0026C030(this, 8, 0x14, packet, packetStatus);
        this->pressure8 = (float) func_0029CB50(packet, packetStatus, 3);
        this->pressure9 = (float) func_0029CB50(packet, packetStatus, 0);
        func_0026C098(this, 0xA, 0x1C, packet, packetStatus);
        func_0026C098(this, 0xB, 0x1E, packet, packetStatus);
        func_0026C098(this, 0xC, 0x1D, packet, packetStatus);
        func_0026C098(this, 0xD, 0x1F, packet, packetStatus);
        this->pressure14 = (float) func_0029CB50(packet, packetStatus, 1);
        this->pressure15 = (float) func_0029CB50(packet, packetStatus, 2);
        axis1 = (-(float) func_0029CB50(packet, packetStatus, 0x13) + 255.0f) - 128.0f;
        this->rawAxis1 = axis1;
        if (axis1 > 0.0f) {
            scaled1 = axis1 / 127.0f;
            this->rawAxis1 = scaled1;
            if (this->initialized == 0) {
                this->maxStep1 = scaled1;
                if (scaled1 > 0.25f) {
                    this->maxStep1 = 0.25f;
                }
            }
            smoothPositive1 = func_0026BF60(this, this->rawAxis1, this->maxStep1);
            this->axis1Negative = 0.0f;
            this->rawAxis1 = smoothPositive1;
            this->axis1Positive = smoothPositive1;
        } else {
            scaledNegative1 = axis1 * 0.0078125f;
            this->rawAxis1 = scaledNegative1;
            if (this->initialized == 0) {
                step1 = -scaledNegative1;
                this->maxStep1 = step1;
                if (step1 > 0.25f) {
                    this->maxStep1 = 0.25f;
                }
            }
            smoothNegative1 = func_0026BF60(this, this->rawAxis1, this->maxStep1);
            negative1 = -smoothNegative1;
            this->axis1Positive = 0.0f;
            this->rawAxis1 = smoothNegative1;
            this->axis1Negative = negative1;
        }
        axis0 = (float) func_0029CB50(packet, packetStatus, 0x12) - 128.0f;
        this->rawAxis0 = axis0;
        if (axis0 > 0.0f) {
            scaled0 = axis0 / 127.0f;
            this->rawAxis0 = scaled0;
            if (this->initialized == 0) {
                this->maxStep0 = scaled0;
                if (scaled0 > 0.25f) {
                    this->maxStep0 = 0.25f;
                }
            }
            smoothPositive0 = func_0026BF60(this, this->rawAxis0, this->maxStep0);
            this->axis0Negative = 0.0f;
            this->rawAxis0 = smoothPositive0;
            this->axis0Positive = smoothPositive0;
        } else {
            scaledNegative0 = axis0 * 0.0078125f;
            this->rawAxis0 = scaledNegative0;
            if (this->initialized == 0) {
                step0 = -scaledNegative0;
                this->maxStep0 = step0;
                if (step0 > 0.25f) {
                    this->maxStep0 = 0.25f;
                }
            }
            smoothNegative0 = func_0026BF60(this, this->rawAxis0, this->maxStep0);
            negative0 = -smoothNegative0;
            this->axis0Positive = 0.0f;
            this->rawAxis0 = smoothNegative0;
            this->axis0Negative = negative0;
        }
        axis3 = (-(float) func_0029CB50(packet, packetStatus, 0x11) + 255.0f) - 128.0f;
        this->rawAxis3 = axis3;
        if (axis3 > 0.0f) {
            scaled3 = axis3 / 127.0f;
            this->rawAxis3 = scaled3;
            if (this->initialized == 0) {
                this->maxStep3 = scaled3;
                if (scaled3 > 0.25f) {
                    this->maxStep3 = 0.25f;
                }
            }
            smoothPositive3 = func_0026BF60(this, this->rawAxis3, this->maxStep3);
            this->axis3Negative = 0.0f;
            this->rawAxis3 = smoothPositive3;
            this->axis3Positive = smoothPositive3;
        } else {
            scaledNegative3 = axis3 * 0.0078125f;
            this->rawAxis3 = scaledNegative3;
            if (this->initialized == 0) {
                step3 = -scaledNegative3;
                this->maxStep3 = step3;
                if (step3 > 0.25f) {
                    this->maxStep3 = 0.25f;
                }
            }
            smoothNegative3 = func_0026BF60(this, this->rawAxis3, this->maxStep3);
            negative3 = -smoothNegative3;
            this->axis3Positive = 0.0f;
            this->rawAxis3 = smoothNegative3;
            this->axis3Negative = negative3;
        }
        axis2 = (float) func_0029CB50(packet, packetStatus, 0x10) - 128.0f;
        this->rawAxis2 = axis2;
        if (axis2 > 0.0f) {
            scaled2 = axis2 / 127.0f;
            this->rawAxis2 = scaled2;
            if (this->initialized == 0) {
                this->maxStep2 = scaled2;
                if (scaled2 > 0.25f) {
                    this->maxStep2 = 0.25f;
                }
            }
            smoothPositive2 = func_0026BF60(this, this->rawAxis2, this->maxStep2);
            this->axis2Negative = 0.0f;
            this->rawAxis2 = smoothPositive2;
            this->axis2Positive = smoothPositive2;
        } else {
            scaledNegative2 = axis2 * 0.0078125f;
            this->rawAxis2 = scaledNegative2;
            if (this->initialized == 0) {
                step2 = -scaledNegative2;
                this->maxStep2 = step2;
                if (step2 > 0.25f) {
                    this->maxStep2 = 0.25f;
                }
            }
            smoothNegative2 = func_0026BF60(this, this->rawAxis2, this->maxStep2);
            negative2 = -smoothNegative2;
            this->axis2Positive = 0.0f;
            this->rawAxis2 = smoothNegative2;
            this->axis2Negative = negative2;
        }
        buttonIndex = 0;
        unsigned char *previous=this->previousStates;
        bool pressed=1;
        pressure = &this->pressure0;
        state = &this->button0;
        do {
            previous[buttonIndex] = *state;
            if (buttonIndex >= 0) {
                if (buttonIndex >= 24) {
                    if (buttonIndex < 28) *state = 0;
                } else {
                    float value = *pressure;
                    if (this->pressureThreshold < value) *state = pressed;
                    else *state = 0;
                }
            }
            buttonIndex += 1;
            pressure = (float *) (((signed char *) pressure) + 4);
            state = (unsigned char *) (((signed char *) state) + 1);
        } while (buttonIndex < 0x1C);
        this->initialized = 1;
    }
}

