#ifndef QDOMNODEITERATOR_H
#define QDOMNODEITERATOR_H

#include <QDomNodeList>

class QDomNodeIterator
{
        int pos_;
        const QDomNodeList &container_;
public:
        //constructors and assignments
        QDomNodeIterator(const QDomNodeList &l,int p) : pos_(p), container_(l) {}
        QDomNodeIterator(const QDomNodeIterator &)=default;
        QDomNodeIterator(QDomNodeIterator &&)=default;
        QDomNodeIterator &operator=(const QDomNodeIterator &)=default;
        QDomNodeIterator &operator=(QDomNodeIterator &&)=default;

        //increment
        QDomNodeIterator &operator++(){ pos_++; return *this;}

        //comparison
        bool operator==(const QDomNodeIterator&o) {
            return pos_==o.pos_ && container_==o.container_;
        }
        bool operator!=(const QDomNodeIterator&o){
            return pos_!=o.pos_ || container_!=o.container_;
        }

        //indirection
        QDomNode operator*() { return container_.at(pos_);}
};

//begin and end
inline QDomNodeIterator begin(const QDomNodeList &l)
{ return QDomNodeIterator(l, 0);}

inline QDomNodeIterator end(const QDomNodeList &l)
{ return QDomNodeIterator(l, l.size());}

#endif // QDOMNODEITERATOR_H
