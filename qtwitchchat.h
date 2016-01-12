#ifndef QTWITCHCHAT_H
#define QTWITCHCHAT_H

//#include <QList>
#include <QMap>

#include "qchatservice.h"

class QTcpSocket;
class QNetworkAccessManager;
class QNetworkReply;

class QTwitchChat: public QChatService
{
    Q_OBJECT
public:
    explicit                    QTwitchChat( QObject * parent = nullptr );
    virtual                     ~QTwitchChat();

    void                        loadSettings();
    QString                     emotIcon( const QString & smileName );

private:
    void                        loadSelf();
    virtual void                loadSmiles();
    void                        loadBadges();

    void                        loadStatistic();

    void                        safeDeleteSocket();

protected:
    virtual void                timerEvent( QTimerEvent * );

public slots:
    virtual void                connect();
    virtual void                disconnect();
    virtual void                reconnect();

    void                        changeOriginalColors( bool originalColors );

private slots:
    void                        onConnected();

    void                        parseMessage();

    void                        onSocketError();

    void                        onSelfLoaded();
    void                        onSelfLoadError();

    void                        onSmilesLoaded();
    void                        onSmilesLoadError();

    void                        onBadgesLoaded();
    void                        onBadgesLoadError();

    void                        onStatisticLoaded();
    void                        onStatisticLoadError();

    void                        changeBadges( bool badges );

private:
    QTcpSocket *                socket_ = {nullptr};
    QNetworkAccessManager *     nam_;
    QString                     oauthString_;
    QString                     nickName_;
    QString                     channelName_;
    QString                     selfLink_;
    QString                     emotIconsLink_;
    QString                     badgesLink_;
    int                         reconnectTimerId_ = {-1};
    int                         statisticTimerId_ = {-1};
    int                         saveConnectionTimerId_ = {-1};
    bool                        originalColors_ = {false};
    bool                        badges_ = {false};
    QMap< QString, QString >    badgesMap_;


    static const QString        SERVICE_NAME;
    static const QString        SERVICE_USER_NAME;

    static const int            RECONNECT_INTERVAL;
    static const int            STATISTIC_INTERVAL;
    static const int            SAVE_CONNECTION_INTERVAL;
};

#endif // QTWITCHCHAT_H
