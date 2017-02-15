#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

const int peopleToMatch = 3;

// Holds the man's order of preference of women and the link to the next man
struct Man{
  string myName;
  string women[peopleToMatch];
  bool isMatched;
  int timesProposed;
  string matchedTo;
  Man *next;
};

// Has the preference list for a woman and if she is already matched along with the rank of the person she is matched to
struct Woman{
  string myName;
  string men[peopleToMatch];
  bool isMatched;
  string matchedTo;         //holds the rank in preference that a woman is matched to
};










// *******************************************************************************************************
void Init(Man *head, Woman *women, Man *end);
void TestMenAndWomen(Man *head, Woman *women);
void MatchPartners(Man *current, Woman *women, Man *end);
bool ProposeTo(string woman, Woman *women, string man, Man *head);
bool CompareMen(Woman *woman, string man, int womanSpot);
void SwitchMen(Man *head, string manToAdd, string manToRemove);
// *******************************************************************************************************


int main(){
  Woman women[peopleToMatch];
  Man *head;
  Man *end;
  
  head = new Man;

  Init(head, women, end);  

// Tests the names and preferences of each man/woman
  TestMenAndWomen(head, women);

  MatchPartners(head, women, end);

  return 0;
}



void MatchPartners(Man *current, Woman *women, Man *end){
  Man *next;
  int cnt=0;		// Used to check how many men in a row are unmatched.
  bool matched;
  
  
  // Loop through while adding unmatched men to the end of the list.
  // End once the amount of people to match has been cycled through and all are matched.
  while(cnt<peopleToMatch){
    if(!(*current).isMatched){
      cnt = 0;

      // Check if the guy is unmatched
      while(!(*current).isMatched || (*current).timesProposed <= peopleToMatch){
        // Propose to the next woman
        cout << endl << current->myName << " proposing to: " << (*current).women[(*current).timesProposed];
        matched = ProposeTo((*current).women[(*current).timesProposed], women, (*current).myName, current);
        // If she approves - handle it
        if(matched){
        cout << endl << "MATCHED!" << endl;
          (*current).isMatched = true;
          (*current).matchedTo = women[(*current).timesProposed].myName;

          // Look at the next guy
          next = current->next;

          // Move Guy to the end of the list          
          end->next = current;
          current->next = NULL;

          end = current;
          
          // Look at the front of the list
          current = next;
          
        }
        (*current).timesProposed = (*current).timesProposed + 1;
        break;
      }
    }
    else
      cnt++;
  }
}


bool ProposeTo(string woman, Woman *women, string man, Man *head){
  int womanSpot;
  bool womanFound = false;
  bool switchMen = false;
  
  // Find the desired woman in the array
  for(womanSpot = 0; womanSpot < peopleToMatch; womanSpot++){
    if(strcmp(woman.c_str(), (women[womanSpot].myName).c_str()) == 0){
      womanFound = true;
      break;
      }
  }
  if(womanFound){
    if(women[womanSpot].isMatched == false){
      women[womanSpot].isMatched = true;
      women[womanSpot].matchedTo = man;
      return true;
    }
    else{
      switchMen = CompareMen(women, man, womanSpot);
      if(switchMen){
// Dump Current Guy (switch his and her matched status)
        SwitchMen(head, man, women[womanSpot].matchedTo);
      }
    }  
  }
  return switchMen;
}



// Changes a man's matched status once broken up with
void SwitchMen(Man *head, string manToAdd, string manToRemove){
  Man *current;
  
  current = head;
  
  for(int i = 0; i < peopleToMatch; i++){
     if(strcmp(manToRemove.c_str(), ((*current).myName).c_str() ) == 0){
       current->isMatched = false;
       current->matchedTo = "----";
     }
     else
       current = current->next;
  }
}



bool CompareMen(Woman *woman, string man, int womanSpot){
  // Find the guy proposing or the current match
  for(int i = 0; i < peopleToMatch; i++){
    if(strcmp((woman[womanSpot].men[i]).c_str(), (woman[womanSpot].matchedTo).c_str()) == 0)
      return false;
    else if(strcmp((woman[womanSpot].men[i]).c_str(), man.c_str()) == 0){
      return true;
    }
  }
}



// Sets up the array of women and the linked list of Men and fills their preferences and matched status
void Init(Man *head, Woman *women, Man *end){

// These are a list of 5 names to use separated into 3 names and 5 names.
// Women:  Amy Betty Carla    -    Daphne Ella
// Men:    Adam Bert Caleb    -    David Elliot

  Man *current;
  Man *next;
  
  current = head;
  
  // Set up the men's preferences
  current->myName = "Adam";  
  current->women[0] = "Amy"  ;
  current->women[1] = "Carla";
  current->women[2] = "Betty";
  current->isMatched = false;
  current->timesProposed = 0;

  next = new Man;
  next->myName = "Bert";
  next->women[0] = "Carla";
  next->women[1] = "Amy";
  next->women[2] = "Betty";
  next->isMatched = false;
  next->timesProposed = 0;
  current->next = next;
  current = next;

  next = new Man;
  next->myName = "Caleb";
  next->women[0] = "Carla";
  next->women[1] = "Betty";
  next->women[2] = "Amy";
  next->isMatched = false;
  next->timesProposed = 0;
  current->next = next;
  current = next;

  // Ends the linked list of Men
  next->next = NULL;
  end = next;
  
  // Set up the women's preferences
  women[0].myName = "Amy";
  women[0].men[0] = "Caleb";
  women[0].men[1] = "Adam";
  women[0].men[2] = "Bert";
  women[0].isMatched = false;
  

  women[1].myName = "Betty";
  women[1].men[0] = "Caleb";
  women[1].men[1] = "Bert";
  women[1].men[2] = "Adam";
  women[1].isMatched = false;

  women[2].myName = "Carla";
  women[2].men[0] = "Bert";
  women[2].men[1] = "Caleb";
  women[2].men[2] = "Adam";
  women[2].isMatched = false;
  
}



// This function outputs the names and preferences for each man and each woman.
// *For Testing Purposes*
void TestMenAndWomen(Man *head, Woman *women){
  Man *current;
  Man *next;
  
  current = head;
  
  // Loop through Men.
  cout << endl << "MEN: " << endl << endl;
  for( int j = 0; j<peopleToMatch; j++){
    cout << "My Name Is: " << (*current).myName << endl
         << "\tMy preference order of women are: " << endl;
    
    // Loop through Preferences
    for(int k = 0; k<peopleToMatch; k++){
        cout << "\t" << k+1 << ")  " << (*current).women[k] << endl;
      }
    cout << endl;
    current = current->next;
  }

  cout << endl << "---------------------------------------------------------------------" << endl << endl;

  cout << "WOMEN: " << endl << endl;
  // Loop through Women
  for(int i = 0; i<peopleToMatch; i++){
    cout << "My Name Is: " << women[i].myName << endl
         << "\tMy preference order for men are: " << endl;
    
    // Loop through Preferences
    for(int j = 0; j<peopleToMatch; j++){
      cout << "\t" << j+1 << ")  " << women[i].men[j] << endl;
    }
    cout << endl;
  }
}