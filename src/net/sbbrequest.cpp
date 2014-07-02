#include "sbbrequest.h"

SBBRequest::SBBRequest() : reply_{nullptr}, query_{nullptr}, contentType_{""},
    handler_{nullptr}
{}

SBBRequest::~SBBRequest()
{
    if(query_)
        delete query_;
}

SBBRequest::SBBRequest(SBBQuery *query, QString contentType, SBBHandler *handler)
    : reply_{nullptr}, query_(query), contentType_(contentType),
      handler_(handler)
{}

SBBQuery *SBBRequest::getSBBQuery()
{
    return query_;
}

QString SBBRequest::getContentType()
{
    return contentType_;
}

void SBBRequest::setReply(QNetworkReply *r)
{
    reply_ = r;
}

QNetworkReply *SBBRequest::getReply()
{
    return reply_;
}

SBBHandler *SBBRequest::getHandler()
{
    return handler_;
}
