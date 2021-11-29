#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mcordDatabase = QSqlDatabase::addDatabase("QSQLITE");
    //TODO Przeniesc sciezke z nazwa bazy danych do stałej w jakies sensowne miejsce
    //Docelowo to powinna być względna ścierzka do pliku (poczytać jak i gdzie Qt umieszcza standardowe zasoby), taka, żeby pod Linuksem teżdziałało
    mcordDatabase.setDatabaseName("C:/Users/user/Documents/QtProjects/Qt_database_GUI_prototype/db/MCORD_Server_sqlite_db.sqlite3");
    if(mcordDatabase.open())
        qDebug() << "Database is open";
    else
        qDebug() << "Nie udalo się otworzyc bazy danych";

    //TODO Utworzyć w bazie danych tabelkę (chyba jedna wystarczy) w której będą trzymane takie dane jak lista dostępnych państw, instytucji, pokojów, możliwych stanów urządzeń, itp.,
    //tak, żeby można było je wczytać przy starcie aplikacji.
    QStringList countries = {"Poland", "Russia"}; //Zapoznać się z Qt Linguist, tak, żeby w programie i bazie danych były angielskie nazwy, a inne języki były uwzględnione jedynie w dedykowanym do tego narzędziu.
    ui->comboBox_country->addItems(countries);

    QStringList institutions = {"NCBJ", "PW", "JINR"};
    ui->comboBox_institution->addItems(institutions);

    QStringList rooms = {"40", "238"};
    ui->comboBox_room->addItems(rooms);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
// ui->comboBox_country;
}

