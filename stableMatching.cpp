#include <iostream>
#include <cstring>

using namespace std;

const int peopleToMatch = 3;

// ***********************************************************************
struct Woman;
class Man;

void CreateListOfMen(Man * & head);
void InitializeMan(Man *head, int num);
void InitializeWomen(Woman *women);
void MatchPartners(Man * & head, Woman *women, int *matchings);
int Propose(Man * & head, Woman *women, int womanNum);
void SwitchMen(Man * & head, Woman *women, int womanNum, int *matchings, int loser);
string GetName(char gender, int myName);
void PrintPreferences(Man *head, Woman *women);
void PrintMatched(const int *matchings);
// ***********************************************************************



// ***********************************************************************
//
//				Women
//
// ***********************************************************************

// Has the preference list for a woman and if she is already matched
struct Woman{
  int myNum;
  int men[peopleToMatch];
  bool isMatched;
  int matchedTo;
};


// ***********************************************************************
//
//				 Men
//
// ***********************************************************************

class Man{

// Eventually make these private and use class functions to call them
  public:
  int myNum;
  int women[peopleToMatch];
  Man *next;

  void add_man(Man*&,int);
  void delete_man(Man*&);
};

// ***********************************************************************

// Creates a man and inserts him at the front of the list
// Sets the head to be the newly created man
void Man::add_man(Man * & head, int myNum){
  Man *current;
  current = new Man;
  current->next = head;
  
  head = current;

  InitializeMan(head, myNum);
}

// ***********************************************************************

// Deletes a man from the list and sets the head as the next man
void Man::delete_man(Man * & head){
//*** cout << endl << "****DELETING " << head << "****" << endl;
  Man *toDelete;

  toDelete = head;

  head = head->next;
  delete toDelete;
  toDelete->next = NULL;
}


// ***********************************************************************
//
//				Main 
//
// ***********************************************************************


int main(){

cout << endl << endl;

  int matchings[peopleToMatch];		// matchings[guy] = woman
  Woman women[peopleToMatch];
  Man *head = NULL;
  
  
  CreateListOfMen(head);
  InitializeWomen(women);
  PrintPreferences(head, women);

  MatchPartners(head, women, matchings);

  PrintMatched(matchings);
  
  cout << endl << endl;
  return 0;
}



// ***********************************************************************
//
//			    Men/Women Creation
//
// ***********************************************************************

void CreateListOfMen(Man * & head){
  Man *next = NULL;
  
  for(int i=0; i<peopleToMatch; i++){
    head->add_man(head, i);
    
    // Set up as FILO
    if(i == 0){
      head->next = NULL;
    }
//***    cout << endl << "Current " << head << endl << "Next " << head->next << endl;
//***    cout << "   Man " << head->myNum << ") " << head->women[0] << head->women[1]<< head->women[2]<< endl << endl;
  }
}  


// ***********************************************************************


// Fills in a man's number and his preference for women
void InitializeMan(Man *head, int num){
   if(num == 0){
    head->myNum = 0;
    head->women[0] = 0;
    head->women[1] = 1;
    head->women[2] = 2;
  }
  else if(num == 1){
    head->myNum = 1;
    head->women[0] = 0;
    head->women[1] = 2;
    head->women[2] = 1;
  }
  else if(num == 2){
    head->myNum = 2;
    head->women[0] = 0;
    head->women[1] = 2;
    head->women[2] = 1;
  }
}


// ***********************************************************************


// Creates the list of women and sets up their preferences
void InitializeWomen(Woman *women){

  women[0].myNum = 0;
  women[0].men[0] = 1;
  women[0].men[1] = 1;
  women[0].men[2] = 2;
  women[0].isMatched = false;

  women[1].myNum = 1;
  women[1].men[0] = 1;
  women[1].men[1] = 2;
  women[1].men[2] = 0;
  women[1].isMatched = false;

  
  women[2].myNum = 2;
  women[2].men[0] = 1;
  women[2].men[1] = 0;
  women[2].men[2] = 2;
  women[2].isMatched = false;
 
}


// ***********************************************************************
//
//				Matching
//
// ***********************************************************************



void MatchPartners(Man * & head, Woman *women, int *matchings){
  int loser;
  int proposeCnts[peopleToMatch];	// Holds the number of times each guy has proposed
  
  for(int i = 0; i < peopleToMatch; i++){
    proposeCnts[i] = 0;
  }

  while(head != NULL){
    // Loop through men's preferences
    for(int i = proposeCnts[head->myNum]; i < peopleToMatch; i++){
      
      loser = Propose(head, women, head->women[i]);
      proposeCnts[head->myNum] = proposeCnts[head->myNum] + 1;

///*****/      cout << endl << "Man " << head->myNum << " asks " << head->women[i];
      
      // If she's unmatched (-1), delete myself then break me out of the loop
      if(loser == -1){
///*****/        cout << endl << "Won by default - Man " << head->myNum << " asks " << head->women[i];
        matchings[head->myNum] = head->women[i];
        head->delete_man(head);
        break;
      }
      
      // Otherwise check if I'm not the looser
      else if(loser != head->myNum){
        // If I'm not the looser, switch my partners, delete myself, and add the loser back to the list
        SwitchMen(head, women, head->women[i], matchings, loser);
        matchings[head->myNum] = head->women[i];
        
///*****/        cout << endl <<  "Deleting Winner " << head << " - Man " << head->myNum << "  - Woman " << head->women[i];
        head->delete_man(head);
///*****/        cout << endl << "New Man Added " << loser << " " << head << endl;
        head->add_man(head, loser);
        break;
      }
    }  
  }
  
}


// ***********************************************************************


// Determine's the woman's choice of preference. If she is unmatched then she matches
  // Return Values:
  // -1 means she is unmatched
  // Otherwise she returns the looser's number
int Propose(Man * & head, Woman *women, int womanNum){
//***  cout << "Proposing - Man " << head->myNum << " asks " << womanNum << endl;
  // If Unmatched
  if(women[womanNum].isMatched == false){
    women[womanNum].isMatched = true;
    women[womanNum].matchedTo = head->myNum;
    
    return -1;
  }
  // Otherwise - determine who is better
  else{
    // Loop through woman's preferences until the best man is found
    for(int i = 0; i < peopleToMatch; i++){
      if(women[womanNum].men[i] == head->myNum){
        return women[womanNum].matchedTo;
      }
      else if(women[womanNum].men[i] == women[womanNum].matchedTo)
        return head->myNum;
    }
  }
  return -2;
}

// ***********************************************************************

// Switches the man's spots and returns the amt of people already proposed to
// Deletion and adding the other man will be handled elsewhere
void SwitchMen(Man * & head, Woman *women, int womanNum, int *matchings, int loser){
  matchings[loser] = -5;        // Arbitary negative number since a woman will never be negative

//***  cout << endl << "Man " << head->myNum << " wins. Loser is " << loser << endl;
  women[womanNum].matchedTo = head->myNum;
}


// ***********************************************************************
//
//			Name/Number Conversion
//
// ***********************************************************************


// Returns the string name linked to the number used to represent the name
string GetName(char gender, int myName){
// Men:   1) Adam
//        2) Bert
//        3) Caleb

// Women: 1) Amy
//        2) Beth
//        3) Carla

  string men[peopleToMatch] = {"Adam", "Bert", "Caleb"};
  string women[peopleToMatch] = {"Amy", "Beth", "Carla"};

  if(gender == 'm')
    return men[myName];
  else
    return women[myName];

}


// ***********************************************************************
//
//				Print
//
// ***********************************************************************
void PrintPreferences(Man *head, Woman *women){
  Man *temp;
  
  temp = head;
  
  cout << endl << "Preference Order: " << endl
       << "\tMen:";
  while(temp != NULL){
    
    cout << endl << "\t" << temp->myNum << ") ";
    for(int j = 0; j<peopleToMatch; j++){
       cout << temp->women[j] << " "; 
    }
    temp = temp->next;
  }
  
  cout << endl << endl << "\tWomen:";
  for(int i = 0; i<peopleToMatch; i++){
    cout << endl << "\t" << i << ") ";
    for(int j = 0; j<peopleToMatch; j++){
      cout << women[i].men[j] << " ";
    }
  }  
}


// ***********************************************************************


void PrintMatched(const int *matchings){
  cout << endl << endl;

  cout << "Names of Men: " << endl;
  for(int i = 0; i < peopleToMatch; i++){
    cout << i << ") " << GetName('m', i) << endl;
  }
  
  cout << endl << endl << "Names of Women: " << endl;
  for(int i = 0; i < peopleToMatch; i++){
    cout << i << ") " << GetName('f', i) << endl;
  }

  

  cout << endl << endl << "After Matchings:" << endl << endl;
  
  cout << "\t    Women" << endl
       << "\t    0   1   2" << endl << "\t   ";
      
  for(int i = 0; i<peopleToMatch; i++)
    cout << "--- "; 
    
  cout << endl <<  "Men\t";
  for(int i = 0; i<peopleToMatch; i++){
    cout << i << " |";
    for(int j = 0; j<peopleToMatch; j++){
        
      if(matchings[j] == i){
        cout << " x |";
      } else{
        cout << "   |";    
      }
    }
      cout << endl << "\t";
  }
    
  cout << endl << endl;
  for(int i = 0; i<peopleToMatch; i++)
    cout << GetName('m', i) << " is matched with " << GetName('f', matchings[i]) << endl;

  cout << endl;


}
