#ifndef MAINDATABASE_H
#define MAINDATABASE_H

#include<QMessageBox>
#include"user.h"

class maindatabase
{
public:
    maindatabase();
    static void Add_user(user in_user);
    static bool Check_username(QString in_username);//for sign in
    static bool Check_PhoneNumber(QString in_PhoneNumber);//for sign in
    static bool Check_EmailAddress(QString in_EmailAddress);//for sign in
    static bool Find_user( user &in_user );//for login
    static QVector<user> read_AllUsers();
    static user getUserdetails(int userid);
    static void Modify_UserDetails( user in_user );
    bool userpasswordForforgot(user in_user, QString &pass);
    bool showhistory(user in_user, int &wins,int &loses);
    bool showhistory(QString name, int &wins,int &loses);
    static void score(user in_user,int score);
    static void addwin(user in_user);
    static void addlost(user in_user);
};

#endif // MAINDATABASE_H
