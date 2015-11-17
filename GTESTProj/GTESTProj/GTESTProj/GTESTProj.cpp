#include "stdafx.h"  
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
*	This is the Member base class. It represents all the common data all members of a gym have.
Number of basic functions are included allowing setting and retrieving data for a member type.
Currently, there are two types of Members: CUSTOMER and STAFF. This is represented using enum Type.

Any subclass of member must implement a print, clone, and serialize function.
The print() function simply prints out any data associated with that specific member to the console.
The clone() function returns a copy of itself, used by the prototype pattern
The serialize() function turns the data associated with a member into a structured form to be stored in a file.
*/

class Member
{
public:

	/**
	The enumerated "Type" type is used to define whether if the staff is a customer, or a staff.
	*/
	enum Type { CUSTOMER, STAFF };

	/*Pure virtual functions to be implemented by derived classes*/

	/**
	Prints out all information related to this member into the console
	*/
	virtual void print(void) = 0;

	/**
	Clones and returns another instance of the current Member.
	*/
	virtual Member* clone() = 0;

	/**
	Serializes the current Member object into a readable structure for file storage. 
	*/
	virtual void serialize(string file_name) = 0;

	/**
	Reads a structured serialized file and returns an appropriate member object from it
	*/
	virtual Member* deserialize(string file_name) = 0;

	/*Other functions shared by all derived classes*/

	/**
	Sets the current member's full name.
	*/
	void setName(string name)
	{
		this->name = name;
	}

	/**
	Sets the current member's address.
	*/
	void setAddress(string address)
	{
		this->address = address;
	}

	/**
	Sets the current member's member type. This function should not be called again after initial construction for security reasons.
	*/
	void setMemberType(Type member_type)
	{
		this->member_type = member_type;
	}

	/**
	Sets the current member's gym membership ID explicitly instead of using the randomly generated one.
	*/
	void setMembershipID(unsigned long membership_id)
	{
		this->membership_id = membership_id;
	}

	/**
	Sets the current member's bracelet ID used to interact with machines.
	*/
	void setBraceletID(unsigned long bracelet_id)
	{
		this->bracelet_id = bracelet_id;
	}

	/**
	Retreives the current member's full name as a string.
	*/
	string getName()
	{
		return name;
	}

	/**
	Retreives the current member's address as a string.
	*/
	string getAddress()
	{
		return address;
	}

	/**
	Retreives the current member's gym membership ID as an unsigned long.
	*/
	unsigned long getMembershipID()
	{
		return membership_id;
	}

	/**
	Retreives the current member's gym bracelet ID as an unsigned long.
	*/
	unsigned long getBraceletID()
	{
		return bracelet_id;
	}

	/**
	Returns what type of member this is.
	*/
	Type getMemberType()
	{
		return member_type;
	}

private:
	string name;
	string address;
	unsigned long membership_id;
	unsigned long bracelet_id;
	Member::Type member_type;
};

/**
The Customer class is a derived class of Members. It's used to represent a client of a gym.
On top of the datas used in a Member type, a Customer needs to specify a credit card number (unsigned long credit_card_num),
the amount of credits the customer has in his/her account (int gym_credit), and a membership tier the customer is paying.
The membership tier is represented by a enum SubscriptionLevel, which can be INACTIVE, BASIC, PREMIUM, DELUXE.

The Customer class requires to be manually initialized after construction, since the constructor does not take any arguments.
Use the "intialize" function to fill in the data for the customer. Alternatively, each of the data fields can be set individually using individual set methods.
*/
class Customer : public Member
{
public:

	/**
	The enumerated "SubscriptionLevel" type defines the membership plan that a customer is currently subscribed to.
	*/
	enum SubscriptionLevel { INACTIVE, BASIC, PREMIUM, DELUXE };

	/**
	Constructor for Customer.
	*/
	Customer()
	{
		setMemberType(CUSTOMER);
		setGymCredits(20);
	}

	/*Implemeting Member's Virtual Functions*/

	/**
	Prints out all data related to the current customer to the console. The output takes the following format:

	Name
	Address
	Membership ID
	Bracelet ID
	Credit Card Number
	Gym Credits
	*/
	void print(void)
	{
		cout << getName() << endl << getAddress() << endl << getMembershipID() << endl << getBraceletID()
			<< endl << getCreditCard() << endl << getGymCredits() << endl;
	}

	/**
	To be used by the MemberFactory, the clone() function returns another instance of the current Customer.
	*/
	Customer* clone()
	{
		return new Customer(*this);
	}

	/**
	Serializes the current Staff object into a structured object to be stored in text.
	*/
	void serialize(string file_name)
	{

	}

	/**
	Reads a structured serialized file and returns an appropriate Customer object from it
	*/
	Customer* deserialize(string file_name)
	{
		return NULL;
	}

	/*Other functions*/

	/**
	Since the default constructor does not take paramters, this function must be ran to add the necessary data needed for a Customer.
	Alternatively, the data can be added individually using each of the set functions.
	*/
	void initialize(string name, string address, unsigned long credit_card_num, unsigned long bracelet_id, SubscriptionLevel subscription_level)
	{
		srand(time(NULL));
		setMembershipID(rand());

		setName(name);
		setAddress(address);
		setBraceletID(bracelet_id);
		setCreditCard(credit_card_num);
		setSubscriptionLevel(subscription_level);
	}

	/**
	Sets a credit card number for the current customer.
	*/
	void setCreditCard(unsigned long credit_card_num)
	{
		this->credit_card_num = credit_card_num;
	}

	/**
	Sets a fixed amount of gym credit for the current customer.
	*/
	void setGymCredits(int gym_credits)
	{
		this->gym_credits = gym_credits;
	}

	/**
	Adds a fixed amount of gym credit for the current customer on top of his/her current balance.
	*/
	void addGymCredits(int amount)
	{
		gym_credits += amount;
	}

	/**
	Deducts a fixed amount of gym credit for the current customer on top of his/her current balance.
	*/
	void deductGymCredits(int amount)
	{
		gym_credits -= amount;
	}

	/**
	Change the membership subscription level of the current customer.
	*/
	void setSubscriptionLevel(SubscriptionLevel subscription_level)
	{
		this->subscription_level = subscription_level;
	}

	/**
	Retreives the current member's credit card number as an unsigned long.
	*/
	int getCreditCard()
	{
		return credit_card_num;
	}

	/**
	Retreives the current member's gym credit amount as an int.
	*/
	int getGymCredits()
	{
		return gym_credits;
	}

	/**
	Retreives the current member's membership subscription level.
	*/
	SubscriptionLevel getSubscriptionLevel()
	{
		return subscription_level;
	}

private:
	unsigned long credit_card_num;
	int gym_credits;
	SubscriptionLevel subscription_level;

};

/**
The Staff class is a derived class of Members. It's used to represent a staff member of a gym.
On top of the datas used in a Member type, a staff must specify his/her employee number (unsigned long employee_id),
as well as its role in the gym (Clearance staff_clearance).

The role is represented using a enum Clearance, and has the values of GENERAL, MANAGER, ADMINISTRATOR.

The Staff class requires to be manually initialized after construction, since the constructor does not take any arguments.
Use the "intialize" function to fill in the data for the Staff. Alternatively, each of the data fields can be set individually using individual set methods.
*/

class Staff : public Member
{
public:

	/**
	The enumerated "Clearance" type defines the security clearance and roles of a staff.
	*/
	enum Clearance { GENERAL, MANAGER, ADMINISTRATOR };

	/**
	Constructor for Staff.
	*/
	Staff()
	{
		setMemberType(STAFF);
	}

	/*Implemeting Member's Virtual Functions*/

	/**
	Prints out all data related to the current customer to the console. The output takes the following format:

	Name
	Address
	Membership ID
	Bracelet ID
	Employee ID
	*/
	void print(void)
	{
		cout << getName() << endl << getAddress() << endl << getMembershipID() << endl << getBraceletID()
			<< endl << getEmployeeID() << endl;
	}

	/**
	To be used by the MemberFactory, the clone() function returns another instance of the current Staff.
	*/
	Staff* clone()
	{
		return new Staff(*this);
	}

	/**
	Serializes the current Staff object into a structured object to be stored in text.
	*/
	void serialize(string file_name)
	{

	}

	/**
	Reads a structured serialized file and returns an appropriate Staff object from it
	*/
	Staff* deserialize(string file_name)
	{
		return NULL;
	}

	/*Other functions*/

	/**
	Since the default constructor does not take paramters, this function must be ran to add the necessary data needed for a Customer.
	Alternatively, the data can be added individually using each of the set functions.
	*/
	void initialize(string name, string address, unsigned long credit_card_num, unsigned long bracelet_id, Clearance staff_clearance)
	{
		srand(time(NULL));
		setMembershipID(rand());
		setEmployeeID(rand());

		setName(name);
		setAddress(address);
		setBraceletID(bracelet_id);
		setStaffClearance(staff_clearance);
	}

	/**
	Sets the employee ID for the current Staff.
	*/
	void setEmployeeID(unsigned long employee_id)
	{
		this->employee_id = employee_id;
	}

	/**
	Sets the current staff's security clearance/role.
	*/
	void setStaffClearance(Clearance staff_clearance)
	{
		this->staff_clearance = staff_clearance;
	}

	/**
	Retreives the employee ID for the current Staff.
	*/
	unsigned long getEmployeeID()
	{
		return employee_id;
	}

	/**
	Retreives the security clearance for the current Staff.
	*/
	Clearance getStaffClearance()
	{
		return staff_clearance;
	}

private:
	unsigned long employee_id;
	Clearance staff_clearance;

};

/**
The MemberFactory class makes clones of a templated Customer and Staff to return new objects back to the caller.
Two templates are created, Customer* CustomerClone and Staff* StaffClone. They are both initialized upon constructing the factory.

Once an instance of the MemberFactory has been constructed, copies of Customer can be created by calling the getCustomer() function.
Similarily, copies of Staff can also be created by calling the getStaff() function.
Both functions will only return a barebone template. The corresponding "initialize" function for each class must be called after to fill them with data.
*/
class MemberFactory
{

private:
	/*Default templates to used for cloning*/
	Customer* CustomerClone;
	Staff* StaffClone;

public:

	/**
	Constructor for MemberFactory.
	*/
	MemberFactory()
	{
		CustomerClone = new Customer();
		StaffClone = new Staff();
	}

	/**
	Destructor for MemberFactory.
	*/
	~MemberFactory()
	{
		delete CustomerClone;
		delete StaffClone;
	}

	/**
	Returns a "new" Customer by cloning a barebone template of one.
	*/
	Customer* getCustomer()
	{
		return CustomerClone->clone();
	}

	/**
	Returns a "new" Staff by cloning a barebone template of one.
	*/
	Staff* getStaff()
	{
		return StaffClone->clone();
	}
};

/*Test macros for gtest*/

/*Testing the Customer and Member class*/
TEST(test_customers_case1, test_customers)
{
	Customer m;
	m.initialize("John Doe", "123 Maple Rd", 123456789, 987654321, Customer::SubscriptionLevel::BASIC);
	
	/*Check Name*/
	EXPECT_STREQ("John Doe", m.getName().c_str());
	m.setName("Doe John");
	EXPECT_STREQ("Doe John", m.getName().c_str());

	/*Check Address*/
	EXPECT_STREQ("123 Maple Rd", m.getAddress().c_str());
	m.setAddress("321 Rd Maple");
	EXPECT_STREQ("321 Rd Maple", m.getAddress().c_str());
	
	/*Check Credit Card Number*/
	EXPECT_EQ(123456789, m.getCreditCard());
	m.setCreditCard(1111111);
	EXPECT_EQ(1111111, m.getCreditCard());

	/*Check Membership ID*/
	EXPECT_LT(0, m.getMembershipID());
	m.setMembershipID(333333333);
	EXPECT_EQ(333333333, m.getMembershipID());

	/*Check Bracelet ID*/
	EXPECT_EQ(987654321, m.getBraceletID());
	m.setBraceletID(222222222);
	EXPECT_EQ(222222222, m.getBraceletID());

	/*Check Gym Credits*/
	EXPECT_EQ(20, m.getGymCredits());
	m.setGymCredits(100);
	EXPECT_EQ(100, m.getGymCredits());
	m.addGymCredits(10);
	EXPECT_EQ(110, m.getGymCredits());
	m.deductGymCredits(100);
	EXPECT_EQ(10, m.getGymCredits());

	/*Check Subscription Levels*/
	EXPECT_EQ(Customer::SubscriptionLevel::BASIC, m.getSubscriptionLevel());
	m.setSubscriptionLevel(Customer::SubscriptionLevel::PREMIUM);
	EXPECT_EQ(Customer::SubscriptionLevel::PREMIUM, m.getSubscriptionLevel());

	/*Check Member Type*/
	EXPECT_EQ(Member::Type::CUSTOMER, m.getMemberType());
}

/*Testing the Staff and Member class*/
TEST(test_staff_case1, test_staff)
{
	Staff m;
	m.initialize("Mary Janes", "420 Dank Hill", 2214356879, 87654321, Staff::Clearance::MANAGER);

	/*Check Name*/
	EXPECT_STREQ("Mary Janes", m.getName().c_str());
	m.setName("Jane Mary");
	EXPECT_STREQ("Jane Mary", m.getName().c_str());

	/*Check Address*/
	EXPECT_STREQ("420 Dank Hill", m.getAddress().c_str());
	m.setAddress("024 Hill Dank");
	EXPECT_STREQ("024 Hill Dank", m.getAddress().c_str());

	/*Check Membership ID*/
	EXPECT_LT(0, m.getMembershipID());
	m.setMembershipID(333333333);
	EXPECT_EQ(333333333, m.getMembershipID());

	/*Check Bracelet ID*/
	EXPECT_EQ(87654321, m.getBraceletID());
	m.setBraceletID(222222222);
	EXPECT_EQ(222222222, m.getBraceletID());

	/*Check Employee ID*/
	EXPECT_LT(0, m.getEmployeeID());
	m.setEmployeeID(333333333);
	EXPECT_EQ(333333333, m.getEmployeeID());

	/*Check Subscription Levels*/
	EXPECT_EQ(Staff::Clearance::MANAGER, m.getStaffClearance());
	m.setStaffClearance(Staff::Clearance::GENERAL);
	EXPECT_EQ(Staff::Clearance::GENERAL, m.getStaffClearance());

	/*Check Member Type*/
	EXPECT_EQ(Member::Type::STAFF, m.getMemberType());
}

/*Testing the Factory class using Customers*/
TEST(test_factory_customer, test_factory1)
{
	MemberFactory member_factory;
	Customer* m = member_factory.getCustomer();

	m->initialize("John Doe", "123 Maple Rd", 123456789, 987654321, Customer::SubscriptionLevel::BASIC);

	/*Check Name*/
	EXPECT_STREQ("John Doe", m->getName().c_str());
	m->setName("Doe John");
	EXPECT_STREQ("Doe John", m->getName().c_str());

	/*Check Address*/
	EXPECT_STREQ("123 Maple Rd", m->getAddress().c_str());
	m->setAddress("321 Rd Maple");
	EXPECT_STREQ("321 Rd Maple", m->getAddress().c_str());

	/*Check Credit Card Number*/
	EXPECT_EQ(123456789, m->getCreditCard());
	m->setCreditCard(1111111);
	EXPECT_EQ(1111111, m->getCreditCard());

	/*Check Membership ID*/
	EXPECT_LT(0, m->getMembershipID());
	m->setMembershipID(333333333);
	EXPECT_EQ(333333333, m->getMembershipID());

	/*Check Bracelet ID*/
	EXPECT_EQ(987654321, m->getBraceletID());
	m->setBraceletID(222222222);
	EXPECT_EQ(222222222, m->getBraceletID());

	/*Check Gym Credits*/
	EXPECT_EQ(20, m->getGymCredits());
	m->setGymCredits(100);
	EXPECT_EQ(100, m->getGymCredits());
	m->addGymCredits(10);
	EXPECT_EQ(110, m->getGymCredits());
	m->deductGymCredits(100);
	EXPECT_EQ(10, m->getGymCredits());

	/*Check Subscription Levels*/
	EXPECT_EQ(Customer::SubscriptionLevel::BASIC, m->getSubscriptionLevel());
	m->setSubscriptionLevel(Customer::SubscriptionLevel::PREMIUM);
	EXPECT_EQ(Customer::SubscriptionLevel::PREMIUM, m->getSubscriptionLevel());
	/*Check Member Type*/
	EXPECT_EQ(Member::Type::CUSTOMER, m->getMemberType());
}

/*Testing the Factory class using Staff*/
TEST(test_factory_staff, test_factory2)
{
	MemberFactory member_factory;
	Staff* m = member_factory.getStaff();
	m->initialize("Mary Janes", "420 Dank Hill", 2214356879, 87654321, Staff::Clearance::MANAGER);

	/*Check Name*/
	EXPECT_STREQ("Mary Janes", m->getName().c_str());
	m->setName("Jane Mary");
	EXPECT_STREQ("Jane Mary", m->getName().c_str());

	/*Check Address*/
	EXPECT_STREQ("420 Dank Hill", m->getAddress().c_str());
	m->setAddress("024 Hill Dank");
	EXPECT_STREQ("024 Hill Dank", m->getAddress().c_str());

	/*Check Membership ID*/
	EXPECT_LT(0, m->getMembershipID());
	m->setMembershipID(333333333);
	EXPECT_EQ(333333333, m->getMembershipID());

	/*Check Bracelet ID*/
	EXPECT_EQ(87654321, m->getBraceletID());
	m->setBraceletID(222222222);
	EXPECT_EQ(222222222, m->getBraceletID());

	/*Check Employee ID*/
	EXPECT_LT(0, m->getEmployeeID());
	m->setEmployeeID(333333333);
	EXPECT_EQ(333333333, m->getEmployeeID());

	/*Check Subscription Levels*/
	EXPECT_EQ(Staff::Clearance::MANAGER, m->getStaffClearance());
	m->setStaffClearance(Staff::Clearance::GENERAL);
	EXPECT_EQ(Staff::Clearance::GENERAL, m->getStaffClearance());

	/*Check Member Type*/
	EXPECT_EQ(Member::Type::STAFF, m->getMemberType());
}

int main(int argc, char** argv)
{
	/*Test stuff*/
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	/*Use as a pause*/
	getchar(); 
}