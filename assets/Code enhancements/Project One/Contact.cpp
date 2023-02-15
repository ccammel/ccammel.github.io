#include <iostream>
#include <vector>
#include <string>

#include "Contact.h"

class Contact {
    // Create classes for Contacts including ID, First & Last Name, Phone, and Address
private:
    static std::vector<std::string> ContactIds;
    std::string contactId;
    std::string firstName;
    std::string lastName;
    std::string phone;
    std::string address;

public: // Allows editing of individual strings	
    Contact(std::string contactId, std::string firstName, std::string lastName, std::string phone, std::string address) {
        setContactId(contactId);
        setFirstName(firstName);
        setLastName(lastName);
        setPhone(phone);
        setAddress(address);
    }
    // Grabs Contact ID Number
    std::string getContactId() {
        return contactId;
    }
    void setContactId(std::string contactId) {
        // If / Else If / Else Loop to set Contact IDs, including error throws
        if (this->contactId != "" && contactId.length() != 0) {
            throw std::runtime_error("Contact ID is not updateable.");
        }
        else if (std::find(ContactIds.begin(), ContactIds.end(), contactId) != ContactIds.end()) {
            throw std::runtime_error("Contact ID " + contactId + " is unavailable.");
        }
        else if (contactId == "" || contactId.length() == 0) {
            throw std::runtime_error("Contact ID can not be empty");
        }
        else if (contactId.length() > 10) {
            throw std::runtime_error("Contact ID " + contactId + " is too long. Must be 10 characters or less.");
        }
        else {
            this->contactId = contactId;
        }
    }
    // Grabs First Name
    std::string getFirstName() {
        return firstName;
    }
    void setFirstName(std::string firstName) {
        // If / Else If / Else Loop to set First Name, including error throws
        if (firstName == "" || firstName.length() == 0) {
            throw std::runtime_error("First Name can not be empty.");
        }
        else if (firstName.length() > 10) {
            throw std::runtime_error("First Name " + firstName + " is too long. Must be 10 characters or less.");
        }
        else {
            this->firstName = firstName;
        }
    }
    // Grabs Last Name
    std::string getLastName() {
        return lastName;
    }
    void setLastName(std::string lastName) {
        // If / Else If / Else Loop to set Last Name, including error throws
        if (lastName == "" || lastName.length() == 0) {
            throw std::runtime_error("Last Name can not be empty.");
        }
        else if (lastName.length() > 10) {
            throw std::runtime_error("Last Name " + lastName + " is too long. Must be 10 characters or less.");
        }
        else {
            this->lastName = lastName;
        }
    }
    // Grabs Phone Number
    std::string getPhone() {
        return phone;
    }
    void setPhone(std::string phone) {
        // If / Else If / Else Loop to set Phone Number, including error throws
        if (phone == "" || phone.length() == 0) {
            throw std::runtime_error("Phone Number can not be empty.");
        }
        else if (phone.length() != 10 || isNumeric(phone)) {
            throw std::runtime_error("Phone Number must be 10 digits");
        }
        else {
            this->phone = phone;
        }
    }
    // Grabs Address
    std::string getAddress() {
        return address;
    }
    void setAddress(std::string address) {
        // If / Else If / Else Loop to set Address, including error throws
        if (address == "" || address.length() == 0) {
            throw std::runtime_error("Address can not be empty.");
        }
        else if (address.length() > 30) {
            throw std::runtime_error("Address " + address + " is too long. Must be 30 characters or less.");
        }
        else {
            this->address = address;
        }
    }
    // Try / Catch loop to determine if strings are numeric where needed.
    private:
        static bool isNumeric(std::string str) {
            try {
                std::stol(str);
                return true;
            }
            catch (std::invalid_argument) {
                return false;
            }
        }
};