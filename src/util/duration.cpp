#include "duration.h"

#include <QString>

Duration::Duration()
{
    this->mSeconds = 0;
}

Duration::Duration(int seconds)
{
    this->mSeconds = seconds;
}

int Duration::getSeconds()
{
    return this->mSeconds;
}

QString Duration::toString() const
{
    QString res;
    int duration = this->mSeconds;
    //    int seconds = (int) (duration % 60);
    duration /= 60;
    int minutes = (int) (duration % 60);
    duration /= 60;
    int hours = (int) (duration % 24);
    int days = (int) (duration / 24);
    if((hours == 0)&&(days == 0))
        return res.sprintf("0:%02d", minutes);
    if (days == 0)
        return res.sprintf("%02d:%02d", hours, minutes);
    return res.sprintf("%dd%02d:%02d", days, hours, minutes);
}
