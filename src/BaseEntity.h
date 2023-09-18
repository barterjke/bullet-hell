#pragma once
#include <sys/_types/_size_t.h>

class BaseEntity {
  public:
    size_t id;
    virtual void Think() = 0;
    virtual ~BaseEntity(){};
};