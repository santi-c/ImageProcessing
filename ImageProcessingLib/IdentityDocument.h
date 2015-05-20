#ifndef IDENTITY_DOCUMENT_H
#define IDENTITY_DOCUMENT_H

#include <stdio.h>
#include <iostream>

using namespace std;

class IdentityDocument{
	string id;
	string checkId;
	string type;
	string country;
	string surnames;
	string givenNames;
	string sex;
	string nationality;
	string dateBirth;
	string checkBirth;
	string placeBirth;
	string dateIssue;
	string dateExpiry;
	string checkExpiry;
	string optionalData;
	string checkOptional;

public:
	string getId(){return id;};
	void setId(string mId){id = mId;};

	string getCheckId(){return checkId;};
	void setCheckId(string mCheckId){checkId = mCheckId;};

	string getType(){return type;};
	void setType(string mType){type = mType;};

	string getCountry(){return country;};
	void setCountry(string mCountry){country = mCountry;};

	string getSurnames(){return surnames;};
	void setSurnames(string mSurnames){surnames = mSurnames;};

	string getGivenNames(){return givenNames;};
	void setGivenNames(string mGivenNames){givenNames = mGivenNames;};

	string getSex(){return sex;};
	void setSex(string mSex){sex = mSex;};

	string getNationality(){return nationality;};
	void setNationality(string mNationality){nationality = mNationality;};

	string getDateBirth(){return dateBirth;};
	void setDateBirth(string mDateBirth){dateBirth = mDateBirth;};

	string getCheckBirth(){return checkBirth;};
	void setCheckBirth(string mCheckBirth){checkBirth = mCheckBirth;};

	string getPlaceBirth(){return placeBirth;};
	void setPlaceBirth(string mPlaceBirth){placeBirth = mPlaceBirth;};

	string getDateIssue(){return dateIssue;};
	void setDateIssue(string mDateIssue){dateIssue = mDateIssue;};

	string getDateExpiry(){return dateExpiry;};
	void setDateExpiry(string mDateExpiry){dateExpiry = mDateExpiry;};

	string getCheckExpiry(){return checkExpiry;};
	void setCheckExpiry(string mCheckExpiry){checkExpiry = mCheckExpiry;};

	string getOptionalData(){return optionalData;};
	void setOptionalData(string mOptionalData){optionalData = mOptionalData;};

	string getCheckOptional(){return checkOptional;};
	void setCheckOptional(string mCheckOptional){checkOptional = mCheckOptional;};
};

#endif