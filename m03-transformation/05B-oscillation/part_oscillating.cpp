//
// Created by Ben on 3/19/2021.
//

#include "part_oscillating.h"

void part_oscillating::animate(double time, double delta_time) {
    double x = (1 + sin(time*rate)) * .5;
    animation_transform.translate = glm::mix(end0, end1, x);
}