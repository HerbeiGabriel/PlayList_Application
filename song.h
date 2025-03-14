#ifndef SONG_H
#define SONG_H
#include <QString>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMainWindow>
#include <QVector>

class Song{
private:
    QString title;
    QString author;
    int duration;
    QString path;
public:
    Song(QString t, QString a, int d,QString p);
    QString get_title()const{return title;}
    void set_title(QString t){title=t;}
    QString get_author()const{return author;}
    void set_author(QString a){author=a;}
    int get_duration()const{return duration;}
    void set_duration(int d){duration=d;}
    QString get_path()const{return path;}
    void set_path(QString p){path=p;}
};
class SongController{
private:
    QVector<Song> AllSongs;
    QVector<Song> Playlist;
public:
    void add_AllSongs(Song song);
    int search_song1(QString title)const;
    int search_song2(QString title)const;
    void delete_AllSongs(int index);
    void add_Playlist(Song song);
    void delete_Playlist(int index);
    Song get_song(int index);

};

class MainWindow: public QMainWindow{
    Q_OBJECT
private:
    SongController *songs;
    QTableWidget *tablewidget;
    QLineEdit *titleedit;
    QLineEdit *authoredit;
    QLineEdit *durationedit;
    QLineEdit *pathedit;
    QPushButton *add;
    QPushButton *delet;
    QListWidget *list;
    QPushButton *next1;

    void setupUI();
private slots:
    void Add();
    void Delet();
    void Next();
public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
};

#endif // SONG_H
