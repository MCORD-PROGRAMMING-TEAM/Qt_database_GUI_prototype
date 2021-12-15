#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    static const QString sipmFilteredQueryString;

private slots:
    void on_pushButton_search_clicked();

private:
    Ui::Widget * ui;
    QSqlDatabase * mcordDatabase;
    QList<QSqlQuery *> * preparedQueries;
    QStandardItemModel * mcordModel;

    void addDataToModel(QStandardItemModel *model, QList<QSqlQuery *> * queries);
    QList<QSqlQuery *> * createQueries(QSqlDatabase * mcordDatabase);
};


#endif // WIDGET_H
