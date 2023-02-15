package Contact;
import java.util.ArrayList;
import java.util.List;

public class contact {
	
	private static List<String> ContactIds = new ArrayList<String> ();
	private String contactId;
	private String firstName;
	private String lastName;
	private String phone;
	private String address;
			
	public contact (String contactId, String firstName, String lastName, String phone, String address){
		this.setContactId(contactId);
		this.setFirstName(firstName);
		this.setLastName(lastName);
		this.setPhone(phone);
		this.setAddress(address);
	}	


	public String getContactId() {
		return contactId;
	}

	private void setContactId (String contactId) {
	
		if (this.contactId != null && contactId.length() != 0) {
			throw new RuntimeException("Contact ID is not updateable.");
		}
	
		else if (ContactIds.contains(contactId)) {
			throw new RuntimeException("Contact ID " + contactId + " is unavailable.");
		}
	
		else if (contactId == null || contactId.length() == 0) {
			throw new RuntimeException("Contact ID can not be empty");
		}
		
		else if (contactId.length() > 10) {
			throw new RuntimeException("Contact ID " + contactId + " is too long. Must be 10 characters or less.");
		}
		
		else {
			this.contactId = contactId;
		}
	}
	
	public String getFirstName() {
		return firstName;
	}
	
	public void setFirstName (String firstName) {
		
		if (firstName == null || firstName.length() == 0) {
			throw new RuntimeException("First Name can not be empty.");
		}
		
		else if (firstName.length() > 10) {
			throw new RuntimeException ("First Name " + firstName + " is too long. Must be 10 characters or less.");
		}
		
		else {
			this.firstName = firstName;
		}
	}
	
	public String getLastName() {
		return lastName;
	}
	
	public void setLastName (String lastName) {
		
		if (lastName == null || lastName.length() == 0) {
			throw new RuntimeException("Last Name can not be empty.");
		}
		
		else if (lastName.length() > 10) {
			throw new RuntimeException ("Last Name " + lastName + " is too long. Must be 10 characters or less.");
		}
		
		else {
			this.lastName = lastName;
		}
	}
	
	public String getPhone () {
		return phone;
	}
	
	public void setPhone (String phone) {
		
		if (phone == null || phone.length() == 0) {
			throw new RuntimeException("Phone Number can not be empty.");
		}
		
		else if (phone.length() != 10 || !isNumeric(phone)) {
			throw new RuntimeException ("Phone Number must be 10 digits");
		}
		
		else {
			this.phone = phone;
		}
	}
	
	public String getAddress () {
		return address;
	}
	
	public void setAddress (String address){
		
		if (address == null || address.length() == 0) {
			throw new RuntimeException("Address can not be empty.");
		}
		
		else if ( address.length() > 30) {
			throw new RuntimeException("Address " + address + " is too long. Must be 30 characters or less.");
		}
		
		else {
			this.address = address;
		}
	}
	
	private static boolean isNumeric(String str) {
		try {
			Long.parseLong(str);
			return true;
		}
		catch (NumberFormatException e) {
			return false;
		}
	}
	public void add(contact contact) {
		// TODO Auto-generated method stub
		
	}


	public void remove(contact contact) {
		// TODO Auto-generated method stub
		
	}
}	