/* Ticket_Master

 NAME: Kate Walley
 DATTE: May 14, 2021

 PURPOSE: This program simulates a ticket selling program like ticket master. 
 This program has the user input the number of rows/columns and the price 
 they want to assign to each row.The program can also print out the venue with 
 the seats if they are sold or unsold if they are unsold the price of the seat. 
 This program also allows a user to purchase tickets. It is also possible to print out different stats 
 about the venue and the seats. The user can also save and load the file with the venue in it.
 */


#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
using namespace std;

//Globals
enum status {sold, unsold};			//Tracks if a seat is either sold or unsold

struct seat {									//Structure to track each seat in the venu
	status seat_status;					//Keeps track if the seat is sold yet
	int price;										//Price of the ticket
};

struct venue {									//The venue the tickets are being sold for		
	int rows;										//Number of rows in the venue (up to 10 rows)
	int columns;								//Number of columns in the venue (up to 10 columns)
	seat seats[10][10];					//Venue size up to 10x10 (it will be a rectangle always)
	int rowprices[10];						//Price for the ticket in each row
	bool open;									//Ensures there is a venue for the user to buy from
};

//Prototypes
void input(venue & myvenue);					//Tracks the input of the venue size (rows/columns) and the price for tickets in different rows
void print(venue myvenue);						//Prints the venue with sold/unsold seats and prices for unsold seats
void sell_tickets(venue & myvenue);		//Gets the number of tickets the user wants, give out the ticket prices for avabile rows, then it looks for consecutive seats in the price range
void venue_stats(venue myvenue);			//Prints out information about the venue and the stats about sold/unsold seats
void save(venue myvenue);						//Saves the current venue in a file so it can be used again later
void load(venue & myvenues);					//Loads a previously saved venu so it can continue to be used

int main(void)
{
	char choice;					//Menu choice the user makes
	venue myvenue;				//Overall venue tracks
	int i, j;								//Loop counter

	//Set seats to not sold
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10;j++)
		{
			myvenue.seats[i][j].seat_status = unsold;
		}//for
	}//for

	//Set to false to ensure that a user can't do some actions without a loaded venue
	myvenue.open = false;

	//Print out a message to show the user what they are using
	cout << "Ticket-Master: Your go to place for buying tickets to events!" << endl;
	do
	{
		//Give the user options on what they can do 
		cout << "What do you want to do:"<<endl;
		cout<<"(I)nput data, (P)rint out venue info, (B)uy tickets, (S)ave venue, (L)oad venue, (V)enue stats print, or e(X)it? ";
		choice = toupper(_getwche());
		cout << endl;
		//Validate the choice
		while (choice != 'I' && choice != 'P' && choice != 'B' && choice != 'S' && choice != 'L' && choice != 'X' && choice !='V')
		{
			cout<<"INVALID ENTRY!"<<endl;
			cout<<"(I)nput data, (P)rint out venue info, (B)uy tickets, (S)ave venue, (L)oad venue, (V)enue stats print, or e(X)it. ";
			choice = toupper(_getwche());
			cout << endl;
		}//while
		//Switch baised off choice the user makes
		switch (choice)
		{
			case 'I':input(myvenue); break;
			case 'P':print(myvenue); break;
			case  'B':sell_tickets(myvenue); break;
			case 'V': venue_stats(myvenue);break;
			case 'S':save(myvenue); break;
			case 'L':load(myvenue); break;
		}//switch
		//Keep going until the user says they want to exit
	} while (choice != 'X');
	//Print leaving message
	cout << "Thank you for using Ticket-Master. " << endl;
	return 0;
}//Main

/* input - This method tracks the input of the venu size (rows/columns) and the price for tickets in different rows.
   The parameter myvenue tracks the overall venue.
*/
void input(venue & myvenue)
{
	int number_rows;							//Number of rows 
	int number_seats_row;					//The number of seats per row
	int i;													//Loop counter
	int price;											//The price to assign to a row

	//Get the number of rows the user wants
	cout << "How many rows of seats do you want? (Max 10 rows) : ";
	cin >> number_rows;
	//Validate
	while (number_rows <= 0 || number_rows > 10)
	{
		cout << "INVALID! Please enter a number from 1-10: ";
		cin >> number_rows;
	}//while
	myvenue.rows = number_rows;

	//Get the number of seats the user wants
	cout << "How many seats do you want in each row? (Max 10 seats) : ";
	cin >> number_seats_row;
	//Validate
	while (number_seats_row <= 0 || number_seats_row > 10)
	{
		cout << "INVALID! Please enter a number from 1-10: ";
		cin >> number_seats_row;
	}//while
	myvenue.columns = number_seats_row;

	//Price the tickets for each row
	for (i = 0; i < number_rows; i++)
	{
		cout << "What price do you want to make Row " << (i + 1) << " ? (Must be at least $10 and less than $100): $";
		cin >> price;
		//Validate the price
		while (price < 10 || price > 99)
		{
			cout << "INVALID! Please enter a price that is at least $10 and less than $100: $";
			cin >> price;
		}//while
		myvenue.rowprices[i] = price;
	}//for
	myvenue.open = true;
}//inpu

/* print - This method prints the venue with sold/unsold seats and prices for unsold seats.
   The parameter myvenue will track the overall venue.
*/
void print(venue myvenue)
{
	int i, j;				//Loop counters

	if (myvenue.open == true)
	{
		cout << "Here is the current venue (not sold in green, sold in red, and the dollar amount of the ticket is listed on the seat): " << endl;

		//Print out column numbers
		for (i = 0; i < myvenue.columns; i++)
		{
			cout << "    " << i + 1;
		}//for
		cout << endl;
		//Print out the status of the seats
		for (i = 0; i < myvenue.rows; i++)
		{
			if (i != 9)
			{
				cout << " " << i + 1;
			}//if
			else
			{
				cout << i + 1;
			}//else
			for (j = 0; j < myvenue.columns; j++)
			{
				//Print out the unsold seats and their price
				if (myvenue.seats[i][j].seat_status == unsold)
				{
					cout << "[$" << myvenue.rowprices[i] << "]";
				}//if
				//Print out the sold seats
				else
				{
					cout << "[N/A]";
				}//else
			}//for
			cout << endl;
		}//for
	}//if
	else
	{
		cout << "There is no venue to print! " << endl;
	}//else
}//print

/*sell_tickets - This method gets the number of tickets the user wants, give 
  out the ticket prices for avabile rows, then it looks for consecutive seats in the price range.
  Once again the parameter myvenue tracks the overall venue.
 */
void sell_tickets(venue & myvenue)
{
	int tickets;						//Number of tickets the user wants to buy
	int i, j,k;							//Loop counters
	int range;						//The price the user wants to buy a ticket for 
	bool not_found;				//Price the user enters (checks to make sure it exists)
	bool search;					//Tracks if we've found enough tickets in the correct priced row
	char want_tic;				//Askes the user if they want to tickets the computer has found
	int num_ava;					//Tracks the number of avaliable tickets
	int pos_sold[10][10];		//Tracks if the seat is possibly sold

	if (myvenue.open == true)
	{
		//Initialize
		not_found = false;
		search = false;
		//Get the number of tickets the user wants to buy
		cout << "How many tickets do you want to buy? ";
		cin >> tickets;

		//Give the price range the user can pick from 
		cout << "Ticket Prices to pick from: " << endl;
		for (i = 0; i < myvenue.rows; i++)
		{
			cout << "$" << myvenue.rowprices[i] << endl;
		}//for

		cout << "Select your price : $";
		cin >> range;
		//Validate
		while (not_found == false)
		{
			//Check to make sure the user selects a price in the range
			for (i = 0; ((i < myvenue.rows) && (not_found == false)); i++)
			{
				if (myvenue.rowprices[i] == range)
				{
					not_found = true;
				}//if
			}//for
			if (not_found == false)
			{
				cout << "INVALID! Please enter a valid price: ";
				cin >> range;
			}//if
		}//while

		//Look for the correct number of tickets in a consecutive order
		for (i = 0; (i < myvenue.rows) && (search != true); i++)
		{
			num_ava = 0;
			if (myvenue.rowprices[i] == range)
			{
				for (j = 0; (j < myvenue.columns) && (search != true); j++)
				{
					if (myvenue.seats[i][j].seat_status == unsold)
					{
						num_ava++;
						pos_sold[i][j] = 1;
						if (num_ava == tickets)
						{
							search = true;
						}//if
					}//if
				}//for
			}//if
			k = i;
		}//for

		//Tell the user if you've found the tickets and ask them if they want the found tickets
		if (search == true)
		{
			cout << "We've found " << tickets << " ticket(s) in Row " << k + 1 << " would you like to buy these tickets (Y/N)? ";
			want_tic = toupper(_getche());
			cout << endl;
			//Validate
			while (want_tic != 'Y'&&want_tic != 'N')
			{
				cout << "INVALID! Please enter (Y)es or (N)o: ";
				want_tic = toupper(_getche());
				cout << endl;
			}//while
			if (want_tic == 'Y')
			{
				cout << "You've got the tickets! " << endl;
				//Set the seats to taken
				for (i = 0; i < myvenue.rows; i++)
				{
					for (j = 0; j < myvenue.columns; j++)
					{
						if (pos_sold[i][j] == 1)
						{
							myvenue.seats[i][j].seat_status = sold;
						}//if
					}//for
				}//for
			}//if
			else
			{
				cout << "You chose not to buy the tickets. " << endl;
			}//else
		}//if
		else
		{
			cout << "Sorry we couldn't find enough consecutive tickets for the price you wanted. " << endl;
		}//else
	}//if
	else
	{
		cout << "There is no venue to buy tickets from! " << endl;
	}//else
}//sell_tickets

/*venue_stats -This method prints out information about the venue and the stats about sold/unsold seats.
  Again myvenue is a parameter which will track the overall venue.
*/
void venue_stats(venue myvenue)
{
	int total_seats;								//The total number of seats in the venue
	float num_sold;								//Number of seats sold
	float num_unsold;							//Number of seats left to be sold
	float dollar_value_unsold;			//Dollar value of unsold tickets
	float dollar_value_sold;					//Dollat value of sold tickets
	int i, j;												//Loop counters

	if (myvenue.open == true)
	{
		//Initialize
		total_seats = 0;
		num_sold = 0;
		num_unsold = 0;
		dollar_value_sold = 0;
		dollar_value_unsold = 0;

		//Set the price of each seat baised off of the row prices
		for (i = 0; i < myvenue.rows; i++)
		{
			for (j = 0; j < myvenue.columns; j++)
			{
				myvenue.seats[i][j].price = myvenue.rowprices[i];
			}//for
		}//for

		//Find the total number of seats in the venue
		for (i = 0; i < myvenue.rows; i++)
		{
			for (j = 0; j < myvenue.columns; j++)
			{
				total_seats++;
				//See if the seat is sold or not and track the number of each
				if (myvenue.seats[i][j].seat_status == sold)
				{
					dollar_value_sold += myvenue.seats[i][j].price;
					num_sold++;
				}//if
				else
				{
					dollar_value_unsold += myvenue.seats[i][j].price;
					num_unsold++;
				}//else
			}//for
		}//for
		//Print out the data to the user
		cout << "There are " << total_seats << " seats in the venue." << endl;
		cout << "There are " << num_sold << " (" << (num_sold / total_seats) * 100 << "%) seat(s) sold." << endl;
		cout << "There are " << num_unsold << " (" << (num_unsold / total_seats) * 100 << "%) seat(s) available." << endl;
		//Ensures that we do not divide by zero
		if (num_sold > 0)
		{
			cout << "The total dollar value of the sold ticket(s) is $" << dollar_value_sold << " (" << (dollar_value_sold / (dollar_value_sold + dollar_value_unsold)) * 100 << "%)." << endl;
			cout << "The total dollar value of the available ticket(s) is $" << dollar_value_unsold << " (" << (dollar_value_unsold / (dollar_value_sold + dollar_value_unsold)) * 100 << "%)." << endl;
		}//if
	}//if
	else
	{
		cout << "There is no venue to get stats from! " << endl;
	}//else
}//venue_stats

/*save - This method saves the current venue in a file so it can be used again later.
  myvenus is a parameter which will track the overall venue.
*/
void save(venue myvenue)
{
	ofstream outfile;                   //File we are writing to 

	//Check to make sure there is a puzzle to save
	if (myvenue.open == true)
	{
		//Open the file
		outfile.open("venue.DAT", ios::out);

		//Look for any potentil file erros
		if (outfile)
		{
			//Write to the file and then close the file
			outfile.write((char*)&myvenue, sizeof(myvenue));
			outfile.close();
			//Tell the user that the venue has been saved
			cout << "The venue has been saved." << endl;
		} // if
		else
		{
			//Print out message if there is a file error
			cout << "FILE ERROR - This file may not exist. " << endl;
		} // else
	}//if
	else
	{
		cout << "There is no venue to save currently! " << endl;
	}//else
}//save

/*load - This method loads a previously saved venu so it can continue to be used.
  Parameter myvenue tracks the overall venue.
*/
void load(venue & myvenue)
{
	ifstream infile;                        //What file is being read from 
	char choice;						    //Get the user choice before they load

	//Make sure the user wants to continue
	cout << "By loading you will delete any current data. Do you want to contine (Y)es or (N)o?: ";
	choice = toupper(_getwche());
	cout << endl;
	//Validate
	while (choice != 'Y' && choice != 'N')
	{
		cout << "INVALID! Please enter (Y)es or (N)o: ";
		choice = toupper(_getwche());
		cout << endl;
	}//while
	//User selects that they want to continue
	if (choice == 'Y')
	{
		//Open the file
		infile.open("venue.DAT", ios::in);
		if (infile)
		{
			//Read structure and then close the file
			infile.read((char*)&myvenue, sizeof(myvenue));
			infile.close();
			//Tell the user that the venue has been loaded
			cout << "The venue data has been loaded. " << endl;
			myvenue.open = true;
		} // if
		else
		{
			cout << "FILE ERROR! File may not exist." << endl;
		} // else
	} // if confirm
}//load