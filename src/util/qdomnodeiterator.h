/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

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
