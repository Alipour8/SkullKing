#include "user.h"

user::user()
{
    coins=1000;
    wins=0;
    loses=0;
    score=0;
}

void user::set_UserName(QString in_UserName)
{
    UserName = in_UserName ;
}

void user::set_Password(QString in_Pass)
{
    Password = in_Pass ;
}

void user::set_Firstname(QString in_firstname)
{
    Firstname = in_firstname;
}

void user::set_PhoneNumber(QString in_PhoneNumber)
{
    PhoneNumber =in_PhoneNumber ;
}

void user::set_EmailAddress(QString in_EmailAddress)
{
    EmailAddress = in_EmailAddress ;
}

void user::set_coins(long int _coins){
    coins=_coins;
}

int user::get_coins()
{
    return coins ;
}

QString user::get_UserName()
{
    return UserName ;
}

QString user::get_Password()
{
    return Password ;
}

QString user::get_firstname()
{
    return Firstname;
}

QString user::get_PhoneNumber()
{
    return PhoneNumber ;
}

QString user::get_EmailAddress()
{
    return EmailAddress ;
}

int user::get_wins(){
    return wins;
}

int user::get_lost(){
    return loses;
}

int user::get_score(){
    return score;
}

void user::add_coins(long int _coins){
    coins+=_coins;
}

void user::delete_coins(long int _coins){
    coins-=_coins;
}

void user::add_wins(long int _wins){
    wins+=_wins;
}

void user::add_lost(long int _loses){
    loses+=_loses;
}

void user::add_score(long _score){
    score+=(_score*10);
}

void user::delete_score(long _score){
    score-=(_score*10);
}

QString user::Get_Wins(){
    QString s = QString::number(wins);
    return s;
}

QString user::Get_Lost(){
    QString l = QString::number(loses);
    return l;
}

QString user::Get_coins(){
    QString l = QString::number(coins);
    return l;
}

QString user::Get_Score(){
    QString l = QString::number(score);
    return l;
}
