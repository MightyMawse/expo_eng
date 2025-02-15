#pragma once
#include "typedef.h"
#include <vector>
#include <algorithm>

static class Utils {
public:
    static float Round_2DP(float var)
    {
        float value = (int)(var * 100 + .5);
        return (float)value / 100;
    }

    static void SplitInvertCastPos(std::vector<Vertex>& castPoints) {
        //std::vector<Vertex> secondHalf;
        //int midIndex = (castPoints.size() / 2) - 1;
        //for (int i = midIndex; i < castPoints.size(); i++) {
        //    secondHalf.push_back(castPoints[i]);
        //}

        //castPoints.erase(castPoints.begin() + midIndex, castPoints.end());

        //std::reverse(secondHalf.begin(), secondHalf.end());
        //std::sort(secondHalf.begin(), secondHalf.end());

        //std::sort(castPoints.begin(), secondHalf.end());

        //castPoints.insert(castPoints.begin(), secondHalf.begin(), secondHalf.end());
        std::sort(castPoints.begin(), castPoints.end());
    }

    // NOTE: A needs to be the offset angle, not the world space angle
    static float GetRayRange(float distance, float a) {
        float range = distance * Utils::Round_2DP(cos(DEG(a)));
        return range;
    }
};