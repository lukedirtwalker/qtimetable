#include "sbbrequest.h"

SBBRequest::SBBRequest(SBBQuery *query, QString contentType, SBBHandler *handler)
    : query_(query), reply_{nullptr} , contentType_(contentType),
      handler_(handler)
{}

SBBRequest::~SBBRequest()
{
    if(query_)
        delete query_;
}
