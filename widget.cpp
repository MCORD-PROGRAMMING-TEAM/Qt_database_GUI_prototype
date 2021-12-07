#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

const QString Widget::sipmFilteredQueryString =
        R"(SELECT d.serial_number AS serial_number,
       d.purchase_date AS purchase_date,
       d.model 		   AS model,
       d.status        AS status,
       d.comments 	   AS comment,
       l.institution   AS institution,
       l.country       AS country,
       l.room          AS room
FROM location l
JOIN device d ON d.location_id = l.id
JOIN sipm s ON d.id = s.id AND d.date_from = s.date_from
WHERE (d.serial_number = coalesce(:serialNumber, d.serial_number) OR d.serial_number ISNULL))";
//AND (d.purchase_date = coalesce(:purchaseDate, d.purchase_date) OR d.purchase_date ISNULL)

//const QString Widget::sipmFilteredQueryString =
//        R"(SELECT d.serial_number AS serial_number,
//       d.purchase_date AS purchase_date,
//       d.model 		   AS model,
//       d.status        AS status,
//       d.comments 	   AS comments,
//       l.institution   AS institution,
//       l.country       AS country,
//       l.room          AS room
//FROM location l
//JOIN device d ON d.location_id = l.id
//JOIN sipm s ON d.id = s.id AND d.date_from = s.date_from
//WHERE (d.serial_number = coalesce(:serialNumber, d.serial_number) OR d.serial_number ISNULL) AND
//      (d.purchase_date = coalesce(:purchaseDate, d.purchase_date) OR d.purchase_date ISNULL) AND
//      (d.model = coalesce(:model, d.model) OR d.model ISNULL) AND
//      (d.status = coalesce(:status, d.status) OR d.status ISNULL) AND
//      (l.institution = coalesce(:institution, l.institution) OR l.institution  ISNULL) AND
//      (l.country = coalesce(:country, l.country) OR l.country  ISNULL) AND
//      (l.room = coalesce(:room, l.room) OR l.room  ISNULL))";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mcordDatabase = new QSqlDatabase;
    *mcordDatabase = QSqlDatabase::addDatabase("QSQLITE");
    //TODO Przeniesc scieżkę z nazwa bazy danych do stałej w jakies sensowne miejsce
    //Docelowo to powinna być względna ścieżka do pliku (poczytać jak i gdzie Qt umieszcza standardowe zasoby), taka, żeby pod Linuksem też działało
    mcordDatabase->setDatabaseName("C:/Users/user/Documents/QtProjects/Qt_database_GUI_prototype/db/MCORD_Server_sqlite_db.sqlite3");
    if(mcordDatabase->open())
    {
        qDebug() << "MCORD database has been opened";
    }
    else
    {
        qDebug() << "Error! MCORD database could not be opened";
    }
    mcordModel = new QStandardItemModel(parent);
    //TODO Utworzyć w bazie danych tabelkę (chyba jedna wystarczy) w której będą trzymane takie dane jak lista dostępnych państw, instytucji, pokojów, możliwych stanów urządzeń, itp.,
    //tak, żeby można było je wczytać przy starcie aplikacji.
    QStringList countries = {"", "Poland", "Russia"}; //Zapoznać się z Qt Linguist, tak, żeby w programie i bazie danych były angielskie nazwy, a inne języki były uwzględnione jedynie w dedykowanym do tego narzędziu.
    ui->comboBox_country->addItems(countries);

    QStringList institutions = {"", "NCBJ", "PW", "JINR"};
    ui->comboBox_institution->addItems(institutions);

    QStringList rooms = {"", "40", "238"};
    ui->comboBox_room->addItems(rooms);

//    QStringList statuses = {"nowe", "zamontowane w belce"};
    ui->comboBox_status->addItem("", "");
    ui->comboBox_status->addItem("new", "nowe");
    ui->comboBox_status->addItem("mounted in the bar", "zamontowane w belce");

    QStringList types = {"","SiPM", "AFE", "Hub", "scintillator"};
    ui->comboBox_type->addItems(types);

    QStringList models = {"","S13360-3075PE"};
    ui->comboBox_model->addItems(models);

    preparedQueries = createQueries(mcordDatabase);
}

Widget::~Widget()
{
    delete ui;
    for(const QSqlQuery * query: *preparedQueries)
    {
        delete query;
    }
    delete preparedQueries;

}


void Widget::on_pushButton_search_clicked()
{
    if(mcordDatabase->isOpen())
    {
        qDebug() << "MCORD database is open";
    }
    else
    {
        //TODO Wdrożyć jakieś narzędzie do logowania błędów
        qDebug() << "Error! MCORD database is closed";
    }


    addDataToModel(mcordModel, preparedQueries);
    ui->tableView_all->setModel(mcordModel);
}

QList<QSqlQuery *> * Widget::createQueries(QSqlDatabase * mcordDatabase)
{
    QList<QSqlQuery *> * queries = new QList<QSqlQuery *>;
    if(mcordDatabase->open())
    {
        QSqlQuery * sipmQuery = new QSqlQuery(mcordDatabase->database());
        sipmQuery->prepare(sipmFilteredQueryString);
        queries->append(sipmQuery);
    }
    return queries;
}

void Widget::addDataToModel(QStandardItemModel * model, QList<QSqlQuery *> * queries)
{
    model->clear();

    //TODO Nazwy kolumn przenieść do stałej i utworzyć jakieś miejsce do przechowywania tego typu informacji.
    // Docelowo wdrożyć narzędzie umożliwiające wielojęzyczność Qt Linguist
    QStringList headers;
    headers.append("Type");
    headers.append("Serial number");
    headers.append("Purchase date");
    headers.append("Model");
    headers.append("Status");
    headers.append("Institution");
    headers.append("Comment");
    headers.append("Country");
    headers.append("Room");

    QString serialNumber = ui->lineEdit_serialNumber->text();
    QVariant serialNumberOrNull = serialNumber.isEmpty() ? QVariant(QVariant::String) : serialNumber;  //Proponowane zamiaste tej przestażałej wersji rozwiązania nie działają

//    QString purchaseDate = ui->dateEdit_purchaseDate->text();
//    QVariant purchaseDateOrNull = purchaseDate.isEmpty() ? QVariant(QVariant::String) : purchaseDate;

    for(QSqlQuery * query : *queries)
    {
        query->bindValue(":serialNumber", serialNumberOrNull);
//        query->bindValue(":purchaseDate", purchaseDateOrNull);
        if(query->exec())
        {
            while(query->next())
            {
                QList<QStandardItem*> rowList = {
                    new QStandardItem("SiPM"),
                    new QStandardItem(query->value("serial_number").toString()),
                    new QStandardItem(query->value("purchase_date").toString()),
                    new QStandardItem(query->value("model").toString()),
                    new QStandardItem(query->value("status").toString()),
                    new QStandardItem(query->value("institution").toString()),
                    new QStandardItem(query->value("comment").toString()),
                    new QStandardItem(query->value("country").toString()),
                    new QStandardItem(query->value("room").toString())
                };
                model->appendRow(rowList);
            }
        }
        else
        {
            qDebug() << "Error! The SiPM query has failed";
        }
    }

    model->setColumnCount(headers.size());
    model->setHorizontalHeaderLabels(headers);

}
