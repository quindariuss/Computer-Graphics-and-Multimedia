//
// Created by Ben on 3/19/2021.
//

#pragma once

#include "cs4722/part.h"

class part_oscillating : public cs4722::part {
public:
    glm::vec4 end0, end1;
    double rate;

//    inline part_oscillating(glm::vec4 end0, glm::vec4 end1, double rate)
//        : end0(end0), end1(end1), rate(rate)
//        {}

    void animate(double time, double delta_time ) override;
};

