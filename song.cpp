#include "song.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include "song.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHeaderView>
Song::Song(QString t, QString a, int d,QString p) {
    title=t;
    author=a;
    duration=d;
    path=p;
}
void SongController::add_AllSongs(Song song){
    AllSongs.append(song);
}
Song SongController::get_song(int index){
    return AllSongs[index];
}
void SongController::add_Playlist(Song song){
    Playlist.append(song);
}
int SongController::search_song1(QString title)const{
    for(int i=0; i<AllSongs.size(); i++){
        if(AllSongs[i].get_title()==title)
            return i;
    }
    return -1111;
}
int SongController::search_song2(QString title)const{
    for(int i=0; i<Playlist.size(); i++){
        if(Playlist[i].get_title()==title)
            return i;
    }
    return -1111;
}
void SongController::delete_AllSongs(int index){
    for(int i=index;i<AllSongs.size()-1;i++){
        AllSongs[i]=AllSongs[i+1];
    }
    AllSongs.pop_back();
}
void SongController::delete_Playlist(int index){
    for(int i=index;i<Playlist.size()-1;i++){
        Playlist[i]=Playlist[i+1];
    }
    Playlist.pop_back();
}

MainWindow::MainWindow(QWidget *parent):///Wtf is this??? Ill find out later.:(
    QMainWindow(parent), songs(new SongController){
    setupUI();
}
MainWindow::~MainWindow(){
}
void MainWindow::setupUI(){
    QWidget *main=new QWidget(this);
    setCentralWidget(main);
    QWidget *first=new QWidget(main);
    QWidget *second=new QWidget(main);
    QWidget *third=new QWidget(main);
    QWidget *fifth=new QWidget(main);
    tablewidget=new QTableWidget(0, 4, main);
    titleedit=new QLineEdit(main);
    authoredit=new QLineEdit(main);
    durationedit=new QLineEdit(main);
    pathedit=new QLineEdit(main);
    add=new QPushButton("Add", main);
    connect(add, &QPushButton::clicked, this, &MainWindow::Add);
    QPushButton *delet=new QPushButton("Delete", main);
    connect(delet, &QPushButton::clicked, this, &MainWindow::Delet);
    QPushButton *update=new QPushButton("Update", main);
    QPushButton *filter=new QPushButton("Filter", main);
    QPushButton *next1=new QPushButton(">", main);
    connect(next1, &QPushButton::clicked, this, &MainWindow::Next);
    list=new QListWidget(main);
    QPushButton *playe=new QPushButton("Play", main);
    QPushButton *next2=new QPushButton("Next", main);
    QVBoxLayout *vertical=new QVBoxLayout{};
    vertical->addWidget(new QLabel("All songs", main));
    QStringList header{"Title", "Author", "Duration", "Path"};
    tablewidget->setHorizontalHeaderLabels(header);
    tablewidget->setWordWrap(true);
    tablewidget->verticalHeader()->setDefaultSectionSize(20);
    vertical->addWidget(tablewidget);
    QFormLayout *form=new QFormLayout{};
    form->addRow("Title", titleedit);
    form->addRow("Author", authoredit);
    form->addRow("Duration", durationedit);
    form->addRow("Path", pathedit);
    first->setLayout(form);
    vertical->addWidget(first);
    QHBoxLayout *hor=new QHBoxLayout{};
    hor->addWidget(add);
    hor->addWidget(delet);
    hor->addWidget(update);
    hor->addWidget(filter);
    second->setLayout(hor);
    vertical->addWidget(second);
    third->setLayout(vertical);
    QHBoxLayout *final=new QHBoxLayout{};
    final->addWidget(third);
    final->addWidget(next1);
    QVBoxLayout *forth=new QVBoxLayout{};
    forth->addWidget(new QLabel("Playlist", main));
    forth->addWidget(list);
    forth->addWidget(playe);
    forth->addWidget(next2);
    fifth->setLayout(forth);
    final->addWidget(fifth);
    main->setLayout(final);
    ///connect(delet, &QPushButton::clicked, this, &MainWindow::Delet);
    ///connect(next1,&QPushButton::clicked, this, &MainWindow::Next);
}
void MainWindow::Add(){
    if (!titleedit) {
        qDebug() << "title";
        return;
    }
    else if(!authoredit){
        qDebug()<<"author";
    }
    else if(!durationedit){
        qDebug()<<"duration";
    }
    else if(!pathedit){
        qDebug()<<"path";
    }
    else if(!tablewidget){
        qDebug()<<"table";
    }
    else if(!songs){
        qDebug()<<"song";
    }
    qDebug() << "Add button clicked";
    qDebug() << "Title: " << titleedit->text();
    qDebug() << "Author: " << authoredit->text();
    qDebug() << "Duration: " << durationedit->text().toInt();
    qDebug() << "Path: " << pathedit->text();
    Song t{titleedit->text(), authoredit->text(), durationedit->text().toInt(), pathedit->text()};
    songs->add_AllSongs(t);
    int currentRow=tablewidget->rowCount();
    tablewidget->insertRow(currentRow);
    tablewidget->setItem(currentRow, 0, new QTableWidgetItem(t.get_title()));
    tablewidget->setItem(currentRow, 1, new QTableWidgetItem(t.get_author()));
    tablewidget->setItem(currentRow, 2, new QTableWidgetItem(QString::number(t.get_duration())));
    tablewidget->setItem(currentRow, 3, new QTableWidgetItem(t.get_path()));
    titleedit->clear();
    authoredit->clear();
    durationedit->clear();
    pathedit->clear();
    tablewidget->resizeRowsToContents();
}
void MainWindow::Delet(){
    int current=tablewidget->currentRow();
    songs->delete_AllSongs(current);
    tablewidget->removeRow(current);
}
void MainWindow::Next(){
    int current=tablewidget->currentRow();
    Song song=songs->get_song(current);
    songs->add_Playlist(song);
    QString title=song.get_title();
    list->addItem(title);
    songs->delete_AllSongs(current);
    tablewidget->removeRow(current);
}
