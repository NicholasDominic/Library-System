#include <iostream>
#include <string>	
#include <tuple>
#include <vector>
#include <thread>
#include <fstream>
#include <ctime>
#include <chrono> 

#define cc cin.clear(); cin.sync();

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int BUTTON_TOTAL = 4;

static int sUserCounter = 0;
static int sItemCounter = 0;
static int sRegCounter = 0;
static int sBorCounter = 0; 
static int sRetCounter = 0;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

enum LItemType
{
	ITEM_TYPE_BOOK = 0,
	ITEM_TYPE_MAGAZINE = 1,
	ITEM_TYPE_DISC = 2,
	ITEM_TYPE_TOTAL = 3
};

class GeneralItemData
{
public:
	void setItemDate (int date, int month, int year);
	void setItemCode (string code) { this->mItemCode = code; }
	void setItemTitle(string title) { this->mItemTitle = title; }
	void setItemType(LItemType type) { this->mItemType = type;  }
	void setItemStock(int stock) { this->mItemStock = stock; }
	
	tuple <int, int, int> getItemDate();
	string getItemCode() { return mItemCode; }
	string getItemTitle() { return mItemTitle; }
	LItemType getItemType() { return mItemType; }
	int getItemStock() { return mItemStock; }

	string getItemTypeDef();

	void fillItemData(string code, string title, LItemType type, int date, int month, int yeat, int stock);
	
private :
	string mItemCode;
	LItemType mItemType;
	string mItemTitle;
	int mItemStock;
	int mDatePublished;
	int mMonthPublished;
	int mYearPublished;
};

void GeneralItemData::fillItemData(string code, string title, LItemType type, int date, int month, int year, int stock)
{
	this->mItemCode = code;
	this->mItemTitle = title;
	this->mItemType = type;
	this->mDatePublished = date;
	this->mMonthPublished = month;
	this->mYearPublished = year;
	this->mItemStock = stock;
}
void GeneralItemData::setItemDate(int date, int month, int year)
{
	this->mDatePublished = date;
	this->mMonthPublished = month;
	this->mYearPublished = year;
}
tuple <int, int, int> GeneralItemData :: getItemDate()
{
	return std::make_tuple(mDatePublished, mMonthPublished, mYearPublished); //auto date = ThisBook.getBookDate(); std::get<0>(getBookDate)
}

string GeneralItemData::getItemTypeDef()
{
	switch (getItemType())
	{
	case ITEM_TYPE_BOOK:
		return "Book";
		break;
	case ITEM_TYPE_MAGAZINE:
		return "Magazine";
		break;
	case ITEM_TYPE_DISC:
		return "Disc";
		break;
	}
}

class Book : virtual public GeneralItemData
{
public:
	void setISBN(string ISSN) { this->isbn = ISSN; }
	void setAuthor(string vol) { this->author = vol; }

	string getISBN() { return isbn; }
	string getAuthor() { return author; }

private:
	string isbn;
	string author;
};

class Magazine : virtual public GeneralItemData
{
public:
	void setISSN(string ISSN) { this->issn = ISSN; }
	void setEdition(int vol) { this->edition = vol; }

	string getISSN() { return issn; }
	int getEdition() { return edition; }

private:
	string issn;
	int edition;
};

class Disc : virtual public GeneralItemData
{
public:
	void setOwner(string Owner) { this->owner = Owner; }
	void setVolume(int vol) { this->vol = vol; }

	string getOwner() { return owner; }
	int getVolume() { return vol; }

private:
	string owner;
	int vol;
};

class ItemData : public Book, public Magazine, public Disc
{
public :
	void fillItemInfo(string info1, string info2); //fill Data before info (must define type)
	string getItemInfo1();
	string getItemInfo2();
	string getImplementedDate();

};

class UserData {

public :

	void fillUserData(string mIdCode, string mUserName, string mUserIDName, string mUserPassword, string mUserAddress, bool type);

	void encryptPassword();
	void decryptPassword();

	string getUserIDName() { return mUserIDName; }
	string getUserName() { return mUserName; }
	string getUserPassword() { return mUserPassword; }
	string getUserAddress() { return mUserAddress; }
	string getUserIdCode() { return mIdCode; }
	bool getUserType() { return type; }

	void setUserIDName(string mThisUser) { this->mUserIDName = mThisUser; }
	void setUserName(string mThisUser) { this->mUserName = mThisUser; }
	void setUserPassword(string mThisUser) { this->mUserPassword = mThisUser; }
	void setUserAddress(string mThisUser) { this->mUserAddress = mThisUser; }
	void setUserIdCode(string mThisUser) { this->mIdCode = mThisUser; }
	void setUserType(bool mThisUser) { this->type = mThisUser; }

protected :
	
	string mIdCode;
	string mUserName;
	string mUserIDName;
	string mUserPassword;
	string mUserAddress;
	bool type;
};

void UserData :: fillUserData(string mIdCode, string mUserName, string mUserIDName, string mUserPassword, string mUserAddress, bool type)
{
	this->mUserIDName = mUserIDName;
	this->mUserName = mUserName;
	this->mUserPassword = mUserPassword;
	this->mUserAddress = mUserAddress;
	this->mIdCode = mIdCode;
	this->type = type;
}

class RegistrationData : public UserData {
public :
	void fillRegData(string rCode, string mUserName, string mUserIDName, string mUserPassword, string mUserAddress);

	string getUserRCode() { return rCode; }

	void setUserRCode(string mThisUser) { this->rCode = mThisUser; }
private : 
	string rCode;
};

void RegistrationData::fillRegData(string rCode, string mUserName, string mUserIDName, string mUserPassword, string mUserAddress)
{
	this->mUserIDName = mUserIDName;
	this->mUserName = mUserName;
	this->mUserPassword = mUserPassword;
	this->mUserAddress = mUserAddress;
	this->rCode = rCode;
}

class BorrowData
{
public :
	void setBorrowDate(int date, int month, int year);
	void setItemDate(int date, int month, int year);
	void setItemCode(string code) { this->mItemCode = code; }
	void setItemTitle(string title) { this->mItemTitle = title; }
	void setItemType(int type) { this->mItemType = type; }
	void setItemInfo1(string info) { this->mItemInfo1 = info; }
	void setItemInfo2(string info) { this->mItemInfo2 = info; }
	void setUserIdCode(string mThisUser) { this->mIdCode = mThisUser; }
	void setUserAddress(string mThisUser) { this->mUserAddress = mThisUser; }
	void setUserName(string mThisUser) { this->mUserName = mThisUser; }

	string getUserIdCode() { return mIdCode; }
	string getUserAddress() { return mUserAddress; }
	tuple <int, int, int> getBorrowedDate();
	tuple <int, int, int> getItemDate();
	string getImplementedBorrowedDate();
	string getItemCode() { return mItemCode; }
	string getItemTitle() { return mItemTitle; };
	int getItemType() { return mItemType; };
	string getItemInfo1() { return mItemInfo1; }
	string getItemInfo2() { return mItemInfo2; }
	string getUserName() { return mUserName; }
	string getImplementedItemDate();
	string getItemTypeDef();
	int getCalculatedDate();

	void fillBorrowData(string IDcode, string name, string address, string code, string title, string info1, string info2, int type, int pDate, int pMonth, int pYear);

protected :
	string mItemCode;
	int mItemType;
	string mItemTitle;
	string mItemInfo1;
	string mItemInfo2;
	int mDateBorrowed;
	int mMonthBorrowed;
	int mYearBorrowed;
	int mPublishedDate;
	int mPublishedMonth;
	int mPublishedYear;
	string mIdCode;
	string mUserName;
	string mUserAddress;
};

void BorrowData :: fillBorrowData(string IDcode, string name, string address, string code, string title, string info1, string info2, int type, int pDate, int pMonth, int pYear)
{
	mIdCode = IDcode;
	mUserName = name;
	mUserAddress = address;
	mItemCode = code;
	mItemTitle = title;
	mItemInfo1 = info1;
	mItemInfo2 = info2;
	mItemType = type; 
	mPublishedDate = pDate;
	mPublishedMonth = pMonth;
	mPublishedYear = pYear;
}

void BorrowData::setBorrowDate(int date, int month, int year)
{
	this->mDateBorrowed = date;
	this->mMonthBorrowed = month;
	this->mYearBorrowed = year;
}
void BorrowData::setItemDate(int date, int month, int year)
{
	mPublishedDate = date;
	mPublishedMonth = month;
	mPublishedYear = year;
}
tuple <int, int, int> BorrowData::getBorrowedDate()
{
	return std::make_tuple(mDateBorrowed, mMonthBorrowed, mYearBorrowed); //auto date = ThisBook.getBookDate(); std::get<0>(getBookDate)
}

tuple <int, int, int> BorrowData::getItemDate()
{
	return std::make_tuple(mPublishedDate, mPublishedMonth, mPublishedYear); //auto date = ThisBook.getBookDate(); std::get<0>(getBookDate)
}

string BorrowData::getImplementedBorrowedDate()
{
	return (to_string(mDateBorrowed) + "/" + to_string(mMonthBorrowed+1) + "/" + to_string(mYearBorrowed+1900));
}

string BorrowData::getImplementedItemDate()
{
	auto dates = getItemDate();
	return (to_string(std::get<0>(dates)) + "/" + to_string(std::get<1>(dates)) + "/" + to_string(std::get<2>(dates)));
}

string BorrowData::getItemTypeDef()
{
	switch (getItemType())
	{
	case ITEM_TYPE_BOOK:
		return "Book";
		break;
	case ITEM_TYPE_MAGAZINE:
		return "Magazine";
		break;
	case ITEM_TYPE_DISC:
		return "Disc";
		break;
	}
}

tuple <int, int, int> getTodaysDate()
{
	tm * timer;
	time_t now;
	time(&now);
	timer = localtime(&now);
	int day = timer->tm_mday;
	int month = timer->tm_mon;
	int year = timer->tm_year;
	return make_tuple(day, month, year);
}

int BorrowData::getCalculatedDate()
{
	auto bDates = getBorrowedDate();
	auto tDates = getTodaysDate();
	int days;

	int date = get<0>(tDates);
	int month = get<1>(tDates);
	int year = get<2>(tDates)-1900;

	if (month == 1)
		days = 28;
	else if (month % 2 == 0)
		days = 30;
	else
		days = 31;
	int finDate = (365 * (year - mYearBorrowed) + days * (month - mMonthBorrowed) + date - mDateBorrowed);
	return finDate;
}

class ReturnData : public BorrowData
{
public :
	string getItemRCode() { return rCode; }

	void setItemRCode(string mThisUser) { this->rCode = mThisUser; }

	void fillReturnData(string rCode, string IDcode, string name, string address, string code, string title, string info1, string info2, int type, int pDate, int pMonth, int pYear);
private:
	string rCode;
};
void ReturnData::fillReturnData(string rCode, string IDcode, string name, string address, string code, string title, string info1, string info2, int type, int pDate, int pMonth, int pYear)
{
	this->rCode = rCode;
	mIdCode = IDcode;
	mUserName = name;
	mUserAddress = address;
	mItemCode = code;
	mItemTitle = title;
	mItemType = type;
	mItemInfo1 = info1;
	mItemInfo2 = info2;
	mPublishedDate = pDate;
	mPublishedMonth = pMonth;
	mPublishedYear = pYear;
}


vector<UserData> users;
UserData thisUser;
vector <RegistrationData> regUsers;
vector <ItemData> items;
ItemData thisItem;
vector <ReturnData> returns;
vector <BorrowData> borrows;
vector <int> indexKeeper;

void getUserDatas()
{
	string stringLine;
	string fullname;
	string id;
	string pass;
	string address;
	string type;
	string username;
	bool truType;
	int uStart;
	int uSpace = 0;

	ifstream files;
	files.open("uDatas.txt", fstream::in);
	if (files.fail())
	{
		cout << "File is non-existent." << endl;
	}
	else
	{
		users.clear();
		sUserCounter = 0;
		while (!files.eof()) {
			uStart = 0;

			getline(files, stringLine); cc; //stringLine will keep all string on a line in files'
			if (stringLine == "")
			{
				break;
			}

			uSpace = stringLine.find('#', 0); // find the separator character
			username.assign(stringLine, uStart, uSpace - uStart);//  the exact word to be copied (string, starting index, character length)
				

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			pass.assign(stringLine, uStart, uSpace - uStart);
					
			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			type.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			fullname.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			address.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('\0', uStart);
			id.assign(stringLine, uStart, uSpace - uStart);

			if (type == "true") truType = true;
			else truType = false;
				
			UserData toVector;
			toVector.fillUserData(id, fullname, username, pass, address, truType);
			toVector.decryptPassword();

			users.push_back(toVector);

			sUserCounter++;
		}
		
		
	}
	files.close();
}

void OvwUserDatas()
{
	int counter = 0;
	string type;
	ofstream myfile;
	myfile.open("uDatas.txt", fstream::trunc);
	while (counter < sUserCounter)
	{
		if (users.at(counter).getUserType() == true) type = "true"; else type = "false";

		users.at(counter).encryptPassword();
		myfile << users.at(counter).getUserIDName() << "#";
		myfile << users.at(counter).getUserPassword() << "#";
		myfile << type << "#";
		myfile << users.at(counter).getUserIDName() << "#";
		myfile << users.at(counter).getUserAddress() << "#";
		myfile << users.at(counter).getUserIdCode();

		if (counter < sUserCounter)  myfile << endl;

		counter++;
		}

	myfile.close();
}

void getRegDatas()
{
	string stringLine;
	string fullname;
	string id;
	string pass;
	string address;
	string rcode;
	string username;
	int uStart;
	int uSpace = 0;

	ifstream files;
	files.open("regDatas.txt", fstream::in);
	if (files.fail())
	{
		cout << "File is non-existent." << endl;
	}
	else
	{
		regUsers.clear();
		sRegCounter = 0;
		while (!files.eof()) {
			uStart = 0;

			getline(files, stringLine); cc; //stringLine will keep all string on a line in files
			if (stringLine == "")
			{
				break;
			}

			uSpace = stringLine.find('#', 0); // find the separator character
			rcode.assign(stringLine, uStart, uSpace - uStart);//  the exact word to be copied (string, starting index, character length)
			

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			username.assign(stringLine, uStart, uSpace - uStart);
			
			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			pass.assign(stringLine, uStart, uSpace - uStart);
			
			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			fullname.assign(stringLine, uStart, uSpace - uStart);
			
			uStart = uSpace + 1;
			uSpace = stringLine.find('\n', uStart);
			address.assign(stringLine, uStart, uSpace - uStart);
			
			RegistrationData thisReg;
			thisReg.fillRegData(rcode, fullname, username, pass, address);
			thisReg.decryptPassword();

			regUsers.push_back(thisReg);

			sRegCounter++;
		}
		
		
	}
	files.close();
}

void OvwRegDatas()
{
	int counter = 0;
	string type;

	ofstream myfile;
	myfile.open("regDatas.txt", fstream::trunc);
	while (counter < sRegCounter)
	{
		regUsers.at(counter).encryptPassword();
		myfile << regUsers.at(counter).getUserRCode() << "#";
		myfile << regUsers.at(counter).getUserIDName() << "#";
		myfile << regUsers.at(counter).getUserPassword() << "#";
		myfile << regUsers.at(counter).getUserName() << "#";
		myfile << regUsers.at(counter).getUserAddress();
		
		if (counter < sRegCounter)  myfile << endl;

		counter++;
	}

	myfile.close();

}

LItemType itemTypeInvert(int type)
{
	switch (type) 
	{
	case 0: return ITEM_TYPE_BOOK;
	case 1: return ITEM_TYPE_MAGAZINE;
	case 2: return ITEM_TYPE_DISC;
	}
}

LItemType itemTypeInvert(string type)
{
	if(type == "disc")  return ITEM_TYPE_DISC;
	else if (type == "magazine") return ITEM_TYPE_MAGAZINE;
	else return ITEM_TYPE_BOOK;
	
}

void ItemData::fillItemInfo(string info1, string info2)
{
	int intType;
	switch (getItemType())
	{
	case ITEM_TYPE_BOOK:
		setAuthor(info1);
		setISBN(info2);
		break;
	case ITEM_TYPE_MAGAZINE:
		intType = stoi(info1);
		setEdition(intType);
		setISSN(info2);
		break;
	case ITEM_TYPE_DISC:
		intType = stoi(info1);
		setVolume(intType);
		setOwner(info2);
		break;
	}
}


string ItemData :: getImplementedDate()
{
	auto dates = getItemDate();
	return (to_string(std::get<0>(dates)) + "/" + to_string(std::get<1>(dates)) + "/" + to_string(std::get<2>(dates)));
}

string ItemData::getItemInfo1()
{
	switch (getItemType())
	{
	case ITEM_TYPE_BOOK:
		return getAuthor();
	case ITEM_TYPE_MAGAZINE:
		return to_string(getEdition());
	case ITEM_TYPE_DISC:
		return to_string(getVolume());
	}
}

string ItemData::getItemInfo2()
{
	switch (getItemType())
	{
	case ITEM_TYPE_BOOK:
		return getISBN();
		break;
	case ITEM_TYPE_MAGAZINE:
		return getISSN();
		break;
	case ITEM_TYPE_DISC:
		return getOwner();
		break;
	}
}

void getItemDatas()
{
	ifstream file;
	file.open("iDatas.txt", fstream::in);

	int uStart;
	int uSpace = 0;
	LItemType type;
	string itemCode;
	string itemTitle;
	string itemInfo1;
	string itemInfo2;
	string strInvert;
	int date;
	int typeToBe;
	int month;
	int year;
	int stock;
	string stringLine;
	if (file.fail())
	{
		cout << "File is non-existent." << endl;
	}
	else
	{
		items.clear();
		sItemCounter = 0;
		while (!file.eof()) {
			uStart = 0;

			getline(file, stringLine); cc; //stringLine will keep all string on a line in files
			if (stringLine == "")
			{
				break;
			}

			uSpace = stringLine.find('#', 0); // find the separator character
			itemCode.assign(stringLine, uStart, uSpace - uStart);//  the exact word to be copied (string, starting index, character length)

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemTitle.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;

			uSpace = stringLine.find('#', uStart);
			strInvert.assign(stringLine, uStart, uSpace - uStart);
			typeToBe = stoi(strInvert);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemInfo1.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemInfo2.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			strInvert.assign(stringLine, uStart, uSpace - uStart);
			date = stoi(strInvert);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			strInvert.assign(stringLine, uStart, uSpace - uStart);
			month = stoi(strInvert);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			strInvert.assign(stringLine, uStart, uSpace - uStart);
			year = stoi(strInvert);

			uStart = uSpace + 1;
			uSpace = stringLine.find('\0', uStart);
			strInvert.assign(stringLine, uStart, uSpace - uStart);
			stock = stoi(strInvert);

			type = itemTypeInvert(typeToBe);

			ItemData itemVector;

			itemVector.fillItemData(itemCode, itemTitle, type, date, month, year, stock);
			itemVector.fillItemInfo(itemInfo1, itemInfo2);

			items.push_back(itemVector);

			sItemCounter++;
		}

	}
	file.close();
}

void OvwItemDatas()
{
	int counter = 0;
	string type;
	string itemInfo1;
	string itemInfo2;
	ofstream myfile;
	myfile.open("iDatas.txt", fstream::trunc);
	while (counter < sItemCounter)
	{
		itemInfo1 = items[counter].getItemInfo1();
		itemInfo2 = items[counter].getItemInfo2();

		auto dates = items.at(counter).getItemDate(); 
		myfile << items.at(counter).getItemCode() << "#";
		myfile << items.at(counter).getItemTitle() << "#";
		myfile << items.at(counter).getItemType() << "#";
		myfile << itemInfo1 << "#";
		myfile << itemInfo2 << "#";
		myfile << std::get<0>(dates) << "/";
		myfile << std::get<1>(dates) << "/";
		myfile << std::get<2>(dates) << "#";
		myfile << items.at(counter).getItemStock();

		if (counter < sItemCounter)  myfile << endl;

		counter++;
	}

	myfile.close();
}

void getBorrowDatas()
{
	string stringLine;
	int uStart;
	int uSpace = 0;
	string idCode;
	string realName;
	string userAddress;
	string itemCode;
	string itemTitle;
	string itemTypeStr;
	int itemType;
	string itemInfo1;
	string itemInfo2;
	string date;
	string month;
	string year;
	string pDate;
	string pMonth;
	string pYear;

	ifstream files;
	files.open("bDatas.txt", fstream::in);
	if (files.fail())
	{
		cout << "File is non-existent." << endl;
	}
	else
	{
		borrows.clear();
		sBorCounter = 0;
		while (!files.eof()) {

			uStart = 0;

			getline(files, stringLine); cc; //stringLine will keep all string on a line in files
			if (stringLine == "")
			{
				break;
			}

			uSpace = stringLine.find('#', 0); // find the separator character
			idCode.assign(stringLine, uStart, uSpace - uStart); //  the exact word to be copied (string, starting index, character length)


			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			realName.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			userAddress.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemCode.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemTitle.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemTypeStr.assign(stringLine, uStart, uSpace - uStart);
			itemType = stoi(itemTypeStr);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemInfo1.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemInfo2.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			date.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			month.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			year.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			pDate.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			pMonth.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('\0', uStart);
			pYear.assign(stringLine, uStart, uSpace - uStart);

			BorrowData borrowVector;

			borrowVector.fillBorrowData(idCode, realName, userAddress, itemCode, itemTitle, itemInfo1, itemInfo2, itemType, stoi(pDate), stoi(pMonth), stoi(pYear));
			borrowVector.setBorrowDate(stoi(date), stoi(month), stoi(year));

			borrows.push_back(borrowVector);

			sBorCounter++;
	
		}
		files.close();
	}

}

void OvwBorrowDatas()
{
	int counter = 0;
	string type;
	ofstream myfile;
	myfile.open("bDatas.txt", fstream::trunc);
	while (counter < sBorCounter)
	{
		auto dates = borrows.at(counter).getBorrowedDate();
		auto pDates = borrows.at(counter).getItemDate();

		myfile << borrows.at(counter).getUserIdCode() << "#";
		myfile << borrows.at(counter).getUserName() << "#";
		myfile << borrows.at(counter).getUserAddress() << "#";
		myfile << borrows.at(counter).getItemCode() << "#";
		myfile << borrows.at(counter).getItemTitle() << "#";
		myfile << borrows.at(counter).getItemType() << "#";
		myfile << borrows.at(counter).getItemInfo1() << "#";
		myfile << borrows.at(counter).getItemInfo2() << "#";
		myfile << std::get<0>(dates) << "/";
		myfile << std::get<1>(dates) << "/";
		myfile << std::get<2>(dates) << "#";
		myfile << std::get<0>(pDates) << "/";
		myfile << std::get<1>(pDates) << "/";
		myfile << std::get<2>(pDates);

		if (counter < sBorCounter)  myfile << endl;

		counter++;
	}
}

void getReturnDatas()
{

	string stringLine;
	int uStart;
	int uSpace = 0;
	string idCode;
	string realName;
	string userAddress;
	string itemCode;
	string itemTitle;
	string itemTypeStr;
	int itemType;
	string itemInfo1;
	string itemInfo2;
	string date;
	string month;
	string year;
	string pDate;
	string pMonth;
	string pYear;
	string rCode;

	ifstream files;
	files.open("retDatas.txt", fstream::in);
	if (files.fail())
	{
		cout << "File is non-existent." << endl;
	}
	else
	{
		returns.clear();
		sRetCounter = 0;
		while (!files.eof()) {

			uStart = 0;

			getline(files, stringLine); cc; //stringLine will keep all string on a line in files
			if (stringLine == "")
			{
				break;
			}

			uSpace = stringLine.find('#', uStart);
			rCode.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart); // find the separator character
			idCode.assign(stringLine, uStart, uSpace - uStart); //  the exact word to be copied (string, starting index, character length)

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			realName.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			userAddress.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemCode.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemTitle.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemTypeStr.assign(stringLine, uStart, uSpace - uStart);
			itemType = stoi(itemTypeStr);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemInfo1.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			itemInfo2.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			date.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			month.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('#', uStart);
			year.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			pDate.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('/', uStart);
			pMonth.assign(stringLine, uStart, uSpace - uStart);

			uStart = uSpace + 1;
			uSpace = stringLine.find('\0', uStart);
			pYear.assign(stringLine, uStart, uSpace - uStart);

			ReturnData returnVector;

			returnVector.fillReturnData(rCode, idCode, realName, userAddress, itemCode, itemTitle, itemInfo1, itemInfo2, itemType, stoi(pDate), stoi(pMonth), stoi(pYear));
			returnVector.setBorrowDate(stoi(date), stoi(month), stoi(year));

			returns.push_back(returnVector);

			sRetCounter++;
			
		}
		files.close();
	}

}

void OvwReturnDatas()
{
	int counter = 0;
	string type;
	ofstream myfile;
	myfile.open("retDatas.txt", fstream::trunc);
	while (counter < sRetCounter)
	{
		auto dates = returns.at(counter).getBorrowedDate();
		auto pDates = returns.at(counter).getItemDate();

		myfile << returns.at(counter).getItemRCode() << "#";
		myfile << returns.at(counter).getUserIdCode() << "#";
		myfile << returns.at(counter).getUserName() << "#";
		myfile << returns.at(counter).getUserAddress() << "#";
		myfile << returns.at(counter).getItemCode() << "#";
		myfile << returns.at(counter).getItemTitle() << "#";
		myfile << returns.at(counter).getItemType() << "#";
		myfile << returns.at(counter).getItemInfo1() << "#";
		myfile << returns.at(counter).getItemInfo2() << "#";
		myfile << std::get<0>(dates) << "/";
		myfile << std::get<1>(dates) << "/";
		myfile << std::get<2>(dates) << "#";
		myfile << std::get<0>(pDates) << "/";
		myfile << std::get<1>(pDates) << "/";
		myfile << std::get<2>(pDates);

		if (counter < sRetCounter)  myfile << endl;

		counter++;
	}
}


string createRandomCode()
{
	char var[6];

		sprintf_s(var, "%c%c%d%d%d",
			rand() % 26 + 65, rand() % 26 + 65,
			rand() % 10, rand() % 10, rand() % 10);

		string rCode(var);
		return rCode;
}

int mainMenuInterface()
{
	int input;
	string strInput;

	cout << "Library App" << endl;
	cout << "==============" << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Exit" << endl;

	do
	{
		cout << " i : ";
		cin >> input; cc;
	} while (input < 1 || input > 3);

	cin.get();

	return input;
}

int getUserMatch(string query, string password)
{
	int i = 0;
	for (i; i < users.size(); i++)
	{
		if (query == users[i].getUserIDName())
			if (password == users[i].getUserPassword())
				return i;
	}
	return -1;
}

bool loginInterface()
{

	bool success = true;
	int attemptCounter;

	if (users.size() == 0)
		success = false;

	else
	{
		string userIDName;
		string password;
		cout << "Input Username : ";
		getline(cin, userIDName); cc;
		cout  << "Input Password : ";
		getline(cin, password); cc;

		int userIdx = getUserMatch(userIDName, password);
		if (userIdx == -1)
		{
			cout << endl << "Username doesn't exist/ password doesn't match with user." << endl;
			success = false;
		}
		else
		{
			thisUser = users[userIdx];
		}
	}
	return success;
}

void registerInterface()
{
	string userIDName;
	string userName;
	string userPass;
	string userAddress;
	string showCode;
	system("cls");
	cout << "Enter your real fullname : ";
	getline(cin, userName); cc; 
	cout << "Enter your address : ";
	getline(cin, userAddress); cc;
	cout << "Enter username : ";
	getline(cin, userIDName); cc;
	cout << "Enter password : ";
	getline(cin, userPass); cc;
	system("pause");

	showCode = createRandomCode();
	cout << endl << "Give admin this code : " << showCode << endl << endl;
	system("pause");
 
	RegistrationData thisRegister;
	thisRegister.fillRegData(showCode , userName, userIDName, userPass, userAddress);

	regUsers.push_back(thisRegister);
	sRegCounter++;
}

int userMenuInterface() 
{
	int input = 0;

	system("cls");
	cout << "Welcome, " << thisUser.getUserName() << "!" << endl;
	cout << "====================" << endl;
	cout << "1. Borrow" << endl;
	cout << "2. Return" << endl;
	cout << "3. View my lending info" << endl;
	cout << "4. File a complaint" << endl;
	cout << "5. Logout" << endl;

	while (input < 1 || input > 5)
	{
		cout << ">> ";
		cin >> input; cc;
	}
	return input;

}

int adminMenuInterface()
{
	int input = 0;

		cout << "Welcome, " << thisUser.getUserName() << "!" << endl;
		cout << "====================" << endl;
		cout << "1. Update item (stock)" << endl;
		cout << "2. Add item" << endl;
		cout << "3. Delete item" << endl;
		cout << "4. View library database" << endl;
		cout << "5. View ongoing lending" << endl;
		cout << "6. Confirm return" << endl;
		cout << "7. Confirm registration" << endl;
		cout << "8. Logout" << endl;

	 while (input < 1 || input > 8)
	{
		cout << ">> ";
		cin >> input; cc;
	}
	 return input;
}


void UserData ::encryptPassword()
{
	string pass = getUserPassword();
	int i = 0;
	int j;
	int fear[6] = { 7, 1, 14, 4, 8, 9 };
	while (i < pass.length())
	{
		pass[i] += fear[i % 6];
		i++;
	}
	setUserPassword(pass);
}

void UserData::decryptPassword()
{
	string pass = getUserPassword();
	int i = 0;
	int j;
	int fear[6] = { 7, 1, 14, 4, 8, 9 };
	while (i < pass.length())
	{
		pass[i] -= fear[i % 6];
		i++;
	}
	setUserPassword(pass);
}

void openedIcon()
{
	cout << "                                                        .--------." << endl;
	cout << "                                                       / .------. \ " << endl;
	cout << "                                                      / /        \ \ " << endl;
	cout << "                                                      | |        | |" << endl;
	cout << "                                          ____________| |_       | |" << endl;
	cout << "                                        .' {__}       |_| '.     |_|" << endl;
	cout << "                                        '._____ ____ _____.'" << endl;
	cout << " ad8888888ba                            |     .'____'.     |" << endl;
	cout << "8  8' `8    \"8a  ad\"ba  d\"\"b  d\"a       '.__.'.'    '.'.__.'" << endl;
	cout << "8  8   8       \"\"\"   \"\"\"    \"\"   8b     '.__  |Opened|  __.'" << endl;
	cout << "8  8, ,8    ,aaaaaaaaaaaadddddd8P       |   '.'.____.'.'   |" << endl;
	cout << " \"Y88888888\"                            '.____'.____.'____.'" << endl;
	cout << "                                        '.________________.'" << endl;
}

void lockedIcon()
{
	cout << "        .--------." << endl;
	cout << "       / .------. \ " << endl;
	cout << "      / /        \ \ " << endl;
	cout << "      | |        | |" << endl;
	cout << "     _| |________| |_" << endl;
	cout << "   .' |_|        |_| '." << endl;
	cout << "   '._____ ____ _____.'" << endl;
	cout << "   |     .'____'.     |" << endl;
	cout << "   '.__.'.'    '.'.__.'" << endl;
	cout << "   '.__  |Locked|  __.'" << endl;
	cout << "   |   '.'.____.'.'   |" << endl;
	cout << "   '.____'.____.'____.'" << endl;
	cout << "   '.________________.'" << endl << endl;
}

void lockedWoIcon()
{
	cout << "        .--------." << endl;
	cout << "       / .------. \ " << endl;
	cout << "      / /        \ \ " << endl;
	cout << "      | |        | |" << endl;
	cout << "     _| |________| |_" << endl;
	cout << "   .' |_|        |_| '." << endl;
	cout << "   '._____ ____ _____.'" << endl;
	cout << "   |     .'____'.     |" << endl;
	cout << "   '.__.'.'(```)'.'__.'" << endl;
	cout << "   '.__  |  |_|  | __.'" << endl;
	cout << "   |   '.'.____.'.'   |" << endl;
	cout << "   '.____'.____.'____.'" << endl;
	cout << "   '.________________.'" << endl << endl;
}

void LockSystem()
{
	using namespace std::chrono_literals;
	int i;
	for(i = 0; i<11; i++)
	{
		system("cls");
		if (i % 2 == 0)
			lockedIcon();
		else 
			lockedWoIcon();

			cout << "You attempted too many login tries, try again in 10 seconds." << endl;
			cout << 10 - i << " seconds remaining.";
			std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	system("cls");
	openedIcon();
	std::cout << "Unlocked!" << endl;
	system("pause");
}

int  fineCharge(int idx)
{
	int bDate;
	int fine = -1;
	bDate = returns[idx].getCalculatedDate();
	if (bDate > 14)
	{
		fine = (bDate - 14) * 1;
	}
	return fine;
} 

void RegisterUserToDatabase(int index)
{
	UserData newUser;
	newUser.fillUserData(createRandomCode(), regUsers[index].getUserName(), regUsers[index].getUserIDName(), regUsers[index].getUserPassword(), regUsers[index].getUserAddress(), false);
	users.push_back(newUser);
	sUserCounter++;

	regUsers.erase(regUsers.begin() + index);
	sRegCounter--;
}

bool searchItem(string input)
{
	bool success = false;
	bool found = true;
	int inputLength = input.size();
	int i, j, k;
	string itemString;
	int start = 0;
	int space = 0;
	int length = 0;
	bool flag = false;
	bool endLoop = false;
	indexKeeper.clear();
	int strLength;

	for (i = 0; i < items.size(); i++)
	{
		itemString = items[i].getItemTitle();
		length = items[i].getItemTitle().size();
		found = true;
		start = 0;
		strLength = input.size();
		endLoop = false;
		flag = false;

		space = itemString.find(' ', 0);
		if (space == string::npos)
			space = length;

		while (!endLoop)
		{
			found = true;

			for (j = start, k = 0; j < start+strLength, k < strLength; j++, k++)
			{
				if (itemString[j] != input[k])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				indexKeeper.push_back(i);
				success = true;
				break;
			}
			else
			{
				space = itemString.find(' ', start);
			}
			if (flag)
				endLoop = true;
			if (space == string::npos)
			{
				space = length;
				flag = true;
			}
			else
				start = space + 1;
		}
	}
	return success;
}

int showSearchResult()
{

	int i;
	int input;
	system("cls");
	cout << "No. | Title | Type | Info | Info | Date Published | Stock" << endl;
	cout << "---------------------------------------------------------" << endl;
	for (i = 0; i < indexKeeper.size(); i++)
	{
		cout << i + 1<< " |" << items[indexKeeper[i]].getItemTitle() << "|" << items[indexKeeper[i]].getItemTypeDef() << "|" << items[indexKeeper[i]].getItemInfo1() << "|" << items[indexKeeper[i]].getItemInfo2() << "|" << items[indexKeeper[i]].getImplementedDate() << "|" << items[indexKeeper[i]].getItemStock() << endl;
	}
	cout << endl <<"==============================================" << endl;
	do {
		cout << "Number Input [0 to cancel] : ";
		cin >> input; cc;
	} while (input < 0 || input > indexKeeper.size());
	return input-1;
}

bool eraseLendingData(int retIndex)
{
	string itemCode;
	int i = 0;
	int borIndex;
	int itemIndex;
	bool found = false;

	itemCode = returns[retIndex].getItemCode();

	for (i = 0; i < borrows.size(); i++)
	{
		if (borrows[i].getItemCode() == itemCode)
		{
			found = true;
			borIndex = i;
			break;
		}
	}
	if (!found)
	{
		cout << "System failed to return, data from borrow database not found";
		return found;
	}
	else
	{

	found = false;
	for (i = 0; i < items.size(); i++)
	{
		if (items[i].getItemCode() == itemCode)
		{
			found = true;
			itemIndex = i;
			break;
		}
	}
	if (!found)
	{
		auto itemDate = returns[retIndex].getItemDate();
		thisItem.fillItemData(itemCode, returns[retIndex].getItemTitle(), itemTypeInvert(returns[retIndex].getItemType()), get<0>(itemDate), get<1>(itemDate), get<2>(itemDate), 1);
		thisItem.fillItemInfo(returns[retIndex].getItemInfo1(), returns[retIndex].getItemInfo2());
		items.push_back(thisItem);
		sItemCounter++;
		found = true;
	}
	else
	{
		items[i].setItemStock(items[i].getItemStock() + 1);
	}

	borrows.erase(borrows.begin() + borIndex);
	sBorCounter--;
	returns.erase(returns.begin() + retIndex);
	sRetCounter--;
	}
	return found;
}


void updateStock()
{
	string input;
	int mainInput;
	int i = 0;
	bool change = false;

	system("cls");
	cout << "Update stock" << endl;

	cout << "=============" << endl;
	do
	{
		cout << "Input book's title" << endl;
		cout << ">> ";
		getline(cin, input); cc;
	} while (input.length() < 2);
	if (!searchItem(input))
	{
		cout << "Item not found.";
		system("pause");
	}
	else
	{
		mainInput = showSearchResult();

		if (mainInput == -1)
		{
			system("pause");
		}
		else
		{
			change = true;
			do
			{
				cout << endl;
				cout << items[indexKeeper[mainInput]].getItemTitle() << "'s current stock : " << items[indexKeeper[mainInput]].getItemStock() << endl;
				cout << "Input item's current stock quantity [-2] to cancel: ";
				cin >> i; cin.clear(); cin.sync();

				if (i == -2)
				{
					change = false;
					break;
				}

				cin.get();
				cout << endl;
				cout << "Are you sure you want to change? [Y/N] :";
				getline(cin, input); cc;
			} while (input != "y" && input != "Y");
			if (change)
			{
				items[indexKeeper[mainInput]].setItemStock(i);
			}
		}
	}
}

void addItem()
{
	string title;
	string type;
	string info1;
	string info2;
	string confirm;
	int date;
	int month;
	int year;
	int stock;

	cout << "Add item" << endl;
	cout << "=============" << endl;
	cout << "Enter item's title : ";
	getline(cin, title); cc;

	do
	{
		cout << "Enter item's type [book/magazine/disc] : ";
		getline(cin, type); cc;
	} while (type != "book" && type != "magazine" && type != "disc");

	if (type == "disc")
	{
		do
		{
			cout << "Enter item's volume : ";
			getline(cin, info1); cc;
		} while (stoi(info1) < 1);

		cout << "Enter item's owner : ";
		getline(cin, info2); cc;
	}
	else if (type == "magazine")
	{
		do {
			cout << "Enter item's edition : ";
			getline(cin, info1); cc;
		} while (stoi(info1) < 1);
		
		do
		{
			cout << "Enter item's ISSN : ";
			getline(cin, info2); cc;
		} while (info2.length() != 10);
	}
	else
	{
		do {
			cout << "Enter item's Author : ";
			getline(cin, info1); cc;
		} while (info1.length() < 3);

		do
		{
			cout << "Enter item's ISBN : ";
			getline(cin, info2); cc;
		} while (info2.length() != 10);
	}

	do
	{
		cout << "Enter item's published date : ";
		cin >> date; cc;
	} while (date < 1 || date > 31);

	do
	{
		cout << "Enter item's published month : ";
		cin >> month; cc;
	} while (month < 1 || month > 12);

	do
	{
		cout << "Enter item's published year : ";
		cin >> year; cc;
	} while (year<1900 || year>2018);

	do
	{
		cout << "Enter item's stock : ";
		cin >> stock; cc;
	} while (stock < 0);

	cout << endl << "Item's title : " << title << endl;
	cout << "Item's type : " << type << endl;
	cout << "Item's info : " << info1 << endl;
	cout << "Item's other info : " << info2 << endl;
	cout << "Item's published date : " << date << "/" << month << "/" << year << endl;
	cout << "Item's stock : " << stock << endl << endl;
	cin.get();
	do {
		cout << "continue? [Y/N] : ";
		getline(cin, confirm);
	} while (confirm != "Y" && confirm != "N");

	if (confirm == "Y") {
		thisItem.fillItemData(createRandomCode(), title, itemTypeInvert(type), date, month, year, stock);
		thisItem.fillItemInfo(info1, info2);
		items.push_back(thisItem);
		sItemCounter++;
	}
}

void deleteItem()
{
	int result;
	string confirm;
	string strInput;
	cout << "Delete item" << endl;
	cout << "=============" << endl;
	do
	{
		cout << "Enter item's title you want to delete : ";
		getline(cin, strInput); cc;
	} while (strInput.length() < 2);

	if (!searchItem(strInput))
	{
		cout << "Item's not found.";
		system("pause");
	}
	else
	{
		result = showSearchResult();
			if (result == -1)
			{
				system("pause");
			}
			else
			{
				system("cls");
				cout << "Item's title : " << items[indexKeeper[result]].getItemTitle() << endl;
				cout << "Item's type : " << items[indexKeeper[result]].getItemTypeDef() << endl;
				cout << "Item's info : " << items[indexKeeper[result]].getItemInfo1() << endl;
				cout << "Item's other info : " << items[indexKeeper[result]].getItemInfo2() << endl;
				cout << "Item's published date : " << items[indexKeeper[result]].getImplementedDate() << endl;
				cout << "Item's stock : " << items[indexKeeper[result]].getItemStock() << endl << endl;

				cin.get();
				do {
					cout << "Delete this item? [Y/N] : ";
					getline(cin, confirm);
				} while (confirm != "Y" && confirm != "N");

				if (confirm == "Y") {
					items.erase(items.begin()+indexKeeper[result]);
					sItemCounter--;
				}
			}
	}

}

void listItem()
{
	int i = 0;

	cout << "View Library Database" << endl;
	cout << "=============" << endl;
	cout << "No. | Title | Type | Info | Info | Date Published | Stock" << endl;
	cout << "---------------------------------------------------------" << endl;
	for (i = 0; i < items.size(); i++)
	{
		cout << i+1 << "|"<<  items[i].getItemTitle() << "|" << items[i].getItemTypeDef() << "|" << items[i].getItemInfo1() << "|" << items[i].getItemInfo2() << "|"  << items[i].getImplementedDate() << "|" << items[i].getItemStock() << endl;
	}
	cout << endl << "==============================================" << endl;
	system("pause");
	
}

void viewLenders()
{
	int i = 0;
	cout << "View ongoing lendings" << endl;
	cout << "=============" << endl;
	cout << "Item Code | Item Title | Item Type | User Code | User Name | User Address | Date Borrowed" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (i = 0; i < borrows.size(); i++)
	{
		cout << borrows[i].getItemCode() << "|" << borrows[i].getItemTitle() << "|" << borrows[i].getItemType() << "|" << borrows[i].getUserIdCode() << "|" << borrows[i].getUserName() << "|" << borrows[i].getUserAddress() << "|" << borrows[i].getImplementedBorrowedDate() << endl;
	}
	cout << "-----------------------------------------------------------------------------------------" << endl;
	system("pause");
}

void confirmReturn()
{
	string code;
	string confirm;
	bool found = false;
	int fine = 0;
	int i = 0;
	cout << "Confirm Return" << endl;
	cout << "=============" << endl;
	cout << "Input Return Code : ";
	getline(cin, code); cc;

	for (i = 0; i < returns.size(); i++)
	{
		if (returns[i].getItemRCode() == code)
			found = true;
			break;
	}
	if (!found)
	{
		cout << "Data does not exist/ code not found.";
		system("pause");
		
	}
	else
	{
		cout << "Item Code : " << returns[i].getItemCode() << endl;
		cout << "Item Title : " << returns[i].getItemTitle() << endl;
		cout << "Item Type : " << returns[i].getItemTypeDef() << endl;
		cout << "User Code : " << returns[i].getUserIdCode() << endl;
		cout << "User Name : " << returns[i].getUserName() << endl;
		cout << "User Address : " << returns[i].getUserAddress() << endl;
		cout << "Date Borrowed : " << returns[i].getImplementedBorrowedDate() << endl << endl;

		do {
			cout << "Confirm? [Y/N] : ";
			getline(cin, confirm); cc;
		} while (confirm != "Y" && confirm != "N");
		if (confirm == "N")
		{
			system("pause");
		}
		else
		{
			fine = fineCharge(i);
			if (!eraseLendingData(i))
			{
				cout << "Returning item failed, please hold book and contact nearest IT." << endl;;
				system("pause");
			}
			else
			{
				cout << "Return success!" << endl;
				if (fine == -1)
				{
					cout << "Book returned in time." << endl;
				}
				else
				{
					cout << "Fine : " << fine << endl;
				}
				system("pause");
			}
		}
	}
}

void confirmRegistration()
{
	string code;
	string confirm;
	bool found = false;
	int i = 0;
	cout << "Confirm Registration" << endl;
	cout << "=============" << endl;
	cout << "Input Register Code : ";
	getline(cin, code); cc;

	for (i = 0; i < regUsers.size(); i++)
	{
		if (regUsers[i].getUserRCode() == code)
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "Data does not exist/ code not found.";
		system("pause");
	}
	else
	{

		cout << endl << " Name : "<< regUsers[i].getUserName() << endl;
		cout << " Address : " << regUsers[i].getUserAddress() << endl << endl;
		do {
			cout << "Confirm? [Y/N] : ";
			getline(cin, confirm); cc;
		} while (confirm != "Y" && confirm != "N");
		if (confirm == "N")
		{
			system("pause");
		}
		else
		{
			RegisterUserToDatabase(i);

			cout << "Register user successful!" << endl;
			system("pause");
		}

	}

}

bool checkBook(int idx)
{
	bool success = true;
	if (0 == items[idx].getItemStock())
	{
		success = false;
	}
	return success;
}

void processBorrow(int idx)
{
	time_t now;
	time(&now);
	tm * today = localtime(&now);
	items[idx].setItemStock(items[idx].getItemStock() - 1);

	BorrowData thisBorrow;
	auto pDates = items[idx].getItemDate();
	auto bDates = getTodaysDate();
	thisBorrow.fillBorrowData(thisUser.getUserIdCode(), thisUser.getUserName(), thisUser.getUserAddress(), items[idx].getItemCode(), items[idx].getItemTitle(), items[idx].getItemInfo1(), items[idx].getItemInfo2(), items[idx].getItemType(), get<0>(pDates), get<1>(pDates), get<2>(pDates));
	thisBorrow.setBorrowDate(get<0>(bDates), get<1>(bDates), get<2>(bDates));

	borrows.push_back(thisBorrow);
	sBorCounter++;
}

void borrowItem()
{
	string input;
	int index;
	int number;
	system("cls");
	cout << "Borrow/Lend" << endl;
	cout << "=============" << endl;
	do
	{
		cout << "Input book you're trying to borrow." << endl;
		cout << ">> ";
		getline(cin, input); cc;
	} while (input.length() < 2);
	if (!searchItem(input))
	{
		cout << "Item's not found.";
		system("pause");
	}
	else
	{
		
		index = showSearchResult();

		if (index == -1)
		{
			system("pause");
		}
		else
		{
			do {

				if (index == -1)
				{
					system("pause");
				}
				else
				{
					if (!checkBook(indexKeeper[index]))
					{
						cout << "Book stock's empty, borrowing process failed, please contact librarian." << endl;
						system("pause");
					}
					else
					{
						cin.get();
						do
						{
							cout << "Confirm? [Y/N] : ";
							getline(cin, input); cc;
						} while (input != "Y" && input != "N");

						if (input == "Y")
						{
							processBorrow(indexKeeper[index]);
							cout << "Borrow successful." << endl;
							system("pause");
						}
					}
				}
			} while (input == "N");
		}
		

	}
}


int viewLendingInfo()
{
	bool found = false;
	indexKeeper.clear();
	int i = 0;
	for (i = 0; i < borrows.size(); i++)
	{
		if (borrows[i].getUserIdCode() == thisUser.getUserIdCode())
		{
			indexKeeper.push_back(i);
			found = true;
		}
	}
	return found;
}


bool lendInfo()
{
	int idx;
	bool success= true;
	int counter = 0;
	if (!viewLendingInfo())
	{
		cout << "You have not borrowed anything." << endl;
		system("pause");
		success = false;
	}
	else
	{
		cout << "You have borrowed : " << endl;
		while (counter < indexKeeper.size())
		{
			idx = indexKeeper[counter];

			cout << counter+1 <<". "<< borrows[idx].getItemTitle() << " " << borrows[idx].getItemTypeDef() << " " << borrows[idx].getItemInfo1() << " " << borrows[idx].getItemCode() << ", Borrowed at : " << borrows[idx].getImplementedBorrowedDate()  << endl;
		
			counter++;
		}
	}
	return success;
}

void returnItem()
{
	int input;
	string code;
	int size = indexKeeper.size();
	int idx;
	system("cls");
	cout << "Return" << endl;
	cout << "=============" << endl;

	if (!lendInfo())
	{

	}
	else
	{
		do
		{
			cout << "Input number [0] to cancel: ";
			cin >> input; cc;
			input--;
		} while (input < -1 || input > size);

		if (input == -1)
		{
			system("pause");
		}
		else
		{
			ReturnData thisReturn;
			code = createRandomCode();
			auto pDates = borrows[indexKeeper[input]].getItemDate();
			auto dates = borrows[indexKeeper[input]].getBorrowedDate();
			thisReturn.fillReturnData(code, borrows[indexKeeper[input]].getUserAddress(), borrows[indexKeeper[input]].getUserName(), borrows[indexKeeper[input]].getUserAddress(), borrows[indexKeeper[input]].getItemCode(), borrows[indexKeeper[input]].getItemTitle(), borrows[indexKeeper[input]].getItemInfo1(), borrows[indexKeeper[input]].getItemInfo2(), borrows[indexKeeper[input]].getItemType(), get<0>(pDates), get<1>(pDates), get<2>(pDates));
			thisReturn.setBorrowDate(get<0>(dates), get<1>(dates), get<2>(dates));

			returns.push_back(thisReturn);
			sRetCounter++;

			cout << endl << "Please show this code : " << code << " to the librarian to confirm your book's return." << endl;
			system("pause");
		}
	}
}

void viewMyLendings()
{

	system("cls");
	cout << "View my lending info" << endl;
	cout << "=============" << endl;
	lendInfo();

	system("pause");
}

void fileComplaint()
{

}


int main(int argc, char* args[])
{
	srand(time(NULL));

	int mainInput = 0;
	string input;
	int idx = -1;
	int lockCounter = 0;
	int i = 0;
	bool change;
	int attemptCounter = 0;	

	do
	{
		system("cls");
		mainInput = mainMenuInterface();
		switch (mainInput)
		{
		case 1:

			getUserDatas();

			system("cls");
			if (!loginInterface())
			{
				cout << "Failed to login." << endl;
				lockCounter++;
				if (lockCounter == 5)
				{
					LockSystem();
					lockCounter = 0;
				}
				else
					system("pause");
			}
			else
			{
				if (thisUser.getUserType())
				{
					do {
						system("cls");
						mainInput = adminMenuInterface();
						cin.get();
						cout << endl;
						switch (mainInput)
						{
						case 1: // update items stock
							getItemDatas();
							updateStock();
							OvwItemDatas();
							break;
						case 2: // add item
							getItemDatas();
							addItem();
							OvwItemDatas();
							break;
						case 3: // delete item
							getItemDatas();
							deleteItem();
							OvwItemDatas();
							break;
						case 4: // view all items
							getItemDatas();
							listItem();
							break;
						case 5: // view all lend
							getBorrowDatas();
							viewLenders();
							break;
						case 6: // confirm return
							getReturnDatas();
							confirmReturn();
							OvwReturnDatas();
							OvwBorrowDatas();
							OvwItemDatas();
							break;
						case 7: // confirm reg
							getRegDatas();
							confirmRegistration();
							OvwRegDatas();
							OvwUserDatas();
							break;
						}
					} while (mainInput != 8);
				}
				else
				{
					do {
						mainInput = userMenuInterface();
						cin.get();
						switch (mainInput)
						{
						case 1: //borrow
							getItemDatas();
							getBorrowDatas();
							borrowItem();
							OvwItemDatas();
							OvwBorrowDatas();
							break;
						case 2: // return
							getBorrowDatas();
							returnItem();
							OvwReturnDatas();
							break;
						case 3: // view lending info
							getBorrowDatas();
							viewMyLendings();
							break;
						case 4: // file complaint
							string lol;
							cout << "File a complaint" << endl;
							cout << "================" << endl;
							cout << ">>";
							getline(cin, lol);

							cout << "Thank you for your feedback." << endl;
							system("pause");
							break;
						}
					} while (mainInput != 5);
				}
			}

			break;
		case 2:
			getRegDatas();
			registerInterface();
			OvwRegDatas();
			break;
		}
	} while (mainInput != 3);
	
	return 0;
}
