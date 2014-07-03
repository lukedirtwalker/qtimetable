#ifndef SBBREQUEST_H
#define SBBREQUEST_H

#include <QtNetwork/QNetworkReply>

#include "../query/sbbquery.h"

class SBBHandler;

class SBBRequest
{
public:
    SBBRequest(SBBQuery *query = nullptr, QString contentType = "",
               SBBHandler *handler = nullptr);
    ~SBBRequest();

    inline SBBQuery *getSBBQuery();
    inline QString getContentType();
    inline SBBHandler *getHandler();
    inline QNetworkReply *getReply();
    inline void setReply(QNetworkReply *r);

private:
    SBBQuery *query_;
    QNetworkReply *reply_;
    QString contentType_;
    SBBHandler *handler_;
};

inline SBBQuery *SBBRequest::getSBBQuery() { return query_;}

inline QString SBBRequest::getContentType() { return contentType_;}

inline void SBBRequest::setReply(QNetworkReply *r) { reply_ = r;}

inline QNetworkReply *SBBRequest::getReply() { return reply_;}

inline SBBHandler *SBBRequest::getHandler() { return handler_;}

#endif // SBBREQUEST_H
