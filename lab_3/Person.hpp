#pragma once
#include <ctime>
#include <stdexcept>

using namespace std;

struct PersonID{
    int series;
    int number;
};

class Person{
private:
    PersonID m_id;
    string m_name;
    string m_surname;
    string m_patronymic;
    time_t m_date;
public:
    Person():m_id(),m_name(""), m_surname(""), m_patronymic(""),m_date(0){}

    Person(const PersonID& id, const string& name, const string& surname, 
            const string& patronymic, time_t date):m_id(id),m_name(name), 
            m_surname(surname), m_patronymic(patronymic),m_date(date){}

    string GetName() const{ return m_name; };
    string GetSurName() const{return m_surname;};
    string GetPatronymic() const{return m_patronymic;};
    time_t GetDate() const{return m_date;};
    PersonID GetID() const{return m_id;}

    void SetID(const PersonID& id) { m_id = id; }
    void SetName(const std::string& name) { m_name = name; }
    void SetSurname(const std::string& surname) { m_surname = surname; }
    void SetPatronymic(const std::string& patronymic) { m_patronymic = patronymic; }
    void SetDate(time_t date) { m_date = date; }

    string GetFullName() const{
        return m_name + " " + m_surname + " " + m_patronymic;
    }

    string ToString() const{
        string res = "Id(number): " + to_string(m_id.number) + "Id(series): " + to_string(m_id.series) +
                ",full name: " + GetFullName() + ",date:" + to_string(m_date);
        return res;
    }

};


