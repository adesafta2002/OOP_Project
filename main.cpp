#include <iostream>
#include <cstring>
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
    double getDeparture_coordinates();
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
    void book_seat();
    const Flight& operator++();
    const Flight operator++(int);
    Flight operator+(const Flight& flight_sec);
    Flight operator-(const Flight& flight_sec);
    bool operator<(const Flight& flight_sec);
    bool operator==(const Flight& flight_sec);
    int& operator[](int i);
};
int Flight::id_count=0;

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

void Flight::book_seat(){
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
        cout<<"\nThis seat is already booked, please select another!";
        cin>>seat;
    }
    this->seats_occupied[seat] = 1;
}

void Flight::setDeparture_coordinates(double latitude,double longitude){
    this->departure_coordinates[0] = latitude;
    this->departure_coordinates[1] = longitude;
}

double Flight::getDeparture_coordinates(){
    return departure_coordinates[0], departure_coordinates[1];
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

void Flight::setSeats_occupied(int Snumber, int *seats){
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

    if(this->airport_name != nullptr)
        delete[] this->airport_name;
    this->airport_name = new char[strlen(name)+1];
    strcpy(this->airport_name, name);

    this->fuel_needed = fuel;

    this->days_persons=days1;
    if(this->persons_bookedInNDays != nullptr)
        delete[] persons_bookedInNDays;
    this->persons_bookedInNDays = new int[days_persons];
    for(int i=0;i < days1 ; ++i)
        this->persons_bookedInNDays[i] = persons[i];

    this->days_money=days2;
    if(this->money_earnedInNDays!= nullptr)
        delete[] money_earnedInNDays;
    this->money_earnedInNDays = new float[days_money];
    for(int i=0;i < days1 ; ++i)
        this->money_earnedInNDays[i] = money[i];

    this->company_name = company;

    this->crew_members_number = number;
    if(this->crew_members_names != nullptr)
        delete[] crew_members_names;
    this->crew_members_names = new string[number];
    for(int i=0; i<crew_members_number; ++i)
        this->crew_members_names[i] = names[i];
    for(int i=1; i <= this->total_seats; i++)
        seats_occupied[i]=0;
    for(int i=1; i<=Snumber; ++i)
        this->seats_occupied[seats[i]] = 1 ;
}

Flight::Flight(double latitude, double longitude):flight_id(id_count++) {
    this->departure_coordinates[0] = latitude;
    this->departure_coordinates[1] = longitude;
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
    int pos;
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
private:
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
    Ticket operator+(const Ticket& ticket);
    Ticket operator-(const Ticket& ticket);
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

Ticket Ticket::operator+(const Ticket &ticket) {
    Ticket sec;
    sec = *this;
    sec.baggage_count = this->baggage_count + ticket.baggage_count;
    return sec;
}

Ticket Ticket::operator-(const Ticket &ticket) {
    Ticket sec;
    sec = *this;
    sec.baggage_count = this->baggage_count - ticket.baggage_count;
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
    for(int i=0;  i<this->products_number; i++)
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
}

Ticket::Ticket(int count, bool oneway,int seat, string fname, string lname,int flight_id,int number,string* food):ticket_id(id_count++){
    this->baggage_count = count;
    this->is_oneway = oneway;
    this->seat = seat;
    this->client_Fname = fname;
    this->client_Lname = lname;
    this->flight_id = flight_id;
    this->products_number = number;
    if(this->food_ordered != nullptr)
        delete[] this->food_ordered;
    this->food_ordered =  new string[this->products_number+1];
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
    cout<<"\nSeat: "; in>>ticket.seat;
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
};
int Food_list::count = 0;

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
    sec.name = this->name + food.name;
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

int main() {
    /*string n="Salcioara";
    getline(cin,n);
    Food_list a,b=a;
    cout<<a<<b;
    cout<<endl<<a[3]<<endl;
    for (int i = 0; i < n.size(); ++i) {
        cout<<n[i];
    }
    if(b==a)
        cout<<"\nDa";
    else
        cout<<"\nNU";
    if(b<a)
        cout<<"Da";
    else
        cout<<"NU";*/
    Ticket l;
    cin>>l;
    l.addProduct("ag");
    cout<<l;



    return 0;
}
