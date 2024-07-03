#ifndef BASEHAND_H
#define BASEHAND_H


// the BaseHand class is an abstract base class that defines two pure virtual
// functions, display() and getValue() It provides an interface for derived
// classes to implement their own versions of these functions
class BaseHand {
public:
    virtual void display() const = 0;
    virtual int getValue() const = 0;
};

#endif