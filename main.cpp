#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <iterator>
#include <windows.h>
using namespace std;
class Flight{
private:
    double departure_coordinates[2]{};
    int total_seats;
    bool is_private;
    char airfield_category;
    char* airport_name;
    float fuel_needed;
    int days_persons;
    int days_money;
    int* persons_bookedInNDays;
    float* money_earnedInNDays;
    const int flight_id;
    int crew_members_number;
    string company_name;
    string* crew_members_names;
    int seats_occupied[500]{};
public:
    static int id_count;
    void setDeparture_coordinates(double latitude,double longitude);
    double* getDeparture_coordinates();
    void setTotal_seats(int seat_number);
    int getTotal_seats();
    void setIs_private(bool type);
    bool getIs_private();
    void setAirfield_category(char category);
    char getAirfield_category();
    void setAirport_name(char* name);
    char* getAirport_name();
    void setFuel_needed(float fuel);
    float getFuel_needed();
    void setPersons_bookedInNDays(int days1, int* persons);
    int* getPersons_bookedInNDays();
    void setMoney_earnedInNDays(int days1, float* money);
    float* getMoney_earnedInNDays();
    int getFlight_id();
    void setCompany_name(string company);
    string getCompany_name();
    void setCrew_members_names(int number, string* names);
    string* getCrew_members_names();
    void setSeats_occupied(int Snumber, int* seats);
    int* getSeats_occupied();
    Flight();
    Flight(double latitude, double longitude, int seat_number, bool type,char category, char* name, float fuel, int days1,
           int* persons, int days2, float* money, string company, int number, string* names,int Snumber, int* seats);
    Flight(double latitude, double longitude);
    Flight(const Flight& flight_sec);
    ~Flight();
    Flight& operator=(const Flight& flight_sec);
    friend ostream& operator<<(ostream& out, const Flight& flight);
    friend istream& operator>>(istream& in, Flight& flight);
    int book_seat();
    const Flight& operator++();
    const Flight operator++(int);
    Flight operator+(const Flight& flight_sec);
    Flight operator-(const Flight& flight_sec);
    bool operator<(const Flight& flight_sec);
    bool operator==(const Flight& flight_sec);
    int& operator[](int i);
    explicit operator int();
};
int Flight::id_count=0;

Flight::operator int(){
    return int(this->fuel_needed)+1;
}
int& Flight::operator[](int i) {
    if(i>total_seats){
        cout<<"\nIndex out of range! Converted to max index.\n";
        return seats_occupied[total_seats];
    }
    return this->seats_occupied[i];
}

bool Flight::operator<(const Flight &flight_sec) {
    if(this->total_seats < flight_sec.total_seats)
        return true;
    if((this->total_seats == flight_sec.total_seats)&&(this->fuel_needed < flight_sec.fuel_needed))
        return true;
    return false;
}
bool Flight::operator==(const Flight& flight_sec){
    int ok=1;
    for(int i=0; i<crew_members_number; ++i){
        if(this->crew_members_names[i] != flight_sec.crew_members_names[i])
            ok=0;}
    for(int i=0; i<= flight_sec.total_seats; ++i){
        if(this->seats_occupied[i] != flight_sec.seats_occupied[i])
            ok=0;}
    for(int i=0;i < days_persons ; ++i){
        if(this->persons_bookedInNDays[i] != flight_sec.persons_bookedInNDays[i])
            ok=0;}
    for(int i=0;i < days_money ; ++i){
        if(this->money_earnedInNDays[i] != flight_sec.money_earnedInNDays[i])
            ok=0;}
    if(strcmp(this->airport_name, flight_sec.airport_name)!=0)
        ok=0;

    if(ok==1)
        if((this->departure_coordinates[0] == flight_sec.departure_coordinates[0])
           &&(this->departure_coordinates[1] == flight_sec.departure_coordinates[1])
           &&(this->total_seats ==  flight_sec.total_seats)
           &&(this->is_private == flight_sec.is_private)
           &&(this->airfield_category == flight_sec.airfield_category)
           &&(this->fuel_needed == flight_sec.fuel_needed)
           &&(this->days_persons == flight_sec.days_persons)
           &&(this->days_money == flight_sec.days_money)
           &&(this->company_name == flight_sec.company_name)
           &&(this->crew_members_number == flight_sec.crew_members_number))
            return true;


    return false;
}

Flight Flight::operator+(const Flight& flight_sec){
    Flight flight;
    flight = *this;
    flight.total_seats = this->total_seats + flight_sec.total_seats;
    flight.fuel_needed = this->fuel_needed + flight_sec.fuel_needed;
    return flight;
}

Flight Flight::operator-(const Flight &flight_sec) {
    Flight flight;
    flight = *this;
    flight.total_seats = this->total_seats - flight_sec.total_seats;
    flight.fuel_needed = this->fuel_needed - flight_sec.fuel_needed;
    return flight;
}

const Flight& Flight::operator++() {
    this->total_seats++;
    return *this;
}

const Flight Flight::operator++(int) {
    Flight aux(*this);
    this->total_seats++;
    return aux;
}

int Flight::book_seat(){
    int ok=1,seat;
    cout<<"Please select a seat from the list bellow (occupied seats are marked by X)\n";
    if(this->total_seats>9)
        for(int i=1; i <= 9; i++)
        {
            if (this->seats_occupied[i]==1)
                cout<<" X"<<" ";
            else
                cout<<" "<<i<<" ";
        }
    else
        for(int i=1; i <= this->total_seats; i++)
        {
            if (this->seats_occupied[i]==1)
                cout<<" X"<<" ";
            else
                cout<<" "<<i<<" ";
        }
    cout<<"\n";
    for(int i=10; i <= this->total_seats; i++){
        if (this->seats_occupied[i]==1)
            cout<<" X"<<" ";
        else
            cout<<i<<" ";
        if(i%9==0)
            cout<<"\n";

    }
    cin>>seat;
    while ((this->seats_occupied[seat]==1)||(seat>this->total_seats)||(seat<1)){
        cout<<"\nThis seat is already booked, please select another OR -1 to exit!" ;
        cin>>seat;
        if(seat==-1){
            ok=0;
            break;
        }
    }
    if(ok) {
        this->seats_occupied[seat] = 1;
        return seat;
    }
    else{
        cout<<"\nNo seat was booked!\n";
        return -1;
    }
}

void Flight::setDeparture_coordinates(double latitude,double longitude){
    this->departure_coordinates[0] = latitude;
    this->departure_coordinates[1] = longitude;
}

double* Flight::getDeparture_coordinates(){
    return departure_coordinates;
}

void Flight::setTotal_seats(int seat_number){
    this->total_seats = seat_number;
}

int Flight::getTotal_seats(){
    return this->total_seats;
}

void Flight::setIs_private(bool type){
    this->is_private = type;
}

bool Flight::getIs_private(){
    return this->is_private;
}

void Flight::setAirfield_category(char category){
    this->airfield_category = category;
}

char Flight::getAirfield_category(){
    return this->airfield_category;
}

void Flight::setAirport_name(char* name){
    if (this->airport_name != nullptr)
        delete[] this->airport_name;
    this->airport_name = new char[strlen(name)+1];
    strcpy(this->airport_name, name);
}

char* Flight::getAirport_name(){
    return this->airport_name;
}

void Flight::setFuel_needed(float fuel){
    this->fuel_needed = fuel;
}

float Flight::getFuel_needed(){
    return this->fuel_needed;
}

void Flight::setPersons_bookedInNDays(int days1, int* persons){
    this->days_persons=days1;
    if(this->persons_bookedInNDays != nullptr)
        delete[] persons_bookedInNDays;
    this->persons_bookedInNDays = new int[days_persons];
    for(int i=0;i < days1 ; ++i)
        this->persons_bookedInNDays[i] = persons[i];
}

int* Flight::getPersons_bookedInNDays(){
    return this->persons_bookedInNDays;
}

void Flight::setMoney_earnedInNDays(int days1, float* money){
    this->days_money=days1;
    if(this->money_earnedInNDays!= nullptr)
        delete[] money_earnedInNDays;
    this->money_earnedInNDays = new float[days_money];
    for(int i=0;i < days1 ; ++i)
        this->money_earnedInNDays[i] = money[i];
}

float* Flight::getMoney_earnedInNDays(){
    return this->money_earnedInNDays;
}

int Flight::getFlight_id(){
    return flight_id;
}

void Flight::setCompany_name(string company){
    this->company_name = company;
}

string Flight::getCompany_name(){
    return this->company_name;
}

void Flight::setCrew_members_names(int number, string* names){
    this->crew_members_number = number;
    if(this->crew_members_names != nullptr)
        delete[] crew_members_names;
    this->crew_members_names = new string[number];
    for(int i=0; i<crew_members_number; ++i)
        this->crew_members_names[i] = names[i];
}

string* Flight::getCrew_members_names(){
    return this->crew_members_names;
}

void Flight:: setSeats_occupied(int Snumber, int *seats){
    for(int i=0; i <= this->total_seats; i++)
        seats_occupied[i]=0;

    for(int i=0; i<=Snumber; ++i)
        this->seats_occupied[seats[i]] = 1 ;

}

int* Flight::getSeats_occupied(){
    return this->seats_occupied;
}

Flight::Flight():flight_id(id_count++) {
    this->departure_coordinates[0] = 0;
    this->departure_coordinates[1] = 0;
    this->total_seats = 0;
    this->is_private = false;
    this->airfield_category = 'S';
    this->airport_name = new char[strlen("None")+1];
    strcpy(this->airport_name, "None");
    this->fuel_needed = 0;
    this->days_persons = 0;
    this->persons_bookedInNDays = nullptr;
    this->days_money = 0;
    this->money_earnedInNDays = nullptr;
    this->company_name = "None";
    this->crew_members_number = 0;
    this->crew_members_names = nullptr;
    for(int i=0; i <= this->total_seats; i++)
        seats_occupied[i]=0;
}

Flight::Flight(double latitude, double longitude, int seat_number, bool type,char category, char* name, float fuel, int days1,int* persons, int days2, float* money, string company, int number, string* names,int Snumber, int* seats):flight_id(id_count++) {
    this->departure_coordinates[0] = latitude;
    this->departure_coordinates[1] = longitude;
    this->total_seats = seat_number;
    this->is_private = type;
    this->airfield_category = category;
    this->fuel_needed = fuel;
    this->days_persons=days1;
    this->days_money=days2;
    this->company_name = company;
    this->crew_members_number = number;
    for(int i=1; i <= this->total_seats; i++)
        seats_occupied[i]=0;

    this->airport_name = new char[strlen(name)+1];
    strcpy(this->airport_name, name);


    this->persons_bookedInNDays = new int[days_persons];
    for(int i=0;i < days1 ; ++i)
        this->persons_bookedInNDays[i] = persons[i];

    this->money_earnedInNDays = new float[days_money];
    for(int i=0;i < days2 ; ++i)
        this->money_earnedInNDays[i] = money[i];

    this->crew_members_names = new string[number];
    for(int i=0; i<crew_members_number; ++i)
        this->crew_members_names[i] = names[i];

    for(int i=1; i<=Snumber; ++i) {


        if (seats[i]<=this->total_seats)
            this->seats_occupied[seats[i]] = 1;
        cout<<int(seats[i])<<"ASDAS"<<endl;

    }
}

Flight::Flight(double latitude, double longitude):flight_id(id_count++) {
    this->departure_coordinates[0] = latitude;
    this->departure_coordinates[1] = longitude;
    this->total_seats = 0;
    this->is_private = false;
    this->airfield_category = 'S';
    this->airport_name = new char[strlen("None")+1];
    strcpy(this->airport_name, "None");
    this->fuel_needed = 0;
    this->days_persons = 0;
    this->persons_bookedInNDays = nullptr;
    this->days_money = 0;
    this->money_earnedInNDays = nullptr;
    this->company_name = "None";
    this->crew_members_number = 0;
    this->crew_members_names = nullptr;
    for(int i=0; i <= this->total_seats; i++)
        seats_occupied[i]=0;
}

Flight::Flight(const Flight& flight_sec):flight_id(flight_sec.flight_id) {
    this->departure_coordinates[0] = flight_sec.departure_coordinates[0];
    this->departure_coordinates[1] = flight_sec.departure_coordinates[1];
    this->total_seats = flight_sec.total_seats;
    this->is_private = flight_sec.is_private;
    this->airfield_category = flight_sec.airfield_category;
    this->airport_name = new char[strlen(flight_sec.airport_name)+1];
    strcpy(this->airport_name, flight_sec.airport_name);
    this->fuel_needed = flight_sec.fuel_needed;
    this->days_persons = flight_sec.days_persons;
    this->persons_bookedInNDays = new int[flight_sec.days_persons];
    for(int i=0;i < days_persons ; i++)
        this->persons_bookedInNDays[i] = flight_sec.persons_bookedInNDays[i];
    if (this->days_persons == 0)
        this->persons_bookedInNDays = nullptr;
    this->days_money = flight_sec.days_money;
    this->money_earnedInNDays = new float[flight_sec.days_money];
    for(int i=0;i < days_money ; ++i)
        this->money_earnedInNDays[i] = flight_sec.money_earnedInNDays[i];
    if (this->days_money == 0)
        this->money_earnedInNDays = nullptr;
    this->company_name = flight_sec.company_name;
    this->crew_members_number = flight_sec.crew_members_number;
    this->crew_members_names = new string[flight_sec.crew_members_number];
    for(int i=0; i<crew_members_number; ++i)
        this->crew_members_names[i] = flight_sec.crew_members_names[i];
    for(int i=1; i<=total_seats; ++i)
        this->seats_occupied[i] = flight_sec.seats_occupied[i];
}

Flight::~Flight() {

    if(this->airport_name != nullptr)
        delete[] this->airport_name;

    if(this->persons_bookedInNDays != nullptr)
        delete[] persons_bookedInNDays;

    if(this->money_earnedInNDays!= nullptr)
        delete[] money_earnedInNDays;

    if(this->crew_members_names != nullptr)
        delete[] crew_members_names;
}
Flight& Flight::operator=(const Flight& flight_sec){
    if(this != &flight_sec){

        if(this->airport_name != nullptr)
            delete[] this->airport_name;

        if(this->persons_bookedInNDays != nullptr)
            delete[] persons_bookedInNDays;

        if(this->money_earnedInNDays!= nullptr)
            delete[] money_earnedInNDays;

        if(this->crew_members_names != nullptr)
            delete[] crew_members_names;

        this->departure_coordinates[0] = flight_sec.departure_coordinates[0];
        this->departure_coordinates[1] = flight_sec.departure_coordinates[1];
        this->total_seats = flight_sec.total_seats;
        this->is_private = flight_sec.is_private;
        this->airfield_category = flight_sec.airfield_category;
        this->airport_name = new char[strlen(flight_sec.airport_name)+1];
        strcpy(this->airport_name, flight_sec.airport_name);
        this->fuel_needed = flight_sec.fuel_needed;
        this->days_persons = flight_sec.days_persons;
        this->persons_bookedInNDays = new int[flight_sec.days_persons];
        for(int i=0;i < days_persons ; ++i)
            this->persons_bookedInNDays[i] = flight_sec.persons_bookedInNDays[i];
        if (this->days_persons == 0)
            this->persons_bookedInNDays = nullptr;
        this->days_money = flight_sec.days_money;
        this->money_earnedInNDays = new float[flight_sec.days_money];
        for(int i=0;i < days_money ; ++i)
            this->money_earnedInNDays[i] = flight_sec.money_earnedInNDays[i];
        if (this->days_money == 0)
            this->money_earnedInNDays = nullptr;
        this->company_name = flight_sec.company_name;
        this->crew_members_number = flight_sec.crew_members_number;
        this->crew_members_names = new string[flight_sec.crew_members_number];
        for(int i=0; i<crew_members_number; ++i)
            this->crew_members_names[i] = flight_sec.crew_members_names[i];
        for(int i=0; i<= flight_sec.total_seats; ++i)
            this->seats_occupied[i] = flight_sec.seats_occupied[i];

    }
    return *this;
}
ostream& operator<<(ostream& out, const Flight& flight){
    out<<"Flight coordinates are: "<<flight.departure_coordinates[0]<<" "<<flight.departure_coordinates[1]<<"\n";
    out<<"Total seats: "<<flight.total_seats<<"\n";
    out<<"Is a private flight: "<<flight.is_private<<"\n";
    out<<"Airfield category: "<<flight.airfield_category<<"\n";
    out<<"Airport name: "<<flight.airport_name<<"\n";
    out<<"Fuel needed: "<<flight.fuel_needed<<"\n";
    out<<"For the past "<<flight.days_persons<<" days this many people bought tickets: ";
    if(flight.persons_bookedInNDays != nullptr)
        out<<flight.persons_bookedInNDays[0];
    for(int i=1; i<flight.days_persons; i++)
        out<<", "<<flight.persons_bookedInNDays[i];
    out<<"\n";
    out<<"For the past "<<flight.days_money<< " days the amount of money earned is: ";
    if(flight.money_earnedInNDays != nullptr)
        out<<flight.money_earnedInNDays[0];
    for(int i=1; i<flight.days_money;i++)
        out<<", "<<flight.money_earnedInNDays[i];
    out<<"\nThe ID for this flight is:"<<flight.flight_id;
    out<<"\nCrew members are:";
    if(flight.crew_members_number != 0)
        out<<flight.crew_members_names[0];
    for(int i=1 ; i<flight.crew_members_number; i++)
        out<<", "<<flight.crew_members_names[i];
    out<<"\nCompany name: "<<flight.company_name<<"\n";
    out<<"These seats are not available: ";
    int pos=0;
    for(int i=1 ; i<= flight.total_seats; i++)
        if(flight.seats_occupied[i] == 1) {
            out<<i;
            pos=i+1;
            i=flight.total_seats+1;
        }
    for(int i=pos ; i<= flight.total_seats; i++)
        if(flight.seats_occupied[i] == 1) {
            out<<", "<<i;
        }
    out<<"\n";
    return out;
}
istream & operator>>(istream& in, Flight& flight){
    int thing;
    cout<<"Flight coordinates are: ";
    in>>flight.departure_coordinates[0]>>flight.departure_coordinates[1];
    cout<<"\nTotal number of seats: ";
    in>>flight.total_seats;
    cout<<"\nIs it a private flight? 1=True/0=False. ";
    in>>thing;
    if(thing==0)
        flight.is_private = false;
    else
        flight.is_private = true;
    cout<<"\nAirfield category is: ";
    in>>flight.airfield_category;
    cout<<"\nAirport name: ";
    char auxiliary[100];
    in>>auxiliary;
    if(flight.airport_name != nullptr)
        delete[] flight.airport_name;
    flight.airport_name = new char[strlen(auxiliary)+1];
    strcpy(flight.airport_name,auxiliary);
    cout<<"\nFuel needed: ";
    in>>flight.fuel_needed;
    cout<<"\nDays in which people booked: ";
    in>>flight.days_persons;
    cout<<"\nNumber of people for each day:";
    if(flight.persons_bookedInNDays != nullptr)
        delete[] flight.persons_bookedInNDays;
    flight.persons_bookedInNDays = new int[flight.days_persons];
    for(int i=0; i < flight.days_persons; i++)
        in>>flight.persons_bookedInNDays[i];
    cout<<"\nDays in which money were earned: ";
    in>>flight.days_money;
    cout<<"\nMoney earned each day: ";
    if(flight.money_earnedInNDays != nullptr)
        delete[] flight.money_earnedInNDays;
    flight.money_earnedInNDays = new float[flight.days_money];
    for(int i=0; i < flight.days_money; i++)
        in>>flight.money_earnedInNDays[i];
    cout<<"\nCrew members number:";
    in>>flight.crew_members_number;
    if(flight.crew_members_names != nullptr)
        delete[] flight.crew_members_names;
    cout<<"\nCrew:";
    flight.crew_members_names = new string[flight.crew_members_number];
    for(int i=0; i<flight.crew_members_number; ++i)
        in>>flight.crew_members_names[i];
    cout<<"Company name is:";
    in>>flight.company_name;
    cout<<"\nNumber of seats occupied: ";
    int seats_added,aux;
    in>>seats_added;
    cout<<"\nSeats: ";
    for (int i = 0; i <= flight.total_seats; ++i)
        flight.seats_occupied[i]=0;
    for(int i=0; i <seats_added; i++) {
        in >> aux;
        flight.seats_occupied[aux] = 1;
    }

    return in;
}
class Person{
private:
    string first_name;
    string last_name;
    int age;
    const int person_id;
public:
    static int id_count;
    void setFirst_name(string fname);
    string getFirst_name();
    void setLast_name(string lname);
    string getLast_name();
    void setAge(int iage);
    int getAge();
    int getPerson_id();
    string askForFullName();
    Person();
    Person(string fname, string lname, int iage);
    Person(int iage);
    ~Person();
    Person(const Person& person_sec);
    Person& operator=(const Person& person_sec);
    friend ostream& operator<<(ostream& out, const Person& person);
    friend istream& operator>>(istream& in, Person& person);
    const Person& operator++();
    Person operator++(int);
    Person operator+(const Person& person_sec);
    Person operator-(const Person& person_sec);
    bool operator <(const Person& person_sec);
    bool operator ==(const Person& person_sec);
    string& operator[](int i);

};
bool Person::operator<(const Person &person_sec) {
    if (this->age < person_sec.age)
        return true;
    return false;
}

string Person::askForFullName(){
    return (this->first_name + ' ' +this->last_name);
}

string& Person::operator[](int i) {
    if(i == 1)
        return this->first_name;
    else
        return this->last_name;
}

bool Person::operator==(const Person &person_sec) {
    if ((this->age == person_sec.age)&&(this->last_name == person_sec.last_name)&&(this->first_name == person_sec.first_name))
        return true;
    return false;
}

Person Person::operator+(const Person& person_sec){
    Person person;
    person = *this;
    person.age = this->age + person_sec.age;
    return person;
}

Person Person::operator-(const Person& person_sec){
    Person person;
    person = *this;
    person.age = this->age - person_sec.age;
    return person;
}

int Person::id_count = 0;

const Person& Person::operator++() {
    this->age++;
    return *this;
}
Person Person::operator++(int) {
    Person aux(*this);
    this->age++;
    return aux;
}
ostream& operator<<(ostream& out, const Person& person){
    out<<"\nFirst name:"<<person.first_name;
    out<<"\nLast name:"<<person.last_name;
    out<<"\nAge:"<<person.age;
    out<<"\nPerson ID:"<<person.person_id;
    return out;
}
istream& operator>>(istream& in, Person& person){
    cout<<"\nFirst name:";in>>person.first_name;
    cout<<"\nLast name:";in>>person.last_name;
    cout<<"\nAge:";in>>person.age;
    return in;
}

void Person::setFirst_name(string fname) {
    this->first_name = fname;
}

string Person::getFirst_name() {
    return this->first_name;
}

void Person::setLast_name(string lname) {
    this->last_name = lname;
}

string Person::getLast_name() {
    return this->last_name;
}

void Person::setAge(int iage) {
    this->age = iage;
}

int Person::getAge() {
    return this->age;
}

int Person::getPerson_id() {
    return this->person_id;
}

Person::Person():person_id(id_count++) {
    this->last_name = "None";
    this->first_name = "None";
    this->age = 0;
}

Person::Person(string fname, string lname, int iage):person_id(id_count++) {
    this->last_name = lname;
    this->first_name = fname;
    this->age = iage;
}
Person::Person(int iage):person_id(id_count++) {
    this->last_name = "None";
    this->first_name = "None";
    this->age = iage;
}

Person::~Person() = default;

Person::Person(const Person& person_sec):person_id(person_sec.person_id){
    this->last_name = person_sec.last_name;
    this->first_name = person_sec.first_name;
    this->age = person_sec.age;
}

Person& Person::operator=(const Person& person_sec){
    if(this != &person_sec){
        this->last_name = person_sec.last_name;
        this->first_name = person_sec.first_name;
        this->age = person_sec.age;
    }
    return *this;
}

class Ticket{
protected:
    int baggage_count;
    bool is_oneway;
    int seat;
    string client_Fname;
    string client_Lname;
    int flight_id;
    int products_number;
    string* food_ordered;
    const int ticket_id;
public:
    static int id_count;
    void setBaggage_count(int count);
    int getBaggage_count();
    void setSeat(int seat);
    int getSeat();
    void setClient_Fname(string fname);
    string getClient_Fname();
    void setClient_Lname(string lname);
    string getClient_Lname();
    void setFood_ordered(int number, string* food);
    string* getFood_ordered();
    void setFlight_id(int id);
    int getFlight_id();
    int getTicket_id();
    void addNewBaggage();
    void addProduct(string name);
    Ticket();
    Ticket(int count, bool oneway,int seat, string fname, string lname,int flight_id,int number,string* food);
    Ticket(int count, bool oneway,int seat, string fname, string lname);
    ~Ticket();
    Ticket(const Ticket& ticket_sec);
    Ticket& operator=(const Ticket& ticket_sec);
    friend istream& operator>>(istream& in,Ticket& ticket);
    friend ostream& operator<<(ostream& out, const Ticket& ticket);
    const Ticket& operator++();
    Ticket operator++(int);
    friend Ticket operator+(const Ticket& tic,int x);
    friend Ticket operator-(const Ticket& tic,int x);
    bool operator<(const Ticket& ticket);
    bool operator==(const Ticket& ticket);
    string& operator[](int i);
};
int Ticket::id_count=0;

string& Ticket::operator[](int i) {
    if(i > this->products_number){
        if(products_number !=  0){
            cout<<"Index out of range!  Returned client last name";
            return this->food_ordered[0];}
        else{
            return this->client_Lname;
        }
    }
    return this->food_ordered[i];
}

Ticket operator+(const Ticket& tic, int x) {
    Ticket sec(tic);
    sec.baggage_count += x;
    return sec;
}

Ticket operator-(const Ticket& tic, int x) {
    Ticket sec(tic);
    sec.baggage_count -= x;
    return sec;
}

bool Ticket::operator<(const Ticket &ticket) {
    if(this->baggage_count < ticket.baggage_count)
        return true;
    return false;
}

bool Ticket::operator==(const Ticket &ticket_sec) {
    int ok=1;
    for (int i = 0; i < this->products_number; ++i){
        if(this->food_ordered[i] !=  ticket_sec.food_ordered[i])
            ok=0;}

    if(ok)
        if((this->baggage_count ==  ticket_sec.baggage_count)
           &&(this->is_oneway == ticket_sec.is_oneway)
           &&(this->seat == ticket_sec.seat)
           &&(this->client_Fname == ticket_sec.client_Fname)
           &&(this->client_Lname == ticket_sec.client_Lname)
           &&(this->flight_id == ticket_sec.flight_id))
            return true;
    return false;
}

const Ticket& Ticket::operator++() {
    this->baggage_count++;
    return *this;
}

Ticket Ticket::operator++(int) {
    Ticket aux(*this);
    this->baggage_count++;
    return aux;
}

void Ticket::setBaggage_count(int count){
    this->baggage_count = count;
}

int Ticket::getBaggage_count() {
    return this->baggage_count;
}

void Ticket::setSeat(int seat) {
    this->seat = seat;
}

int Ticket::getSeat() {
    return this->seat;
}

void Ticket::setFlight_id(int id) {
    this->flight_id = id;
}

int Ticket::getFlight_id() {
    return this->flight_id;
}

int Ticket::getTicket_id() {
    return this->ticket_id;
}

void Ticket::setClient_Fname(string fname){
    this->client_Fname = fname;
}

string Ticket::getClient_Fname(){
    return this->client_Fname;
}

void Ticket::setClient_Lname(string lname){
    this->client_Lname = lname;
}

string Ticket::getClient_Lname(){
    return this->client_Lname;
}

void Ticket::setFood_ordered(int number, string* food){
    if(this->food_ordered != nullptr)
        delete[] food_ordered;
    this->products_number = number;
    this->food_ordered = new string[this->products_number+1];
    for(int i=0;  i<this->products_number; i++)
        this->food_ordered[i] = food[i];
}

string* Ticket::getFood_ordered(){
    return this->food_ordered;
}

void Ticket::addNewBaggage() {
    this->baggage_count++;
}
void Ticket::addProduct(string name){
    products_number++;
    string* aux;
    aux =  new string[products_number+1];
    for(int i=0;  i<this->products_number-1; i++)
        aux[i] = this->food_ordered[i];
    aux[this->products_number-1] = name;
    if(this->food_ordered != NULL)
        delete[] this->food_ordered;
    this->food_ordered =  new string[products_number+1];
    for(int i=0;  i<this->products_number; ++i)
        this->food_ordered[i] = aux[i];
    delete[] aux;
}

Ticket::Ticket():ticket_id(id_count++) {
    this->baggage_count=0;
    this->is_oneway = false;
    this->seat = 0;
    this->client_Fname = "None";
    this->client_Lname = "None";
    this->flight_id = 0;
    this->products_number = 0;
    this->food_ordered = nullptr;
}

Ticket::Ticket(int count, bool oneway,int seat, string fname, string lname):ticket_id(id_count++){
    this->baggage_count = count;
    this->is_oneway = oneway;
    this->seat = seat;
    this->client_Fname = fname;
    this->client_Lname = lname;
    this->flight_id = 0;
    this->products_number = 0;
    this->food_ordered = nullptr;
}

Ticket::Ticket(int count, bool oneway,int seat, string fname, string lname,int flight_id,int number,string* food):ticket_id(id_count++){
    this->baggage_count = count;
    this->is_oneway = oneway;
    this->seat = seat;
    this->client_Fname = fname;
    this->client_Lname = lname;
    this->flight_id = flight_id;
    this->products_number = number;
    this->food_ordered =  new string[this->products_number];
    for(int i=0;  i < this->products_number; i++)
        this->food_ordered[i] = food[i];
}

Ticket::~Ticket() {
    if(this->food_ordered != nullptr)
        delete[] this->food_ordered;
}

Ticket::Ticket(const Ticket &ticket_sec):ticket_id(ticket_sec.ticket_id) {
    this->baggage_count =  ticket_sec.baggage_count;
    this->is_oneway =  ticket_sec.is_oneway;
    this->seat =  ticket_sec.seat;
    this->client_Lname = ticket_sec.client_Lname;
    this->client_Fname = ticket_sec.client_Fname;
    this->flight_id = ticket_sec.flight_id;
    this->food_ordered = new string[ticket_sec.products_number+1];
    for (int i = 0; i < this->products_number; ++i)
        this->food_ordered[i] =  ticket_sec.food_ordered[i];
}

Ticket& Ticket::operator=(const Ticket &ticket_sec) {
    if (this != &ticket_sec) {
        if (this->food_ordered != nullptr)
            delete[] this->food_ordered;
        this->baggage_count = ticket_sec.baggage_count;
        this->is_oneway = ticket_sec.is_oneway;
        this->seat = ticket_sec.seat;
        this->client_Lname = ticket_sec.client_Lname;
        this->client_Fname = ticket_sec.client_Fname;
        this->flight_id = ticket_sec.flight_id;
        this->food_ordered = new string[ticket_sec.products_number + 1];
        for (int i = 0; i < this->products_number; ++i)
            this->food_ordered[i] = ticket_sec.food_ordered[i];
    }
    return *this;
}

ostream& operator<<(ostream& out, const Ticket& ticket){
    out<<"\nBaggage count: "<<ticket.baggage_count;
    out<<"\nIs oneway: "<<ticket.is_oneway;
    out<<"\nSeat: "<<ticket.seat;
    out<<"\nFirst name: "<<ticket.client_Fname;
    out<<"\nLast name: "<<ticket.client_Lname;
    out<<"\nFlight id: "<<ticket.flight_id;
    out<<"\nThe products ordered: ";
    if (ticket.food_ordered != nullptr)
        out<<ticket.food_ordered[0];
    for(int i=1; i<ticket.products_number; i++)
        out<<", "<<ticket.food_ordered[i];
    out<<"\nTicket ID:"<<ticket.ticket_id;
    return out;
}

istream& operator>>(istream& in, Ticket& ticket){
    int aux;
    cout<<"\nBaggage count: "; in>>ticket.baggage_count;
    cout<<"\nIs oneway (0/1): "; in>>aux;
    if (aux)
        ticket.is_oneway = true;
    else
        ticket.is_oneway = false;
    cout<<"\nFirst name: "; in>>ticket.client_Fname;
    cout<<"\nLast name: "; in>>ticket.client_Lname;
    cout<<"\nFlight ID: "; in>>ticket.flight_id;
    cout<<"\nProducts ordered: ";in>>ticket.products_number;
    if(ticket.food_ordered != nullptr)
        delete[] ticket.food_ordered;
    ticket.food_ordered = new string[ticket.products_number+1];
    cout<<"\nProducts: ";
    for(int i=0; i<ticket.products_number; i++)
        in>>ticket.food_ordered[i];
    return in;
}

class FirstClass : public Ticket{
private:
    float ticket_price;
    int shower_number;
    string section_stewardess;
public:
    void setTicketprice(float price);
    float getTicketprice() const;
    void setShowernumber(int number);
    int getShowernumber() const;
    void setSection_stewardess(string stewardess);
    string getSectionstewardess() const;
    ~FirstClass();
    FirstClass();
    FirstClass(int count, bool oneway,int seat, string fname,
               string lname,int flight_id,int number,string* food,float price, int shower_nmb, string stewardessname);
    FirstClass(const FirstClass& firstclass_sec);
    FirstClass& operator=(const FirstClass& firstclass_sec);
    friend ostream& operator<<(ostream& out, const FirstClass& firstclass);
    friend istream& operator>>(istream& in, FirstClass& firstclass);
};
FirstClass::~FirstClass() = default;
FirstClass::FirstClass():Ticket() {
    this->ticket_price = 0;
    this-> shower_number = 0;
    this->section_stewardess = "None";
}
FirstClass::FirstClass(int count, bool oneway,int seat, string fname, string lname,int flight_id,int number,
                       string* food,float price, int shower_nmb, string stewardessname):Ticket(count, oneway, seat, fname, lname, flight_id, number, food){
    this->ticket_price = price;
    this->shower_number = shower_nmb;
    this->section_stewardess = stewardessname;
}
FirstClass::FirstClass(const FirstClass &firstclass_sec):Ticket(firstclass_sec) {
    this->ticket_price = firstclass_sec.ticket_price;
    this->shower_number = firstclass_sec.shower_number;
    this->section_stewardess = firstclass_sec.section_stewardess;
}
FirstClass& FirstClass::operator=(const FirstClass &firstclass_sec) {
    if(this != &firstclass_sec){
        Ticket::operator=(firstclass_sec);
        this->ticket_price = firstclass_sec.ticket_price;
        this->shower_number = firstclass_sec.shower_number;
        this->section_stewardess = firstclass_sec.section_stewardess;
    }
    return *this;
}
ostream& operator<<(ostream& out, const FirstClass& firstclass){
    out<<(Ticket&)firstclass;
    out<<"\nTicket price: "<<firstclass.ticket_price;
    out<<"\nShower number: "<<firstclass.shower_number;
    out<<"\nStewardess name: "<<firstclass.section_stewardess;
    return out;
}
istream& operator>>(istream& in, FirstClass& firstclass){
    in>>(Ticket&)firstclass;
    cout<<"\nTicket price:";
    in>>firstclass.ticket_price;
    cout<<"\nShower number: ";
    in>>firstclass.shower_number;
    cout<<"\nStewardess name:";
    in>>firstclass.section_stewardess;
    return in;
}
void FirstClass::setTicketprice(float price) {
    this->ticket_price = price;
}
float FirstClass::getTicketprice() const {
    return this->ticket_price;
}
void FirstClass::setShowernumber(int number) {
    this->shower_number =  number;
}
int FirstClass::getShowernumber() const {
    return this->shower_number;
}
void FirstClass::setSection_stewardess(string stewardess) {
    this->section_stewardess =  stewardess;
}
string FirstClass::getSectionstewardess() const {
    return this->section_stewardess;
}
class EconomyClass : public Ticket{
private:
    float ticket_price;
    int freedrinks_included;
    string free_meal;
public:
    void setTicketprice(float price);
    float getTicketprice() const;
    void setFreedrinksincluded(int drinks);
    int getFreedrinksincluded() const;
    void setFreemeal(string stewardess);
    string getFreemeal() const;
    ~EconomyClass();
    EconomyClass();
    EconomyClass(int count, bool oneway,int seat, string fname,
                 string lname,int flight_id,int number,string* food,float price, int freedrinks, string meal);
    EconomyClass(const EconomyClass& economyclass_sec);
    EconomyClass& operator=(const EconomyClass& economyclass_sec);
    friend ostream& operator<<(ostream& out, const EconomyClass& economyclass);
    friend istream& operator>>(istream& in, EconomyClass& economyclass);
};
EconomyClass::~EconomyClass() = default;
EconomyClass::EconomyClass():Ticket() {
    this->ticket_price = 0;
    this-> freedrinks_included = 0;
    this->free_meal = "None";
}
EconomyClass::EconomyClass(int count, bool oneway,int seat, string fname, string lname,int flight_id,int number,
                           string* food,float price, int freedrinks, string meal):Ticket(count, oneway, seat, fname, lname, flight_id, number, food){
    this->ticket_price = price;
    this->freedrinks_included = freedrinks;
    this->free_meal = meal;
}
EconomyClass::EconomyClass(const EconomyClass &economyclass_sec):Ticket(economyclass_sec) {
    this->ticket_price = economyclass_sec.ticket_price;
    this->freedrinks_included = economyclass_sec.freedrinks_included;
    this->free_meal = economyclass_sec.free_meal;
}
EconomyClass& EconomyClass::operator=(const EconomyClass &economyclass_sec) {
    if(this != &economyclass_sec){
        Ticket::operator=(economyclass_sec);
        this->ticket_price = economyclass_sec.ticket_price;
        this->freedrinks_included = economyclass_sec.freedrinks_included;
        this->free_meal = economyclass_sec.free_meal;
    }
    return *this;
}
ostream& operator<<(ostream& out, const EconomyClass& economyclass){
    out<<(Ticket&) economyclass;
    out<<"\nTicket price: "<<economyclass.ticket_price;
    out<<"\nFreedrinks number: "<<economyclass.freedrinks_included;
    out<<"\nFree meal: "<<economyclass.free_meal;
    return out;
}
istream& operator>>(istream& in, EconomyClass& economyclass){
    in>>(Ticket&) economyclass;
    cout<<"\nTicket price:";
    in>>economyclass.ticket_price;
    cout<<"\nFreedrinks number: ";
    in>>economyclass.freedrinks_included;
    cout<<"\nFree meal:";
    in>>economyclass.free_meal;
    return in;
}
void EconomyClass::setTicketprice(float price) {
    this->ticket_price = price;
}
float EconomyClass::getTicketprice() const {
    return this->ticket_price;
}
void EconomyClass::setFreedrinksincluded(int drinks){
    this->freedrinks_included =  drinks;
}
int EconomyClass::getFreedrinksincluded() const {
    return this->freedrinks_included;
}
void EconomyClass::setFreemeal(string meal) {
    this->free_meal =  meal;
}
string EconomyClass::getFreemeal() const {
    return this->free_meal;
}



class Food_list{
private:
    string name;
    float price;
    int quantity;
    int number_of_persons;
    int calories_per_serving;
    const int identification_code;
public:
    static int count;
    void setName(string name);
    string getName();
    void setPrice(float price);
    float getPrice();
    void setQuantity(int QT);
    int getQuantity();
    void setNumber_of_persons(int number);
    int getNumber_of_persons();
    void setCalories_per_serving(int calories);
    int getCalories_per_serving();
    int getIdentification_code();
    int totalCalories();
    Food_list();
    Food_list(string name, float price, int QT, int number, int calories);
    Food_list(string name);
    Food_list(const Food_list& food);
    ~Food_list();
    Food_list& operator=(const Food_list& food);
    friend istream& operator>>(istream& in,Food_list& food);
    friend ostream& operator<<(ostream& outt, const Food_list food);
    const Food_list& operator++();
    Food_list operator++(int);
    Food_list operator+(const Food_list& food);
    Food_list operator-(const Food_list& food);
    bool operator<(const Food_list& food);
    bool operator==(const Food_list& food);
    int& operator[](int i);
    explicit operator int();
};
int Food_list::count = 0;

Food_list::operator int() {
    return int(this->price)+1;
}

int Food_list::totalCalories() {
    return (this->calories_per_serving*this->number_of_persons);
}

int& Food_list::operator[](int i) {
    if (i == 1)
        return quantity;
    if (i == 2)
        return number_of_persons;
    else
        return calories_per_serving;
}

int Food_list::getIdentification_code() {
    return this->identification_code;
}

bool Food_list::operator<(const Food_list &food) {
    if((this->quantity<food.quantity)&&(this->number_of_persons<food.number_of_persons)&&(this->price<food.price))
        return true;
    return false;
}

bool Food_list::operator==(const Food_list &food) {
    if((this->quantity==food.quantity)&&(this->number_of_persons==food.number_of_persons)&&(this->price==food.price)&&(this->name==food.name)&&(this->calories_per_serving==food.calories_per_serving))
        return true;
    return false;
}

Food_list Food_list::operator+(const Food_list &food) {
    Food_list sec;
    sec.name = this->name +", "+ food.name;
    sec.quantity = this->quantity + food.quantity;
    sec.number_of_persons = this->number_of_persons + food.number_of_persons;
    sec.calories_per_serving = this->calories_per_serving + food.calories_per_serving;
    sec.price = this->price + food.price;
    return sec;
}

Food_list Food_list::operator-(const Food_list &food) {
    Food_list sec;
    sec.quantity = this->quantity - food.quantity;
    sec.number_of_persons = this->number_of_persons - food.number_of_persons;
    sec.calories_per_serving = this->calories_per_serving - food.calories_per_serving;
    sec.price = this->price - food.price;
    return sec;
}

const Food_list& Food_list::operator++() {
    this->price += 5;
    this->quantity += 100;
    this->calories_per_serving += 100;
    return *this;
}

Food_list Food_list::operator++(int) {
    Food_list aux(*this);
    this->price += 5;
    this->quantity += 100;
    this->calories_per_serving += 100;
    return aux;
}

void Food_list::setName(string name) {
    this->name =  name;
}

string Food_list::getName() {
    return this->name;
}

void Food_list::setPrice(float price) {
    this->price = price;
}

float Food_list::getPrice() {
    return this->price;
}

void Food_list::setQuantity(int QT) {
    this->quantity =  QT;
}

int Food_list::getQuantity() {
    return this->quantity;
}

void Food_list::setNumber_of_persons(int number) {
    this->number_of_persons =  number;
}

int Food_list::getNumber_of_persons() {
    return this->number_of_persons;
}

void Food_list::setCalories_per_serving(int calories) {
    this->calories_per_serving =  calories;
}

int Food_list::getCalories_per_serving() {
    return this->calories_per_serving;
}

Food_list::Food_list():identification_code(count++) {
    this->name = "None";
    this->price = 0;
    this->quantity = 0;
    this->number_of_persons = 0;
    this->calories_per_serving = 0;
}

Food_list::Food_list(string name, float price, int QT, int number, int calories):identification_code(count++){
    this->name = name;
    this->price = price;
    this->quantity = QT;
    this->number_of_persons = number;
    this->calories_per_serving = calories;
}

Food_list::Food_list(string name):identification_code(count++){
    this->name = name;
    this->price = 0;
    this->quantity = 0;
    this->number_of_persons = 0;
    this->calories_per_serving = 0;
}

Food_list::~Food_list() = default;

Food_list::Food_list(const Food_list& food):identification_code(food.identification_code) {
    this->name = food.name;
    this->price = food.price;
    this->quantity = food.quantity;
    this->number_of_persons = food.number_of_persons;
    this->calories_per_serving = food.calories_per_serving;
}

Food_list&  Food_list::operator=(const Food_list& food){
    if(this != &food){
        this->name = food.name;
        this->price = food.price;
        this->quantity = food.quantity;
        this->number_of_persons = food.number_of_persons;
        this->calories_per_serving = food.calories_per_serving;
    }

    return *this;
}

istream& operator>>(istream& in,Food_list& food){
    cout<<"\nFood name is: "; getline(in, food.name);
    cout<<"\nPrice: "; in>>food.price;
    cout<<"\nQuantity: "; in>>food.quantity;
    cout<<"\nNumber of persons: "; in>>food.number_of_persons;
    cout<<"\nCalories per serving: ";in>>food.calories_per_serving;
    return in;
}

ostream &operator<<(ostream &out, const Food_list food){
    out << "\nFood name is: " << food.name;
    out << "\nPrice: " << food.price;
    out << "\nQuantity: " << food.quantity;
    out << "\nNumber of persons: " << food.number_of_persons;
    out << "\nCalories per serving: " << food.calories_per_serving;
    return out;
}
class Drink{
protected:
    int quantity;
    int price;
    string drink_name;
public:
    virtual ~Drink();
    Drink();
    Drink(int qt, int prc, string name);
    virtual void setQuantity(int qt);
    virtual void setPrice(int prc);
    virtual void setName(string name);
    virtual void openbottle() = 0;
};
Drink::~Drink() = default;
Drink::Drink() {
    this->quantity = 0;
    this->price = 0;
    this->drink_name = "None";
}
Drink::Drink(int qt,int prc, string name) {
    this->quantity = qt;
    this->price =  prc;
    this->drink_name = name;
}
void Drink::setQuantity(int qt) {
    this->quantity = qt;
}
void Drink::setName(string name) {
    this->drink_name = name;
}
void Drink::setPrice(int prc) {
    this->price =  prc;
}
class NonAlcoholicDrink : public Drink{
private:
    bool is_sparkling;
public:
    void openbottle();
    void setSparkling(bool sprk);
    ~NonAlcoholicDrink();
    NonAlcoholicDrink();
    NonAlcoholicDrink(int qt, int prc, string name, bool sprk);
    NonAlcoholicDrink(const NonAlcoholicDrink& nonalch_sec);
    NonAlcoholicDrink& operator=(const NonAlcoholicDrink& nonalch_sec);
    friend ostream& operator<<(ostream& out, const NonAlcoholicDrink& nonalch_sec);
    friend istream& operator>>(istream& in, NonAlcoholicDrink& nonalch_sec);
};
void NonAlcoholicDrink::setSparkling(bool sprk) {
    this->is_sparkling = sprk;
}
void NonAlcoholicDrink::openbottle() {
    cout<<"You do not need a special tool";
}
NonAlcoholicDrink::~NonAlcoholicDrink()=default;
NonAlcoholicDrink::NonAlcoholicDrink():Drink(){
    this->is_sparkling = false;
}
NonAlcoholicDrink::NonAlcoholicDrink(int qt, int prc, string name, bool sprk):Drink(qt,prc,name) {
    this->is_sparkling = sprk;
}
NonAlcoholicDrink::NonAlcoholicDrink(const NonAlcoholicDrink &nonalch_sec) {
    this->price = nonalch_sec.price;
    this->quantity =  nonalch_sec.quantity;
    this->drink_name =  nonalch_sec.drink_name;
    this->is_sparkling = nonalch_sec.is_sparkling;
}
NonAlcoholicDrink& NonAlcoholicDrink::operator=(const NonAlcoholicDrink &nonalch_sec) {
    if(this != &nonalch_sec){
        this->price = nonalch_sec.price;
        this->quantity =  nonalch_sec.quantity;
        this->drink_name =  nonalch_sec.drink_name;
        this->is_sparkling = nonalch_sec.is_sparkling;
    }
    return *this;
}
ostream& operator<<(ostream& out, const NonAlcoholicDrink& nonalch_sec){
    out<<"\nName:"<<nonalch_sec.drink_name;
    out<<"\nPrice: "<<nonalch_sec.price;
    out<<"\nQuantity: "<<nonalch_sec.quantity;
    out<<"\nIs Sparkling: "<<nonalch_sec.is_sparkling;
    return out;
}
istream& operator>>(istream& in, NonAlcoholicDrink& nonalch_sec){
    cout<<"\nName: ";
    in>>nonalch_sec.drink_name;
    cout<<"\nPrice: ";
    in>>nonalch_sec.price;
    cout<<"\nQuantity: ";
    in>>nonalch_sec.quantity;
    cout<<"\nIs Sparkling: (0/1)";
    in>>nonalch_sec.is_sparkling;
    return in;
}
class AlcoholicDrink : public Drink{
private:
    int alcohol_concentration;
    NonAlcoholicDrink workswith;
public:
    void openbottle() override;
    ~AlcoholicDrink() override;
    AlcoholicDrink();
    AlcoholicDrink(int qt, int prc,string name, int alcprocent, NonAlcoholicDrink nonalch);
    AlcoholicDrink(const AlcoholicDrink& alcoholic_sec);
    AlcoholicDrink& operator=(const AlcoholicDrink& alcoholic_sec);
    friend ostream& operator<<(ostream& out, const AlcoholicDrink& alcoholic_sec);
    friend istream& operator>>(istream& in, AlcoholicDrink& alcoholic_sec);
};
void AlcoholicDrink::openbottle() {
    cout<<"You need a special tool, it can be a beer opener or a corkscrew";
}
AlcoholicDrink::~AlcoholicDrink()=default;
AlcoholicDrink::AlcoholicDrink():Drink(){
    this->alcohol_concentration = 0;
}
AlcoholicDrink::AlcoholicDrink(int qt, int prc,string name, int alcprocent, NonAlcoholicDrink nonalch):Drink(qt,prc,name) {
    this->alcohol_concentration = alcprocent;
    this->workswith = nonalch;
}
AlcoholicDrink::AlcoholicDrink(const AlcoholicDrink &alcoholic_sec) {
    this->price = alcoholic_sec.price;
    this->quantity =  alcoholic_sec.quantity;
    this->drink_name =  alcoholic_sec.drink_name;
    this->alcohol_concentration = alcoholic_sec.alcohol_concentration;
    this->workswith = alcoholic_sec.workswith;
}
AlcoholicDrink& AlcoholicDrink::operator=(const AlcoholicDrink &alcoholic_sec) {
    if(this != &alcoholic_sec){
        this->price = alcoholic_sec.price;
        this->quantity =  alcoholic_sec.quantity;
        this->drink_name = alcoholic_sec.drink_name;
        this->alcohol_concentration = alcoholic_sec.alcohol_concentration;
        this->workswith = alcoholic_sec.workswith;
    }
    return *this;
}
ostream& operator<<(ostream& out, const AlcoholicDrink& alcoholic_sec){
    out<<"\nName:" <<alcoholic_sec.drink_name;
    out<<"\nPrice: "<<alcoholic_sec.price;
    out<<"\nQuantity: "<<alcoholic_sec.quantity;
    out<<"\nAlcohol concentration: "<<alcoholic_sec.alcohol_concentration;
    out<<"\nWorks well with the nonalcoholic drinks with the properties below:\n"<<alcoholic_sec.workswith;
    return out;
}
istream& operator>>(istream& in, AlcoholicDrink& alcoholic_sec){
    cout<<"\nName: ";
    in>>alcoholic_sec.drink_name;
    cout<<"\nPrice: ";
    in>>alcoholic_sec.price;
    cout<<"\nQuantity: ";
    in>>alcoholic_sec.quantity;
    cout<<"\nAlcohol concentration: ";
    in>>alcoholic_sec.alcohol_concentration;
    cout<<"\nWorks well with: ";
    in>>alcoholic_sec.workswith;
    return in;
}
class Document{
public:
    virtual ~Document();
    virtual void askForId() = 0;
    virtual void askForSeries() = 0;
};
Document::~Document()= default;

class Passport : public Document{
private:
    int person_id;
    string document_series;
    int document_number;
public:
    ~Passport();
    Passport();
    Passport(int id, string series, int number);
    Passport(const Passport& passport_sec);
    Passport& operator=(const Passport& passport_sec);
    friend ostream& operator<<(ostream& out,const Passport& passport_sec);
    friend istream& operator>>(istream& in,Passport& passport_sec);
    void askForId();
    void askForSeries();
    void setPerson_id(int id);
};

Passport::~Passport() =  default;
Passport::Passport() {
    this->person_id = 0;
    this->document_series = "None";
    this->document_number = 0;
}
Passport::Passport(int id, string series, int number) {
    this->person_id = id;
    this->document_number = number;
    this->document_series = series;
}
Passport::Passport(const Passport &passport_sec) {
    if(this != &passport_sec){
        this->person_id = passport_sec.person_id;
        this->document_series = passport_sec.document_series;
        this->document_number = passport_sec.document_number;
    }
}
Passport& Passport::operator=(const Passport &passport_sec) {
    if(this != &passport_sec){
        this->person_id = passport_sec.person_id;
        this->document_series = passport_sec.document_series;
        this->document_number = passport_sec.document_number;
    }
    return *this;
}
void Passport::setPerson_id(int id){
    this->person_id = id;
}
ostream& operator<<(ostream& out,const Passport& passport_sec){
    out<<"\nThe person id is:"<<passport_sec.person_id;
    out<<"\nThe document series is:"<<passport_sec.document_series;
    out<<"\nThe document number is:"<<passport_sec.document_number;
    return out;
}
istream& operator>>(istream& in,Passport& passport_sec){
    cout<<"\nThe person id is:";
    in>>passport_sec.person_id;
    cout<<"\nThe document series is:";
    in>>passport_sec.document_series;
    cout<<"\nThe document number is:";
    in>>passport_sec.document_number;
    return in;
}
void Passport::askForId() {
    cout<<"\nThe id is: "<<this->person_id;
}
void Passport::askForSeries() {
    cout<<"\nThe series is: " << this->document_series;
    cout<<"\nThe number is: " << this->document_number;

}

class IdentityCard : public Document{
private:
    int person_id;
    string document_series;
    int document_number;
public:
    ~IdentityCard();
    IdentityCard();
    IdentityCard(int id, string series, int number);
    IdentityCard(const IdentityCard& card_sec);
    IdentityCard& operator=(const IdentityCard& card_sec);
    friend ostream& operator<<(ostream& out,const IdentityCard& card_sec);
    friend istream& operator>>(istream& in,IdentityCard& card_sec);
    void askForId();
    void askForSeries();
    void setPerson_id(int id);
};
void IdentityCard::setPerson_id(int id){
    this->person_id =  id;
}
IdentityCard::~IdentityCard() =  default;
IdentityCard::IdentityCard() {
    this->person_id = 0;
    this->document_series = "None";
    this->document_number = 0;
}
IdentityCard::IdentityCard(int id, string series, int number) {
    this->person_id = id;
    this->document_number = number;
    this->document_series = series;
}
IdentityCard::IdentityCard(const IdentityCard &card_sec) {
    if(this != &card_sec){
        this->person_id = card_sec.person_id;
        this->document_series = card_sec.document_series;
        this->document_number = card_sec.document_number;
    }
}
IdentityCard& IdentityCard::operator=(const IdentityCard &card_sec) {
    if(this != &card_sec){
        this->person_id = card_sec.person_id;
        this->document_series = card_sec.document_series;
        this->document_number = card_sec.document_number;
    }
    return *this;
}
ostream& operator<<(ostream& out,const IdentityCard& card_sec){
    out<<"\nThe person id is:"<<card_sec.person_id;
    out<<"\nThe document series is:"<<card_sec.document_series;
    out<<"\nThe document number is:"<<card_sec.document_number;
    return out;
}
istream& operator>>(istream& in,IdentityCard& card_sec){
    cout<<"\nThe person id is:";
    in>>card_sec.person_id;
    cout<<"\nThe document series is:";
    in>>card_sec.document_series;
    cout<<"\nThe document number is:";
    in>>card_sec.document_number;
    return in;
}
void IdentityCard::askForId() {
    cout<<"\nThe id is: "<<this->person_id;
}
void IdentityCard::askForSeries() {
    cout<<"\nThe series is: " << this->document_series;
    cout<<"\nThe number is: " << this->document_number;

}










int main() {
    ifstream f("date.txt");
    ofstream g("afisare.txt");
    list<Flight> flights;
    map<int,Person> persons;
    vector<Food_list> food;
    vector<AlcoholicDrink>aldrink;
    vector<NonAlcoholicDrink>nonaldrink;
    vector<FirstClass> fclasstickets;
    int number_of_firstclass_tickets;
    vector<EconomyClass> eclasstickets;
    int number_of_economyclass_tickets;
    int number_of_preset_flights;
    int number_of_preset_persons;
    int number_of_meals;
    f>>number_of_preset_flights;
    for(int i = 0; i < number_of_preset_flights ; ++i){
        Flight aux;
        f>>aux;
        flights.push_back(aux);
    }
    f>>number_of_preset_persons;
    for(int i = 0;i < number_of_preset_persons; ++i){
        string fname;
        string lname;
        int age;
        f>>fname;
        f>>lname;
        f>>age;
        Person aux(fname,lname,age);
        persons.insert(pair<int,Person>(aux.getPerson_id(),aux));
    }
    f>>number_of_meals;
    for(int i = 0;i < number_of_meals; ++i){
        string name;
        float price;
        int quantity;
        int number;
        int calories;
        f>>name;
        f>>price;
        f>>quantity;
        f>>number;
        f>>calories;
        Food_list aux(name,price,quantity,number,calories);
        food.push_back(aux);
    }
    int number_of_alcdrinks;
    int number_of_nonalchdrinks;
    f>>number_of_alcdrinks;
    for(int i = 0; i < number_of_alcdrinks; i++){
        AlcoholicDrink aux;
        f>>aux;
        aldrink.push_back(aux);
    }
    f>>number_of_nonalchdrinks;
    for(int i = 0; i < number_of_nonalchdrinks; i++){
        NonAlcoholicDrink aux;
        f>>aux;
        nonaldrink.push_back(aux);
    }
    cout<<nonaldrink[0];
    cout<<nonaldrink[1];
    bool personselected = false;
    Person person_operating;
    int option1;
    string delimitare = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    while(personselected == false){
        system("CLS");
        cout<<endl;
        cout<<delimitare<<endl<<endl;
        cout<<"Press one of the following keys to continue..."<<endl;
        cout<<"1.Select one of the preset clients.\n";
        cout<<"2.Continue as a guest.\n";
        cout<<endl;
        cout<<delimitare<<endl<<endl;
        cin>>option1;
        switch(option1){
            case 1:{
                system("CLS");
                int persnumb;
                cout<<delimitare<<endl<<endl;
                cout<<"Select yourself from the persons below by typing the number or type -1 to go back\n\n";
                for(int i = 0; i < number_of_preset_persons; ++i){
                    cout<<i;
                    cout<<persons[i]<<endl<<endl;
                }
                cout<<endl;
                cout<<delimitare<<endl<<endl;
                cin>>persnumb;
                if(persnumb == -1){
                    break;
                }
                else if(persnumb < number_of_preset_persons){
                    person_operating = persons[persnumb];
                    personselected =  true;
                    break;
                }
                else break;
            }
            case 2:{
                cin>>person_operating;
                personselected = true;
                break;
            }
            default:{
                break;
            }
        }

    }
    bool document_selected = false;
    Passport passport;
    IdentityCard id;
    while(document_selected == false){
        system("CLS");
        cout<<endl;
        cout<<delimitare<<endl<<endl;
        cout<<"Press one of the following keys to continue..."<<endl;
        cout<<"1.To add a passport.\n";
        cout<<"2.To add an id.\n";
        cout<<endl;
        cout<<delimitare<<endl<<endl;
        cin>>option1;

        switch(option1){
            case 1:{
                cout<<endl<<endl;
                cin>>passport;
                passport.setPerson_id(person_operating.getPerson_id());
                document_selected = true;
                break;
            }
            case 2:{
                cout<<endl<<endl;
                cin>>id;
                id.setPerson_id(person_operating.getPerson_id());
                document_selected = true;
                break;
            }
            default:{
                break;
            }
        }
    }
    int option2;
    bool exit =  false;
    while(exit == false){
        system("CLS");
        cout<<endl;
        cout<<delimitare<<endl<<endl;
        cout<<"Press one of the following keys to continue..."<<endl;
        cout<<"1.To display all the available flights.\n";
        cout<<"2.Display your full info.\n";
        cout<<"3.Book a EconomyClass ticket.\n";
        cout<<"4.Book a Firstclass ticket.\n";
        cout<<"5.Display menu.\n";
        cout<<"6.Display and save booked EconomyClass tickets.\n";
        cout<<"7.Display and save booked FirstClass tickets.\n";
        cout<<"8.Any other number to exit.\n";
        cout<<endl;
        cout<<delimitare<<endl<<endl;
        cin>>option2;
        switch(option2){
            case 1:{
                system("CLS");
                list <Flight> :: iterator it;
                for(it = flights.begin(); it != flights.end(); ++it)
                    cout<< *it<<endl;
                system("pause");
                break;
            }
            case 2:{
                system("CLS");
                cout<<"Your personal information:\n";
                cout<<person_operating<<endl<<endl;
                if(option1 == 1){
                    cout<<"Your passport:";
                    cout<<passport<<endl<<endl;
                }
                else{
                    cout<<"Your id:";
                    cout<<id<<endl<<endl;
                }
                system("pause");
                break;
            }
            case 3:{
                EconomyClass aux;
                system("CLS");
                int flight;
                int seat;
                cout<<"Select a flight from the ones listed bellow by typing the flight id.\n"<<endl;
                list <Flight> :: iterator it;
                for(it = flights.begin(); it != flights.end(); ++it)
                    cout<< *it<<endl;
                cin>>flight;
                it = flights.begin();
                while(flight>0){
                    it++;
                    flight--;
                }
                seat = it->book_seat();
                if(seat == -1)
                    break;
                cin>>aux;
                aux.setSeat(seat);
                eclasstickets.push_back(aux);
                number_of_economyclass_tickets++;
                break;
            }
            case 4:{
                FirstClass aux;
                system("CLS");
                int flight;
                int seat;
                cout<<"Select a flight from the ones listed bellow by typing the flight id.\n"<<endl;
                list <Flight> :: iterator it;
                for(it = flights.begin(); it != flights.end(); ++it)
                    cout<< *it<<endl;
                cin>>flight;
                it = flights.begin();
                while(flight>0){
                    it++;
                    flight--;
                }
                seat = it->book_seat();
                if(seat == -1)
                    break;
                cin>>aux;
                aux.setSeat(seat);
                fclasstickets.push_back(aux);
                number_of_firstclass_tickets++;
                break;
            }
            case 5:{
                system("CLS");
                cout<<delimitare<<endl<<endl;
                cout<<"Meals:"<<endl<<endl;
                for(int i = 0;i < number_of_meals; ++i){
                    cout<<food[i]<<endl;
                }
                cout<<delimitare<<endl<<endl;
                cout<<"Alcoholic drinks:"<<endl<<endl;
                for(int i = 0;i < number_of_alcdrinks; ++i){
                    cout<<aldrink[i]<<endl;
                }
                cout<<delimitare<<endl<<endl;
                cout<<"Non alcoholic drinks:"<<endl<<endl;
                for(int i = 0;i < number_of_nonalchdrinks; ++i){
                    cout<<nonaldrink[i]<<endl;
                }
                system("pause");
                cout<<delimitare<<endl<<endl;
            }
            case 6:{
                system("CLS");
                g<<endl<<endl;
                cout<<delimitare<<endl<<endl;
                g<<delimitare<<endl<<endl;
                for(int i = 0; i < number_of_economyclass_tickets;i++){
                    cout<<eclasstickets[i]<<endl;
                    g<<eclasstickets[i]<<endl;
                }
                cout<<delimitare<<endl<<endl;
                g<<delimitare<<endl<<endl;
                system("pause");
                break;
            }
            case 7:{
                system("CLS");
                g<<endl<<endl;
                cout<<delimitare<<endl<<endl;
                g<<delimitare<<endl<<endl;
                for(int i = 0; i < number_of_firstclass_tickets;i++){
                    cout<<fclasstickets[i]<<endl;
                    g<<fclasstickets[i]<<endl;
                }
                cout<<delimitare<<endl<<endl;
                g<<delimitare<<endl<<endl;
                system("pause");
                break;
            }
            default:{
                system("CLS");
                exit = true;
                break;
            }
        }


    }








    /*teste Flight*/
    /*int* p;
    p = new int[2];
    p[0]=1;
    p[1]=2;

    char *cc;
    cc= new char[2];
    cc[0]='a';
    cc[1]='b';
    cc[2]=0;

    float* c;
    c = new float[2];
    c[0]=1;
    c[1]=2;


    string* l;
    l = new string[2];
    l[0] = "nicusor";
    l[1] = "nicusor2";

    int r[3];
    r[1]=2;
    r[2]=3;
    r[3]=6;
    int ll[3];
    ll[1]=2;
    ll[2]=3;
    ll[3]=6;

    Flight k(1,1,20,true,'A',cc,200,2,p,2,c,"asds",2,l,3,ll);
    cout<<k;
    Flight flight;
    Flight a(1,1);
    cout<<a<<" zbor cu lat si long"<<endl;
    flight.setDeparture_coordinates(1,1);
    cout<<flight.getDeparture_coordinates()[0]<<flight.getDeparture_coordinates()[1]<<" coordonate zbor"<<endl;
    flight.setTotal_seats(10);
    cout<<flight.getTotal_seats()<<" locuri total"<<endl;
    flight.setIs_private(true);
    cout<<flight.getIs_private()<<" private"<<endl;
    flight.setAirfield_category('A');
    cout<<flight.getAirfield_category()<<" categorie"<<endl;
    flight.setAirport_name(cc);
    cout<<flight.getAirport_name()<<" nume"<<endl;
    flight.setFuel_needed(10.2);
    cout<<flight.getFuel_needed()<<" fuel "<<endl;
    flight.setPersons_bookedInNDays(2,p);
    cout<<flight.getPersons_bookedInNDays()<<" persoane cazate pe zile"<<endl;
    flight.setMoney_earnedInNDays(2, c);
    cout<<flight.getMoney_earnedInNDays()<<"bani castigati pe zile"<<endl;
    cout<<flight.getFlight_id()<<" id zbor"<<endl;
    flight.setCompany_name("");
    cout<<flight.getCompany_name()<<" nume comp"<<endl;
    flight.setCrew_members_names(2, l);
    cout<<flight.getCrew_members_names()<<" nume echipa"<<endl;
    flight.setSeats_occupied(2, r);
    cout<<flight.getSeats_occupied();
    Flight b(flight),m;
    m=b;
    cout<<m;
    cin>>flight;
    flight.book_seat();
    flight++;
    cout<<flight+m;
    cout<<flight-m;
    m=b;
    if (m==b) {
        cout << "da";
    }
    else
        cout<<"NU";
    if (m<b) {
        cout << "da";
    }
    else
        cout<<"NU";
    Flight ads;
    cout<<int(ads);
    cout<<ads[2];

    Person person;
    Person person2("Micu","Zasa",12);
    cout<<person2;
    Person person3(2);
    cout<<person3;
    person.setFirst_name("abdrei");
    cout<<person.getFirst_name();
    person.setLast_name("avrea");
    cout<<person.getLast_name();
    person.setAge(22);
    cout<<person.getAge();
    cout<<person.getPerson_id();
    cout<<person.askForFullName();
    Person sec(person),la;
    sec=person;
    cout<<sec;
    cin>>la;
    la++;
    cout<<la+sec;
    cout<<la-sec;
    if (sec==person) {
        cout << "da";
    }
    else
        cout<<"NU";
    if (sec<la) {
        cout << "da";
    }
    else
        cout<<"NU";
    cout<<person[1];

    /*Ticket test*/
    /*
    string* fd2;
    fd2= new string[1];
    fd2[0]="12312312a1";


    Ticket tic22(20,1,3,"Andrei","Rosu");
    Ticket tic33(20,1,3,"Andrei","Rosu",2,1,fd2);
    cout<<tic33;
    cout<<tic22;
    Ticket tic,tic2;
    tic.setBaggage_count(2);
    cout<<tic.getBaggage_count();
    tic.setSeat(2);
    cout<<tic.getSeat();
    tic.setClient_Fname("adasdas");
    cout<<tic.getClient_Fname();
    tic.setClient_Lname("212312");
    cout<<tic.getClient_Lname();
    string* fd;
    fd= new string[2];
    fd[0]="dasdas1";
    fd[1]="asdas";
    tic.setFood_ordered(2, fd);
    cout<<tic.getFood_ordered();
    tic.setFlight_id(2);
    cout<<tic.getFlight_id();
    cout<<tic.getTicket_id();
    tic.addNewBaggage();
    tic.addProduct("cdasdasdas");
    cout<<tic;
    Ticket tic3(tic);
    tic2=tic;
    cout<<tic2;
    tic++;
    cout<<++tic;
    tic2=tic;
    tic2=tic2+2;
    tic2=tic2-10;
    if (tic == tic2){
        cout<<"\nDa";
    }
    if(tic<tic2){
        cout<<"NU";
    }
    cout<<tic[1];
    cin>>tic;

    /*Food_list test*/
    /*Food_list food4("paine",21,212,1,232);
    cout<<food4;
    Food_list food5("paine2");
    cout<<food5;
    Food_list food;
    food.setName("clvasda");
    cout<<food.getName()<<endl;
    food.setPrice(2.12);
    cout<<food.getPrice()<<endl;
    food.setQuantity(2);
    cout<<food.getQuantity()<<endl;
    food.setNumber_of_persons(21);
    cout<<food.getNumber_of_persons()<<endl;
    food.setCalories_per_serving(222);
    cout<<food.getCalories_per_serving()<<endl;
    cout<<food.getIdentification_code()<<endl;
    cout<<food.totalCalories()<<endl;
    Food_list food2,food3(food);
    food2=food;
    cin>>food3;
    cout<<food3;
    food3++;
    food3=food3+food;
    food=food-food3;
    food3=food;
    if (food == food3){
        cout<<"\nDa";
    }
    if(food<food2){
        cout<<"NU";
    }
    Food_list per;
    per.setPrice(203.12312);
    cout<<int(per);
    cout<<food[1];
    string* fd2;
    fd2= new string[1];
    fd2[0]="12312312a1";
    FirstClass fir1,fir2;
    fir1.setTicketprice(2.1);
    cout<<fir1.getTicketprice();
    fir1.setShowernumber(2);
    cout<<fir1.getShowernumber();
    fir1.setSection_stewardess("ana");
    cout<<fir1.getSectionstewardess();
    FirstClass fir5(20,1,3,"Andrei","Rosu",2,1,fd2,2.23,3, "ana");
    FirstClass fir3(fir1),fir4;
    fir2 = fir1;
    cin>>fir4;
    cout<<fir4;
    string* fd2;
    fd2= new string[1];
    fd2[0]="12312312a1";
    EconomyClass ec1,ec2;
    ec1.setTicketprice(2.1);
    cout<<ec1.getTicketprice();
    ec1.setFreedrinksincluded(2);
    cout<<ec1.getFreedrinksincluded();
    ec1.setFreemeal("chicken");
    cout<<ec1.getFreemeal();
    EconomyClass ec5(20,1,3,"Andrei","Rosu",2,1,fd2,2.23,3, "ana");
    EconomyClass ec3(ec1),ec4;
    ec2 = ec1;
    cin>>ec4;
    cout<<ec4;
    NonAlcoholicDrink nonalch1(2,21,"aama",true);
    NonAlcoholicDrink nonalch2(nonalch1);
    nonalch1.openbottle();
    cout<<nonalch2;
    AlcoholicDrink alch1(10,21,"anaasdsa",4,nonalch1);
    cout<<alch1;
    AlcoholicDrink alch2;
    alch1.openbottle();
    //cin>>alch2;
    cout<<alch2;
    AlcoholicDrink alch3(alch1),alch4;
    alch4=alch3;
    cout<<alch4;

    Passport passport1,passport2(2,"StringSeries",5123131);
    Passport passport3(passport2);
    Passport passport4;
    passport4 = passport1;
    cout<<passport4;
    cout<<passport3;
    cin>>passport2;
    passport4.askForSeries();
    passport4.askForId();

    IdentityCard id1,id2(2,"StringSeries",5123131);
    IdentityCard id3(id2);
    IdentityCard id4;
    id4 = id1;
    cout<<id4;
    cout<<id3;
    cin>>id2;
    id3.askForSeries();
    id3.askForId();*/



    return 0;
}
