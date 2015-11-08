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

#include "sbbquerycontainer.h"
//#include <QSystemDeviceInfo>
//#include <QtSystemInfo/QSystemInfo>

//using namespace QtMobility;

SBBQueryContainer::SBBQueryContainer()
    : Serializable{"ReqC"}
{
    // TODO device info
//    QSystemInfo info;
//    QSystemDeviceInfo dInfo;
    domStaticElementAttributes_.insert("lang","EN");
//    domStaticElementAttributes_.insert("prod",QString(dInfo.manufacturer() + " " + dInfo.model()));
    domStaticElementAttributes_.insert("prod", "Jolla Jolla");
//    domStaticElementAttributes_.insert("ver",info.version(QSystemInfo::Firmware));
    domStaticElementAttributes_.insert("ver", "1.0.7.6");
    domStaticElementAttributes_.insert("accessId","sbuR5gsaDCEzWpCzSuEnxJOmDbb5vEM1vf0tWwjY3s6eab2uj8dAiLvjisGKDnN");
}

QDomElement SBBQueryContainer::toXML(QDomDocument &query)
{
    QString instr = "version=\"ISO-8859-1\" encoding=\"1.0\"";
    query.appendChild(query.createProcessingInstruction("xml", instr));
    return Serializable::toXML(query);
}
