#ifndef LISTITEM_H
#define LISTITEM_H

#include <QVariant>

class ListItem: public QObject {
  Q_OBJECT

public:
  ListItem(QObject* parent = 0) : QObject(parent) {}
  virtual ~ListItem() {}
  virtual QString getId() const = 0;
  virtual QVariant data(int role) const = 0;
  virtual QHash<int, QByteArray> roleNames() const = 0;
};

#endif // LISTITEM_H
