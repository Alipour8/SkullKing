#include "maindatabase.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "user.h"
#include "QJsonParseError"
#include<QMessageBox>

maindatabase::maindatabase()
{
    QFile Db("MainDatabase.json") ;
       if(!Db.open(QIODevice::ReadWrite))
       {
           QMessageBox messageBox;
           messageBox.critical(0,"Error","There is a problem in opening file!");
           messageBox.setFixedSize(500,200);
       }
       Db.close();
}

void maindatabase::Add_user(user in_user)
{
    QFile Db("MainDatabase.json") ;
    if(!Db.open(QIODevice::ReadWrite))
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file");
       messageBox.setFixedSize(500,200);
       return ;
    }
    QJsonObject Newuser ;
    //make jsonobject and insert some info to it
    Newuser.insert("UserName", in_user.get_UserName());
    Newuser.insert("Password", in_user.get_Password());
    Newuser.insert("PhoneNumber", in_user.get_PhoneNumber());
    Newuser.insert("EmailAddress", in_user.get_EmailAddress());
    Newuser.insert("Firstname" , in_user.get_firstname() );
    Newuser.insert("Wins",in_user.get_wins());
    Newuser.insert("Losts",in_user.get_lost());
    Newuser.insert("scores",in_user.get_score());
    Newuser.insert("coins",in_user.get_coins());

    QJsonParseError JsonParseError;
        QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError);
        Db.close();
        QJsonObject RootObject = JsonDoc.object();
        QJsonArray UsersArray = RootObject.value("Users").toArray();
        UsersArray.append(Newuser);
        RootObject.insert("Users", UsersArray );
        JsonDoc.setObject(RootObject);
        Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        Db.write( JsonDoc.toJson());
        Db.close();
}

bool maindatabase::Check_username(QString in_username)
{
    QFile Db("MainDatabase.json");
    if(!Db.open(QIODevice::ReadOnly))
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_username )
        {
            return false ;
        }
    }
    return true ;
}

bool maindatabase::Check_PhoneNumber(QString in_PhoneNumber)
{
    QFile Db("MainDatabase.json") ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["PhoneNumber"].toString() == in_PhoneNumber )
        {
            return false ;
        }
    }
    return true ;
}

bool maindatabase::Check_EmailAddress(QString in_EmailAddress)
{
    QFile Db("MainDatabase.json") ;
    if(!Db.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["EmailAddress"].toString() == in_EmailAddress )
        {
            return false ;
        }
    }
    return true ;
}

bool maindatabase::Find_user( user &in_user)
{
    QFile Db("MainDatabase.json") ;
    if( !Db.open(QIODevice::ReadOnly))
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
       return false ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["Password"].toString() == in_user.get_Password())
        {
            in_user.set_UserName( TempObj["UserName"].toString()) ;
            in_user.set_Password( TempObj["Password"].toString()) ;
            in_user.set_coins(TempObj["coins"].toInt()) ;
            in_user.set_EmailAddress( TempObj["EmailAddress"].toString());
            in_user.set_PhoneNumber( TempObj["PhoneNumber"].toString());
            in_user.set_Firstname( TempObj["Firstname"].toString());
            return true ;

        }
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Not found current user!");
    messageBox.setFixedSize(500,200);
    return false ;
}

void maindatabase::Modify_UserDetails( user in_user )
{
    QFile Db("MainDatabase.json") ;
    if( !Db.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return  ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject jobj = JsonDoc.object() ;
    QJsonArray UsersArray = jobj["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        QJsonObject TempObj =  UsersArray.at(i).toObject();

        if( in_user.get_UserName() == TempObj["UserName"].toString() )
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject();
            Newuser["EmailAddress"] = in_user.get_EmailAddress();
            Newuser["Password"] = in_user.get_Password();
            Newuser["PhoneNumber"] = in_user.get_PhoneNumber();
            Newuser["Firstname"] = in_user.get_firstname();
            //Newuser["UserName"] = in_user.get_UserName();
            UsersArray.removeAt(i);
            UsersArray.insert(i , Newuser );
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}


bool maindatabase::userpasswordForforgot(user in_user, QString &pass)
{
    QFile Db("MainDatabase.json") ;
    if(!Db.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
      return false ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["PhoneNumber"].toString() == in_user.get_PhoneNumber())
        {
            pass = TempObj["Password"].toString();
            return true ;

        }
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error"," Not found current user");
    messageBox.setFixedSize(500,200);
    return false ;

}

bool maindatabase::showhistory(user in_user,int &wins,int &loses)
{
    QFile Db("MainDatabase.json") ;
    if(!Db.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
      return false ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_user.get_UserName())
        {
            wins = TempObj["Wins"].toInt();
            loses = TempObj["Losts"].toInt();
            return true ;

        }
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error"," Not found current user");
    messageBox.setFixedSize(500,200);
    return false ;

}

bool maindatabase::showhistory(QString name,int &wins,int &loses)
{
    QFile Db("MainDatabase.json") ;
    if(!Db.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
      return false ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == name)
        {
            wins = TempObj["Wins"].toInt();
            loses = TempObj["Losts"].toInt();
            return true ;

        }
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error"," Not found current user");
    messageBox.setFixedSize(500,200);
    return false ;

}
