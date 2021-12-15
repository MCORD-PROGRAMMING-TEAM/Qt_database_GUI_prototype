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
       l.room          AS room,
       s.v_br          AS v_br,
       s.v_op          AS v_op,
       s.dark_current  AS dark_current
FROM location l
JOIN device d ON d.location_id = l.id
JOIN sipm s ON d.id = s.id AND d.date_from = s.date_from
WHERE (d.serial_number = coalesce(:serialNumber, d.serial_number) OR d.serial_number ISNULL)
    AND (d.purchase_date BETWEEN :purchaseDateFrom AND :purchaseDateTo OR d.purchase_date ISNULL)
    AND (l.country = coalesce(:country, l.country) OR l.country  ISNULL)
    AND (d.status = coalesce(:status, d.status) OR d.status ISNULL)
    AND (l.institution = coalesce(:institution, l.institution) OR l.institution  ISNULL)
    AND (d.model = coalesce(:model, d.model) OR d.model ISNULL)
    AND (l.room = coalesce(:room, l.room) OR l.room  ISNULL)
    AND (s.v_br BETWEEN :vBrFrom AND :vBrTo OR s.v_br ISNULL)
    AND (s.v_op BETWEEN :vOpFrom AND :vOpTo OR s.v_op ISNULL)
    AND (s.dark_current BETWEEN :darkCurrentFrom AND :darkCurrentTo OR s.dark_current ISNULL))";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mcordDatabase = new QSqlDatabase;
    *mcordDatabase = QSqlDatabase::addDatabase("QSQLITE");
    //TODO Przeniesc scieżkę z nazwa bazy danych do stałej w jakies sensowne miejsce
    //Docelowo to powinna być względna ścieżka do pliku (poczytać jak i gdzie Qt umieszcza standardowe zasoby), taka, żeby pod Linuksem też działało
    mcordDatabase->setDatabaseName("C:/Users/user/Documents/QtProjects/Qt_database_GUI_prototype/db/MCORD_Server_sqlite_db_test2.sqlite3");
    if(mcordDatabase->open())
    {
        qDebug() << "MCORD database has been opened";
    }
    else
    {
        qDebug() << "Error! MCORD database could not be opened";
    }
    mcordModel = new QStandardItemModel(this);
    //TODO Utworzyć w bazie danych tabelkę (chyba jedna wystarczy) w której będą trzymane takie dane jak lista dostępnych państw, instytucji, pokojów, możliwych stanów urządzeń, itp.,
    //tak, żeby można było je wczytać przy starcie aplikacji.
    QStringList countries = {"", "Poland", "Russia"}; //Zapoznać się z Qt Linguist, tak, żeby w programie i bazie danych były angielskie nazwy, a inne języki były uwzględnione jedynie w dedykowanym do tego narzędziu.
    ui->comboBox_country->addItems(countries);

    QStringList institutions = {"", "NCBJ", "PW", "JINR"};
    ui->comboBox_institution->addItems(institutions);

    QStringList rooms = {"", "40", "238"};
    ui->comboBox_room->addItems(rooms);

//    QStringList statuses = {"nowe", "zamontowano w belce"};
    ui->comboBox_status->addItem("", "");
    ui->comboBox_status->addItem("new", "nowe");
    ui->comboBox_status->addItem("mounted in the bar", "zamontowano w belce");

    QStringList types = {"","SiPM", "AFE", "Hub", "Scintillator"};
    ui->comboBox_type->addItems(types);

    QStringList models = {"","S13360-3075PE"};
    ui->comboBox_model->addItems(models);

    ui->dateEdit_fromPurchaseDate->setCalendarPopup(true);
    QDate dateFrom(2015,1,1);
    ui->dateEdit_fromPurchaseDate->setDate(dateFrom);

    ui->dateEdit_toPurchaseDate->setCalendarPopup(true);
    ui->dateEdit_toPurchaseDate->setDate(QDate::currentDate());

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
        qDebug() << sipmQuery->prepare(sipmFilteredQueryString);
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
    headers.append("v_br");
    headers.append("v_op");
    headers.append("dark_current");

    QString serialNumber = ui->lineEdit_serialNumber->text();
    QVariant serialNumberOrNull = serialNumber.isEmpty() ? QVariant(QVariant::String) : serialNumber; //Proponowane zamiaste tej przestażałej wersji rozwiązania nie działają

    QString country = ui->comboBox_country->currentText();
    QVariant countryOrNull = country.isEmpty() ? QVariant(QVariant::String) : country;

    QString status = ui->comboBox_status->currentData().toString();
    QVariant statusOrNull = status.isEmpty() ? QVariant(QVariant::String) : status;
//    qDebug() << statusOrNull;
    QString institution = ui->comboBox_institution->currentText();
    QVariant institutionOrNull = institution.isEmpty() ? QVariant(QVariant::String) : institution;

    QString deviceModel = ui->comboBox_model->currentText();
    QVariant deviceModelOrNull = deviceModel.isEmpty() ? QVariant(QVariant::String) : deviceModel;
//    qDebug() << deviceModel;
//    qDebug() << deviceModelOrNull;
    QString room = ui->comboBox_room->currentText();
    QVariant roomOrNull = room.isEmpty() ? QVariant(QVariant::String) : room;
    qDebug() << room;
    qDebug() << roomOrNull;

    QDateTime purchaseDateFrom = ui->dateEdit_fromPurchaseDate->date().startOfDay();

    qDebug() << purchaseDateFrom;
    qDebug() << purchaseDateFrom.toMSecsSinceEpoch();
    QDateTime purchaseDateTo = ui->dateEdit_toPurchaseDate->date().endOfDay();
    qDebug() << purchaseDateTo;
    qDebug() << purchaseDateTo.toMSecsSinceEpoch();

    double vBrFrom = ui->doubleSpinBox_vBrFrom->value();
    double vBrTo = ui->doubleSpinBox_vBrTo->value();

    double vOpFrom = ui->doubleSpinBox_vOpFrom->value();
    double vOpTo = ui->doubleSpinBox_vOpTo->value();

    double darkCurrentFrom = ui->doubleSpinBox_darkCurrentFrom->value();
    double darkCurrentTo = ui->doubleSpinBox_darkCurrentTo->value();

    for(QSqlQuery * query : *queries)
    {
        Q_ASSERT(query->driver()->hasFeature(QSqlDriver::NamedPlaceholders));
        query->bindValue(":serialNumber", serialNumberOrNull);
        query->bindValue(":purchaseDateFrom", QVariant(purchaseDateFrom.toMSecsSinceEpoch()));
        query->bindValue(":purchaseDateTo", QVariant(purchaseDateTo.toMSecsSinceEpoch()));
        query->bindValue(":country", countryOrNull);
        query->bindValue(":status", statusOrNull);
        query->bindValue(":institution", institutionOrNull);
        query->bindValue(":model", deviceModelOrNull);
        query->bindValue(":room", roomOrNull);
        query->bindValue(":vBrFrom", vBrFrom);
        query->bindValue(":vBrTo", vBrTo);
        query->bindValue(":vOpFrom", vOpFrom);
        query->bindValue(":vOpTo", vOpTo);
        query->bindValue(":darkCurrentFrom", darkCurrentFrom);
        query->bindValue(":darkCurrentTo", darkCurrentTo);
        qDebug() << query->lastQuery();
        QVariantList list = query->boundValues();
        for (int i = 0; i < list.size(); ++i)
            qDebug() << i << ": " << list.at(i).toString().toUtf8().data() << "\n";
        if(query->exec())
        {
            while(query->next())
            {
                long long purchaseDateMsc = query->value("purchase_date").toLongLong();
                QString purchaseDateText = "";
                if(purchaseDateMsc != 0)
                {
                    purchaseDateText = QDateTime::fromMSecsSinceEpoch(purchaseDateMsc).toString("dd.MM.yyyy");
                }

                QList<QStandardItem*> rowList = {
                    new QStandardItem("SiPM"),
                    new QStandardItem(query->value("serial_number").toString()),
                    new QStandardItem(purchaseDateText),
                    new QStandardItem(query->value("model").toString()),
                    new QStandardItem(query->value("status").toString()),
                    new QStandardItem(query->value("institution").toString()),
                    new QStandardItem(query->value("comment").toString()),
                    new QStandardItem(query->value("country").toString()),
                    new QStandardItem(query->value("room").toString()),
                    new QStandardItem(query->value("v_br").toString()),
                    new QStandardItem(query->value("v_op").toString()),
                    new QStandardItem(query->value("dark_current").toString())
                };
                model->appendRow(rowList);
            }
        }
        else
        {
            qDebug() << "Error! The SiPM query has failed  " << query->lastError() << query->boundValues();
//            QVariantList list = query->boundValues();
//            for (int i = 0; i < list.size(); ++i)
//                qDebug() << i << ": " << list.at(i).toString().toUtf8().data() << "\n";
        }
    }

    model->setColumnCount(headers.size());
    model->setHorizontalHeaderLabels(headers);

}

