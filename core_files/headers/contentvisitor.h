#ifndef CONTENTVISITOR_H
#define CONTENTVISITOR_H

#include"QT_files/headers/viewlib.h"

class ContentVisitor : public Visitor {
private:
    QWidget* dispWidget;
public:
    ContentVisitor();
    ~ContentVisitor();

    void visitFisico(fisico* f) override;
    void visitMagico(magico* m) override;
    void visitSacro(sacro* s) override;
    
    QWidget* returnQWidget();
};

#endif
