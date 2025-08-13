#include "Utils.h"


bool Wait(double intervalo){
    static double lastUpdate = 0;
    double agora = GetTime();

    if(agora - lastUpdate >= intervalo){
        lastUpdate = agora;
        return true;
    }
    return false;
}

bool Wait2(double intervalo){
    static double lastUpdate = 0;
    double agora = GetTime();

    if(agora - lastUpdate >= intervalo){
        lastUpdate = agora;
        return true;
    }
    return false;
}

int getSign(float value){
    if(value > 0){
        return 1;
    }
    if(value == 0){
        return 0;
    }
    return -1;
}

float Slerp(float a, float b, float t) {
    return a + (b - a) * t;
}

Color darkenColor(Color color, float rate){
    return (Color){(int)(color.r * rate), (int)(color.g * rate), (int)(color.b * rate), color.a};
}

float linearFunction(float t){
    return t;
}

float easedFunction(float t){
    return (1 - powf(1 - t, 3));
}

float quadraticFunction(float t){
    return pow(t, 2.0f);
}

float rootFunction(float t){
    return pow(t, 0.5f);
}