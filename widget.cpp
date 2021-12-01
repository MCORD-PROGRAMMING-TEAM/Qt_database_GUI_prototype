#include "widget.h"
#include "ui_widget.h"

const QString Widget::sipmFilteredQueryString =
        R"(SELECT d.serial_number AS serial_number,
       d.purchase_date AS purchase_date,
       d.model 		   AS model,
       d.status        AS status,
       d.comments 	   AS comments,
       l.institution   AS institution,
       l.country       AS country,
       l.room          AS room
FROM location l
JOIN device d ON d.location_id = l.id
JOIN sipm s ON d.id = s.id AND d.date_from = s.date_from
WHERE (d.serial_number = coalesce(:serialNumber, d.serial_number) OR d.serial_number ISNULL) AND
      (d.purchase_date = coalesce(:purchaseDate, d.purchase_date) OR d.purchase_date ISNULL) AND
      (d.model = coalesce(:model, d.model) OR d.model ISNULL) AND
      (d.status = coalesce(:status, d.status) OR d.status ISNULL) AND
      (l.institution = coalesce(:institution, l.institution) OR l.institution  ISNULL) AND
      (l.country = coalesce(:country, l.country) OR l.country  ISNULL) AND
      (l.room = coalesce(:room, l.room) OR l.room  ISNULL))";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mcordDatabase = QSqlDatabase::addDatabase("QSQLITE");
    //TODO Przeniesc scieżkę z nazwa bazy danych do stałej w jakies sensowne miejsce
    //Docelowo to powinna być względna ścieżka do pliku (poczytać jak i gdzie Qt umieszcza standardowe zasoby), taka, żeby pod Linuksem też działało
    mcordDatabase.setDatabaseName("C:/Users/user/Documents/QtProjects/Qt_database_GUI_prototype/db/MCORD_Server_sqlite_db.sqlite3");
    if(mcordDatabase.open())
    {
        qDebug() << "MCORD database has been opened";
        sipmQuery.prepare(sipmFilteredQueryString);
    }
    else
    {
        qDebug() << "Error! MCORD database could not be opened";
    }



    //TODO Utworzyć w bazie danych tabelkę (chyba jedna wystarczy) w której będą trzymane takie dane jak lista dostępnych państw, instytucji, pokojów, możliwych stanów urządzeń, itp.,
    //tak, żeby można było je wczytać przy starcie aplikacji.
    QStringList countries = {"Poland", "Russia"}; //Zapoznać się z Qt Linguist, tak, żeby w programie i bazie danych były angielskie nazwy, a inne języki były uwzględnione jedynie w dedykowanym do tego narzędziu.
    ui->comboBox_country->addItems(countries);

    QStringList institutions = {"NCBJ", "PW", "JINR"};
    ui->comboBox_institution->addItems(institutions);

    QStringList rooms = {"", "40", "238"};
    ui->comboBox_room->addItems(rooms);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_search_clicked()
{
    if(mcordDatabase.isOpen())
    {
        qDebug() << "MCORD database is open";
    }
    else
    {
        qDebug() << "Error! MCORD database is closed";
    }

    sipmQuery.bindValue(":serialNumber", ui->lineEdit_serialNumber->text());
    mcordModel->setQuery(std::move(sipmQuery));
    ui->tableView_all->setModel(mcordModel);
}


void Widget::on_pushButton_clicked()
{

}
