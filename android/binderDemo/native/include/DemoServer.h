#ifndef _DEMO_SERVER_H_
#define _DEMO_SERVER_H_

#include "IDemo.h"
class DemoServer : public BnDemo {
public:
    virtual void test();
};
#endif
