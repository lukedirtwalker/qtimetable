#ifndef SBBHANDLER_H
#define SBBHANDLER_H

#include "../net/sbbservercommunication.h"
#include "../util/globalshared.h"

typedef enum {H_STOPPED,H_STARTED,H_EARLIER,H_LATER,H_READY} eSBBHandlerState;

class SBBHandler : public QObject
{
    Q_OBJECT
public:
    SBBHandler();

    inline QString getErrorMessage();

public slots:
    virtual void parseResponse();

signals:
    void parsingFinished(eStatusID id);

protected:
    virtual void parseXMLResponse(QDomDocument xml) = 0;
    virtual void parseHTMLResponse(QString html) = 0;
    virtual void parseNoTypeResponse(QByteArray data) = 0;


    virtual void sendRequest(SBBRequest *r);
    virtual void stopRequest();

    QString SBBErrorMessage_;
    SBBServerCommunication SBBServerCommunication_;
    SBBRequest *pendingRequest_;
    eSBBHandlerState state_;
};

inline QString SBBHandler::getErrorMessage() { return SBBErrorMessage_;}

#endif // SBBHANDLER_H
