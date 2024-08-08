#ifndef VISITOR_H
#define VISITOR_H

class fisico;
class magico;
class sacro;

class Visitor {
public:
    virtual void visit(fisico* f) = 0;
    virtual void visit(magico* m) = 0;
    virtual void visit(sacro* s) = 0;
};

#endif
