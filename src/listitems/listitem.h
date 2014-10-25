#ifndef LISTITEM_H
#define LISTITEM_H

#include <QVariant>

class ListItem: public QObject {
  Q_OBJECT

public:
  ListItem(QObject* parent = nullptr) : QObject(parent) {}
  virtual ~ListItem() {}
  virtual QString getId() const {return QString();}
  virtual QVariant data(int role) const = 0;
  virtual QHash<int, QByteArray> roleNames() const = 0;
  virtual bool setData(const QVariant &value, int role) = 0;
};

#endif // LISTITEM_H
