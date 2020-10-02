//
// Created by 李喆昊 on 2020/10/2.
//

#ifndef CODES_TIMER_H
#define CODES_TIMER_H
#include <ctime>
#include <cstdio>

namespace NLA {
    class Timer {
    public:
        Timer(const char *name);

        void start();

        void end();

    private:
        clock_t start_t;
        clock_t end_t;
        const char *name;
    };
}


#endif //CODES_TIMER_H
