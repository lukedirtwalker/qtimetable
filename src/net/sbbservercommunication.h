#ifndef SBBSERVERCOMMUNICATION_H
#define SBBSERVERCOMMUNICATION_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

class SBBRequest;

class SBBServerCommunication : public QObject
{
    Q_OBJECT

public:
    SBBServerCommunication();

    void sendRequest(SBBRequest *request);
    void abortRequest(SBBRequest *request);

private:
    QUrl serverUrl_;
    QNetworkAccessManager networkAccessManager_;
};

#endif // SBBSERVERCOMMUNICATION_H
