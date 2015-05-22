#ifndef IDENTITY_DOCUMENT_H
#define IDENTITY_DOCUMENT_H

#include <iostream>

using namespace std;
namespace ip
{

class IdentityDocument{
	string mId;
	string mCheckId;
	string mType;
	string mCountry;
	string mSurnames;
	string mGivenNames;
	string mSex;
	string mNationality;
	string mDateBirth;
	string mCheckBirth;
	string mPlaceBirth;
	string mDateIssue;
	string mDateExpiry;
	string mCheckExpiry;
	string mOptionalData;
	string mCheckOptional;
	string mCheckOverall;

public:

	IdentityDocument();

	string getId(){return mId;};
	void setId(string id){mId = id;};

	string getCheckId(){return mCheckId;};
	void setCheckId(string checkId){mCheckId = checkId;};

	string getType(){return mType;};
	void setType(string type){mType = type;};

	string getCountry(){return mCountry;};
	void setCountry(string country){mCountry = country;};

	string getSurnames(){return mSurnames;};
	void setSurnames(string surnames){mSurnames = surnames;};

	string getGivenNames(){return mGivenNames;};
	void setGivenNames(string givenNames){mGivenNames = givenNames;};

	string getSex(){return mSex;};
	void setSex(string sex){mSex = sex;};

	string getNationality(){return mNationality;};
	void setNationality(string nationality){mNationality = nationality;};

	string getDateBirth(){return mDateBirth;};
	void setDateBirth(string dateBirth){mDateBirth = dateBirth;};

	string getCheckBirth(){return mCheckBirth;};
	void setCheckBirth(string checkBirth){mCheckBirth = checkBirth;};

	string getPlaceBirth(){return mPlaceBirth;};
	void setPlaceBirth(string placeBirth){mPlaceBirth = placeBirth;};

	string getDateIssue(){return mDateIssue;};
	void setDateIssue(string dateIssue){mDateIssue = dateIssue;};

	string getDateExpiry(){return mDateExpiry;};
	void setDateExpiry(string dateExpiry){mDateExpiry = dateExpiry;};

	string getCheckExpiry(){return mCheckExpiry;};
	void setCheckExpiry(string checkExpiry){mCheckExpiry = checkExpiry;};

	string getOptionalData(){return mOptionalData;};
	void setOptionalData(string optionalData){mOptionalData = optionalData;};

	string getCheckOptional(){return mCheckOptional;};
	void setCheckOptional(string checkOptional){mCheckOptional = checkOptional;};

	string getCheckOverall(){return mCheckOverall;};
	void setCheckOverall(string checkOverall){mCheckOverall = checkOverall;};
};

} // Namespace ip

#endif