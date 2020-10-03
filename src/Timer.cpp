//
// Created by 李喆昊 on 2020/10/2.
//
#include "../include/Timer.h"

using namespace ReNLA;

Timer::Timer(const char *name) {this->name = name;}

void Timer::start() {start_t = clock();}

void Timer::end() {end_t = clock();
    printf("[Timer] Duration of $%s$: %f s\n", name, float(end_t - start_t) / CLOCKS_PER_SEC);
}