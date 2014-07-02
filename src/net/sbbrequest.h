#ifndef SBBREQUEST_H
#define SBBREQUEST_H

#include <QtNetwork/QNetworkReply>

#include "../query/sbbquery.h"

class SBBHandler;

class SBBRequest
{
public:
    SBBRequest();
    ~SBBRequest();

    SBBRequest(SBBQuery *query, QString contentType, SBBHandler *handler);

    SBBQuery *getSBBQuery();
    QString getContentType();
    SBBHandler *getHandler();
    QNetworkReply *getReply();
    void setReply(QNetworkReply *r);

private:
    SBBQuery *query_;
    QNetworkReply *reply_;
    QString contentType_;
    SBBHandler *handler_;
};

#endif // SBBREQUEST_H
