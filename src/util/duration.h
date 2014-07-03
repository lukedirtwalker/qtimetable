#ifndef DURATION_H
#define DURATION_H

class QString;

class Duration
{
public:
    Duration();
    Duration(int seconds);

    QString toString() const;
    int getSeconds();

private:
    int mSeconds;
};

#endif // DURATION_H
