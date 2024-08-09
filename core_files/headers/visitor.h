#ifndef VISITOR_H
#define VISITOR_H

class fisico;
class magico;
class sacro;

class Visitor {
public:
    virtual void visitFisico(fisico* f) = 0;
    virtual void visitMagico(magico* m) = 0;
    virtual void visitSacro(sacro* s) = 0;
};

#endif
