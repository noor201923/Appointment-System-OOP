#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<regex>
#include<cstdlib>
#include<ctime>
using namespace std;
struct Bill {
    string patientName;
    string doctorName;
    string appointmentTime;
    double fee;
    string paymentMethod;
};
class User {
private:
    string email;
    string password;
    string name;
    string age;
    string dob;
    string gender;
    string mobileNumber;
public:
    User(string email, string password, string name, string age, string dob, string gender, string mobileNumber) 
        : email(email), password(password), name(name), age(age), dob(dob), gender(gender), mobileNumber(mobileNumber) {}
        
    string getEmail() const 
	{
        return email;
    }
    bool checkPassword(string pass) const 
	{
        return password == pass;
    }
    string getName() const 
	{
        return name;
    }
};
class PaymentSystem {
public:
    bool processPayment(double amount, string paymentMethod, string accountNumber = "") 
	{
        cout<<"Processing payment via "<<paymentMethod<<"..."<<endl;
        if (paymentMethod == "Bank Transfer") 
		{
            cout<<"Account Number: "<<accountNumber<<endl;
        }
        return true;
    }
};
class AppointmentSlot {
public:
    string time;
    bool booked;
    string bookedBy;
public:
    AppointmentSlot(string time) : time(time), booked(false), bookedBy("") {}
    void bookSlot(const string& user) 
	{
        booked = true;
        bookedBy = user;
    }

    bool isBooked() const 
	{
        return booked;
    }

    string getTime() const 
	{
        return time;
    }

    string getBookedBy() const 
	{
        return bookedBy;
    }
};
class Doctor {
private:
    string name;
    string specialization;
    double appointmentFee;
    string bankAccountNumber;
    string easyPaisaNumber;
    vector<AppointmentSlot*> appointmentSlots;
public:
    Doctor(string name, string specialization, double fee, string bankAccNum, string easypaisaNum)
        : name(name), specialization(specialization), appointmentFee(fee), bankAccountNumber(bankAccNum), easyPaisaNumber(easypaisaNum) 
		{ 
        int startHour = 8;
        int endHour = 21;
        for (int i = startHour; i <= endHour; i++) 
		{
            string time;
            if (i < 12)
                time = to_string(i) + ":00 AM";
            else if (i == 12)
                time = "12:00 PM";
            else
                time = to_string(i - 12) + ":00 PM";
            appointmentSlots.push_back(new AppointmentSlot(time));
        }
    }
   
    string getName() const 
	{
        return name;
    }

    string getSpecialization() const 
	{
        return specialization;
    }

    double getAppointmentFee() const 
	{
        return appointmentFee;
    }

    string getBankAccountNumber() const 
	{
        return bankAccountNumber;
    }

    string getEasyPaisaNumber() const 
	{
        return easyPaisaNumber;
    }

    vector<AppointmentSlot*> getAppointmentSlots() const 
	{
        return appointmentSlots;
    }
};

class AppointmentSystem 
{
private:
    vector<User> users;
    vector<Bill> bills;
    bool loggedIn = false;
    User* currentUser = nullptr;
    PaymentSystem paymentGateway;
    Doctor doctors[10] = {
        Doctor("Dr. Sara Khan", "Pediatrician", 1000, "123456789", "090078601Teleone"),
        Doctor("Dr. Fatima Ahmed", "Cardiologist", 1100, "234567890", "090078601Teleone"),
        Doctor("Dr. Hassan Siddiqui", "Orthopedician", 1200, "345678901", "090078601Teleone"),
        Doctor("Dr. Ayesha Khan", "Anesthesiologist", 1300, "456789012", "090078601Teleone"),
        Doctor("Dr. Imran Mahmood", "Dermatologist", 1400, "567890123", "090078601Teleone"),
        Doctor("Dr. Sadia Malik", "Psychiatrist", 1500, "678901234", "090078601Teleone"),
        Doctor("Dr. Usman Ahmed", "Neurologist", 1600, "789012345", "090078601Teleone"),
        Doctor("Dr. Farah Khan", "Oncologist", 1700, "890123456", "090078601Teleone"),
        Doctor("Dr. Bilal Shah", "Urologist", 1800, "901234567", "090078601Teleone"),
        Doctor("Dr. Sana Aslam", "Ophthalmologist",1900, "012345678", "090078601Teleone")
    };
public:
    void registerUser() 
	{
        string name;
		string email; 
		string password; 
		string age;
		string dob; 
		string gender; 
		string mobileNumber;
        cout<<"ENTER YOUR EMAIL: ";
        getline(cin, email);
        regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        if (!regex_match(email, emailPattern)) 
		{
            cout<<"Invalid email format. Please enter a valid email address."<<endl;
            return;
        }
        cout<<"ENTER YOUR PASSWORD: ";
        getline(cin, password);
        cout<<"ENTER YOUR NAME: ";
        getline(cin, name);
        cout<<"ENTER YOUR AGE: ";
        getline(cin, age);
        cout<<"ENTER YOUR DATE OF BIRTH: ";
        getline(cin, dob);
        cout<<"ENTER YOUR GENDER: ";
        getline(cin, gender);
        cout<<"ENTER YOUR PHONE DIGITS: ";
        getline(cin, mobileNumber);
        cin.get();
        system("cls");
        
        //file handling writing operation
        ofstream SNS("Project.txt", ios::app);
    if (SNS.is_open()) 
	{
        SNS<<"Name: "<<name<<endl;
        SNS<<"Email: "<<email<<endl;
        SNS<<"Password: "<<password<<endl;
        SNS<<"Age: "<<age<<endl;
        SNS<<"Date of Birth: "<<dob<<endl;
        SNS<<"Gender: "<<gender<<endl;
        SNS<<"Phone Number: "<<mobileNumber<<endl;
        SNS<<"-----------------------------"<<endl;
        SNS.close();
        cout<<"User registered successfully!"<<endl;
    } 
	else 
	{
        cout<<"Unable to open file."<<endl;
    }
    users.push_back(User(email, password, name, age, dob, gender, mobileNumber));
}
    
    void login() 
	{
        string email;
		string password;
        cout<<"Enter email: ";
        getline(cin, email);
        cout<<"Enter password: ";
        getline(cin, password);
        cin.get();
        system("cls");
        for (User& user : users) 
		{
            if (user.getEmail() == email && user.checkPassword(password)) 
			{
                currentUser = &user;
                loggedIn = true;
                cout<<"Login successful!"<<endl;
                return;
            }
        }
        cout<<"Incorrect email or password. Please try again."<<endl;
    }

    void displayMainMenu() const 
	{
    cout<<"\t\t\t\t\tFOUNDATION HOSPITAL APPOINTMENT SYSTEM"<<endl;
    cout<<"\t\t\t\t\t---------------------------------------"<<endl;
    cout<<"\t\t\t1. Display Available Doctors"<<endl;
    cout<<endl;
    cout<<"\t\t\t2. Book Appointment"<<endl;
    cout<<endl;
    cout<<"\t\t\t3. View Doctors Availability Slots"<<endl;
    cout<<endl;
    cout<<"\t\t\t4. View My Appointments"<<endl;
    cout<<endl;
    cout<<"\t\t\t5. Cancel Appointment"<<endl;
    cout<<endl;
    cout<<"\t\t\t6. View eBill"<<endl;
    cout<<endl;
    cout<<"\t\t\t7. LOG OUT"<<endl;
    cout<<endl;
    cout<<"\t\t\tEnter your choice: ";
}
    void payForAppointment(double amount, const string& patientName, const string& appointmentTime, const string& doctorName, const string& accountNumber = "") 
	{
    cout<<"\n\t\t\t\t\tPAYMENT SCREEN"<<endl;
    cout<<"\t\t\t\t\t---------------"<<endl;
    cout<<left<<setw(20)<<"APPOINTMENT FEE";
    cout<<setw(20)<<"PATIENT NAME";
    cout<<setw(20)<<"APPOINTMENT TIME";
    cout<<setw(30)<<"DOCTOR BOOKED" << endl;
    cout<<"Rs. "<<left<<setw(16)<<amount<<setw(20)<<patientName<<setw(20)<<appointmentTime<<setw(20)<<doctorName<<endl;
    cout<<"\nChoose your payment method: "<<endl;
    cout<<"1. Bank Transfer"<<endl;
    cout<<"2. EasyPaisa"<<endl;
    cout<<"Enter your choice: ";
    int choice;
    cin>>choice;
    cin.ignore();
    string paymentMethod;
    if (choice == 1) 
	{
        paymentMethod = "Bank Transfer";
    } else if (choice == 2) 
	{
        paymentMethod = "EasyPaisa";
    } 
	else 
	{
        cout<<"Invalid choice. Defaulting to Bank Transfer."<<endl;
        paymentMethod = "Bank Transfer";
    }
    PaymentSystem paymentGateway;
    if (paymentGateway.processPayment(amount, paymentMethod, accountNumber)) 
	{
        cout<<"Payment successful!\n";
        bills.push_back({ patientName, doctorName, appointmentTime, amount, paymentMethod });
    } else {
        cout<<"Payment failed. Please try again later."<<endl;
    }
    
    //file handling write operation for displaying appointment details
    ofstream SNN("Project.txt", ios::app); 
    if (SNN.is_open()) 
	{
        SNN<< "Patient Name: "<<patientName<<endl;
        SNN<< "Doctor: "<<doctorName<<endl;
        SNN<< "Appointment Time: "<<appointmentTime<<endl;
        SNN<< "Appointment Fee: Rs. "<<amount<<endl;
        SNN<< "Payment Method: "<<paymentMethod<<endl;
        SNN<< "-----------------------------"<<endl;
        SNN.close();
    } 
	else 
	{
        cout<<"Unable to open file."<<endl;
    }
}
    void bookAppointment() 
	{
    cout<<"DOCTORS AVAILABLE AT OUR HOSPITAL:"<<endl;
    cout<<endl;
    cout<<"  DOCTOR'S NAME         SPECIALIZATION     APPOINTMENT FEE"<<endl;
    cout<<"  --------------------------------------------------------------"<<endl;
    for (int i = 0; i < 10; ++i) 
	{
        const Doctor& doctor = doctors[i];
        cout<<setw(3)<<right<< i+1 <<". ";
        cout<<left<<setw(20)<<doctor.getName();
        cout<<setw(18)<<doctor.getSpecialization();
        cout<<"Rs. "<<setw(10)<<doctor.getAppointmentFee()<<endl;
        cout<<endl;
    }
    cout<<"Please select a doctor to book an appointment (1-10): ";
    int choice;
    cin>>choice;
    
    if (choice >= 1 && choice <= 10) 
	{
        const Doctor& selectedDoctor = doctors[choice - 1];
        vector<AppointmentSlot*> slots = selectedDoctor.getAppointmentSlots();
        cout << "\nAvailable Slots for " << selectedDoctor.getName() << ":\n";
        for (size_t i = 0; i < slots.size(); ++i) 
	{
            cout<<setw(2)<<i + 1<<". "<<setw(10)<<left<<slots[i]->getTime()<<" (" << (slots[i]->isBooked() ? "BOOKED" : "AVAILABLE") << ")";
            if ((i + 1) % 3 == 0) 
		{
            cout<<endl;
        } 
		   else 
		{
           cout<<"\t";
        }
    }
        if (slots.size() % 3 != 0) 
		cout<<endl;
        cout<<"\nPlease select a slot: ";
        int slotChoice;
        cin>>slotChoice;
        cin.ignore();
        if (slotChoice >= 1 && slotChoice <= slots.size()) 
		{
            if (slots[slotChoice - 1]->isBooked()) 
			{
                cout<<"Sorry!!! This slot is already booked. Please choose another slot."<<endl;
            } 
			else 
			{
                slots[slotChoice - 1]->bookSlot(currentUser->getName());
                system("cls"); 
                payForAppointment(selectedDoctor.getAppointmentFee(), currentUser->getName(), slots[slotChoice - 1]->getTime(), selectedDoctor.getName(), selectedDoctor.getBankAccountNumber());
                cout<<"APPOINTMENT BOOKED SUCCESSFULLY"<<endl;
                cout<<"Press Enter to return to main menu...";
                cin.get();
                system("cls");
            }
        } 
		else 
		{
            cout<<"Invalid slot selection. Please try again."<<endl;
        }
    } 
	else 
	{
        cout<<"Invalid doctor selection. Please try again."<<endl;
    }
}
    void cancelAppointment() 
	{  
    cout<<"Appointments booked by "<<currentUser->getName()<<":"<<endl;
    cout<<"------------------------"<<endl;
    bool appointmentsFound = false;
    for (Doctor& doctor : doctors) 
	{
		//later
        for (AppointmentSlot* slot : doctor.getAppointmentSlots()) 
		{
            if (slot->isBooked() && slot->getBookedBy() == currentUser->getName()) 
		   {
                cout<<"Doctor: "<<doctor.getName()<<endl;
                cout<<"Specialization: "<<doctor.getSpecialization()<<endl;
                cout<<"Appointment Time: "<<slot->getTime()<<endl;
                cout<<"Appointment Fee: Rs. "<<doctor.getAppointmentFee()<<endl;
                cout<<"------------------------------"<<endl;
                appointmentsFound = true;
            }
        }
    }
    if (!appointmentsFound) 
	{
        cout<<"No appointments booked." << endl;
        return;
    }
    cout<<"Enter the appointment time you want to cancel: ";
    string cancelTime;
    getline(cin, cancelTime);
    for (Doctor& doctor : doctors) 
	{
        for (AppointmentSlot* slot : doctor.getAppointmentSlots()) {
            if (slot->isBooked() && slot->getBookedBy() == currentUser->getName() && slot->getTime() == cancelTime) 
			{
                slot->booked = false;
                slot->bookedBy = "";
                cout<<"Appointment at "<<cancelTime<<" cancelled successfully..."<<endl;
                return;
            }
        }
        
    } 
    cout<<"Appointment at "<<cancelTime<<"not found."<<endl;
}
    void displayAvailableDoctors() const 
	{
    cout<<"DOCTORS AVAILABLE AT OUR HOSPITAL:"<<endl;
    cout<<endl;
    cout<<"  DOCTOR'S NAME         SPECIALIZATION     APPOINTMENT FEE"<<endl;
    cout<<"  --------------------------------------------------------------"<<endl;
    for (int i = 0; i < 10; ++i) 
	{
        const Doctor& doctor = doctors[i];
        cout<<setw(3)<<right<< i+1 <<". ";
        cout<<setw(20)<<left<<doctor.getName();
        cout<<setw(18)<<left<<doctor.getSpecialization();
        cout<<right<<"Rs. "<<fixed<<setprecision(0)<<doctor.getAppointmentFee()<<endl;
        cout<<endl;
    }
}
   void displayDoctorSlots() const 
{
    cout << "\nDOCTORS AVAILABLE AT OUR HOSPITAL:\n" << endl;
    for (int i = 0; i < 10; ++i) 
    {
        cout<<setw(2)<<right<<i + 1<<". "<< doctors[i].getName()<<" ("<<doctors[i].getSpecialization()<<")"<<endl;
    }
    cout << "\nPlease select a doctor to view availability slots (1-10): ";
    int choice;
    cin>>choice;
    cin.ignore();
    
    if (choice >= 1 && choice <= 10) 
    {
        const Doctor& selectedDoctor = doctors[choice - 1];
        vector<AppointmentSlot*> slots = selectedDoctor.getAppointmentSlots();
        
        cout<<"\nAvailable Slots for " << selectedDoctor.getName() << ":\n";
        cout<<"------------------------------------------------\n";
        cout<<setw(5) << left << "No." << setw(15) << "Time" << "Status\n";
        cout<<"------------------------------------------------\n";
        
        for (size_t i = 0; i < slots.size(); ++i) 
        {
            cout<<setw(5)<<left<<i + 1<<setw(15)<<slots[i]->getTime()<<(slots[i]->isBooked() ? "BOOKED" : "AVAILABLE")<<endl;
        }
    } 
    else 
    {
        cout<<"Invalid doctor selection. Please try again."<<endl;
    }
}

void viewEBill() 
{
    cout<<"\n\t\t\t\t\tE-BILLS"<<endl;
    cout<<"\t\t\t\t\t--------"<<endl;
    if (bills.empty()) 
	{
        cout<<"No bills to show."<<endl;
        return;
    }
    time_t CurrentTime = time(0);
    char* transactionTime = ctime(&CurrentTime);
    cout<<"Transaction Time: "<<transactionTime<<endl;
    for (const Bill& bill : bills) 
	{
        cout<<left<<setw(20)<<"PATIENT NAME: "<<bill.patientName<<endl;
        cout<<left<<setw(20)<<"DOCTOR: "<<bill.doctorName<<endl;
        cout<<left<<setw(20)<<"APPOINTMENT TIME: "<<bill.appointmentTime<<endl;
        cout<<left<<setw(20)<<"FEE: Rs. "<<bill.fee<< endl;
        cout<<left<<setw(20)<<"PAYMENT METHOD: "<<bill.paymentMethod<<endl;
        cout<<"--------------------------------------------------"<<endl;
    }
}
    void displayAppointments() const 
	{
        cout<<"\nAppointments booked by "<<currentUser->getName() << ":\n";
        cout<<endl;
        bool appointmentsFound = false;
        for (const Doctor& doctor : doctors) 
		{
            for (const AppointmentSlot* slot : doctor.getAppointmentSlots())
			{
                if (slot->isBooked() && slot->getBookedBy() == currentUser->getName()) 
				{
                    cout<<"Doctor: "<<doctor.getName()<< endl;
                    cout<<"Specialization: "<<doctor.getSpecialization() << endl;
                    cout<<"Appointment Time: " <<slot->getTime() << endl;
                    cout<<"Appointment Fee: Rs. " <<doctor.getAppointmentFee() << endl;
                    cout<<"------------------------------"<< endl;
                    appointmentsFound = true;
                }
            }
        }
        if (!appointmentsFound) 
		{
            cout<<"No appointments booked."<<endl;
        }
    }

    void logout() 
	{
        if (loggedIn) {
            loggedIn = false;
            currentUser = nullptr;
            cout<<"Logged out successfully."<<endl;
        } else {
            cout<<"No user is currently logged in."<<endl;
        }
    }

    void start() 
	{
        while (true) 
		{
            if (!loggedIn)
			{
                cout<<"\t\t\t\t\tFOUNDATION HOSPITAL APPOINTMENT SYSTEM"<<endl;
                cout<<"\t\t\t\t\t---------------------------------------"<<endl;
                cout<<"\t\t\t1. Register"<<endl;
                cout<<endl;
                cout<<"\t\t\t2. Login"<<endl;
                cout<<endl;
                cout<<"\t\t\t3. Quit"<<endl;
                cout<<endl;
                cout<<"\t\t\tEnter your choice: ";
                int choice;
                cin>>choice;
                cin.ignore();
                switch (choice) 
				{
                case 1:
                    registerUser();
                    break;
                case 2:
                    login();
                    break;
                case 3:
                	cout<<"THANKYOU FOR USING FOUNDATION HOSPITAL APPOINTMENT SYSTEM"<<endl;
                    return;
                default:
                    cout<<"Invalid choice. Please try again." << endl;
                }
            } 
			else 
			{
                displayMainMenu();
                int choice;
                cin>>choice;
                cin.ignore();
                switch (choice) 
				{
                case 1:
                    displayAvailableDoctors();
                    break;
                case 2:
                    bookAppointment();
                    break;
                case 3:
                    displayDoctorSlots();
                    break;
                case 4:
                    displayAppointments();
                    break;
                case 5:
                    cancelAppointment();
                    break;
                case 6:
                    viewEBill();
                    break;
               case 7:
                    logout();
                }
            }
        }
    }
};
int main() 
{
    AppointmentSystem PROJECT;
    PROJECT.start();
    return 0;
}