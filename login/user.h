#ifndef USER_H
#define USER_H

#include<QString>
#include<QVector>
#include<QDebug>

using namespace std;

class user
{
public:
    user();
private:
    QString UserName;
    QString Password ;
    QString PhoneNumber ;
    QString EmailAddress ;
    QString Firstname;//Firstname means Name
    long int coins;
    int wins;
    int loses;
    long score;
public:
    void set_coins(long int _coins);
    void set_UserName(QString in_UserName) ;
    void set_Password(QString in_Pass) ;
    void set_Firstname(QString in_firstname) ;
    void set_PhoneNumber(QString in_PhoneNumber) ;
    void set_EmailAddress(QString in_EmailAddress) ;
    QString get_UserName() ;
    QString get_Password() ;
    QString get_firstname() ;
    QString get_PhoneNumber() ;
    QString get_EmailAddress() ;
    QString Get_Wins();
    QString Get_Lost();
    QString Get_coins();
    QString Get_Score();
    int get_coins() ;
    int get_wins();
    int get_lost();
    int get_score();
    void add_coins(long int _coins);
    void delete_coins(long int _coins);
    void add_wins(long int _wins);
    void add_lost(long int _loses);
    void add_score(long _score);
    void delete_score(long _score);
};

#endif // USER_H
