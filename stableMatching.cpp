#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

const int peopleToMatch = 3;

// Holds the man's order of preference of women and the link to the next man
struct Man{
  int myName;
  int women[peopleToMatch];
  Man *next;
};

// Has the preference list for a woman and if she is already matched along with the rank of the person she is matched to
struct Woman{
  int myName;
  int men[peopleToMatch];
  bool isMatched;
  int matchedTo;         //holds the rank in preference that a woman is matched to
};



// *******************************************************************************************************
void MatchPartners(Man *current, Woman *women, int *matchings);
int Propose(int man, Woman *women, int chosenWoman);
void InitializeAll(Man *head, Woman *women);
void Initialize(Man *head, Woman *women, char gender, int num);
void TestMenAndWomen(Man *head, Woman *women);
string GetName(char gender, int myName);
// *******************************************************************************************************

int main(){
  Woman women[peopleToMatch];
  int matchings[peopleToMatch];
  Man *head;
  string nname;

  head = new Man;

   InitializeAll(head, women);
   

// Tests the names and preferences of each man/woman
//  TestMenAndWomen(head, women);

  MatchPartners(head, women, matchings);

  for(int q = 0; q <= peopleToMatch; q++){
    nname = GetName('m', q);
    cout << endl << nname << " ";
    nname = GetName('w', matchings[q]);
    cout << nname;
  }
  cout << endl;
  return 0;
}


void MatchPartners(Man *current, Woman *women, int *matchings){
  Man *next;
  int proposeCnt;
  int partnerChosen;
  
  while(current->next != NULL){
    next = current->next;

    // Get how many times the guy has proposed
    proposeCnt = matchings[current->myName];
    
    // If it's not his first time proposing - propose to the next girl
    if(proposeCnt != 0)
      proposeCnt++;
    
    // Keep proposing until matched (or running out of people to try - which shouldn't happen)
    while(proposeCnt <= peopleToMatch){
      partnerChosen = Propose(current->myName, women, proposeCnt);
      
      // If the chosen partner is of a higher number - he needs put back on the list
      // because the girl just switched partners
      if(partnerChosen > current->myName){
        matchings[current->myName] = proposeCnt;
        // Add the guy back to the list
        Initialize(current, women, 'm', partnerChosen); 
        current->next = next;
        break;
      }    
    }
  }
}

int Propose(int man, Woman *women, int chosenWoman){
  // Woman is unmatched
  if(!(women[chosenWoman].isMatched))
    return 0;
  
  // Woman prefers the new man
  else if(man < women[chosenWoman].matchedTo)
    return women[chosenWoman].matchedTo;
    
  // Woman prefers her current man
  else
    return -1;
}


void InitializeAll(Man *head, Woman *women){
  Man *tmp;
  Man *next;
  
  
  next = head;  
                
  // Initialize all men
  for(int i = 0; i<peopleToMatch; i++){
   cout << endl << "started" ;
   Initialize(next, women, 'm', i);
   if(i < peopleToMatch-1)
     next = next->next;
   cout << endl << "man " << next->myName << " " << next->women[1] << next->women[2] << next->women[3];
  }
  
  next->next = NULL;
  
  // Get rid of the first once since it is empty
  tmp = head->next;
  delete head;
  head = tmp;
  
  // Initialize all women
  for(int i = 0; i<peopleToMatch; i++)
    Initialize(next, women, 'f', i);                 

}

// Sets up the array of women and the linked list of Men and fills their preferences and matched status
void Initialize(Man *head, Woman *women, char gender, int num){

// These are a list of 5 names to use separated into 3 names and 5 names.
// Women:  Amy Betty Carla    -    Daphne Ella
// Men:    Adam Bert Caleb    -    David Elliot

  switch(gender){
  case 'm':
    Man *current;

    current = head;

    // Set up the men's preferences
      current = new Man;
      head->next = current;

    if(num == 0){
      cout << endl << "one";
      current->myName = 1;
      current->women[0] = 1;
      current->women[1] = 3;
      current->women[2] = 2;
    }
    else if(num == 1){
    cout << endl << "two";
      current->myName = 2;
      current->women[0] = 3;
      current->women[1] = 1;
      current->women[2] = 2;
    }

    else if(num == 2){
    cout << endl << "three";
      current->myName = 3;
      current->women[0] = 3;
      current->women[1] = 2;
      current->women[2] = 1;
    }
    break;
  // Set up the women's preferences
  case 'f':
    if(num == 0){
      women[0].myName = 1;
      women[0].men[0] = 3;
      women[0].men[1] = 1;
      women[0].men[2] = 2;
      women[0].isMatched = false;
    }      
    else if(num == 1){
      women[1].myName = 2;
      women[1].men[0] = 3;
      women[1].men[1] = 2;
      women[1].men[2] = 1;
      women[1].isMatched = false;
    }
    else if(num == 2){
      women[2].myName = 3;
      women[2].men[0] = 2;
      women[2].men[1] = 3;
      women[2].men[2] = 1;
      women[2].isMatched = false;
    }
  }
}


// This function outputs the names and preferences for each man and each woman.
// *For Testing Purposes*
void TestMenAndWomen(Man *head, Woman *women){
  Man *current;
  Man *next;

  current = head;

  // Loop through Men
  cout << endl << "MEN: " << endl << endl;
  for( int j = 0; j<peopleToMatch; j++){
    cout << "My Name Is: " << GetName('m', j)  << endl
         << "\tMy preference order of women are: " << endl;
    for(int i = 0; i<peopleToMatch; i++){
      cout << "\t" << i+1 << ")  " << GetName('w', current->women[i]) << endl;
    }
    current = current->next;
  }
/*
  // Loop through Men.
  cout << endl << "MEN: " << endl << endl;
  for( int j = 0; j<peopleToMatch; j++){
    cout << "My Name Is: " << GetName('m', j)  << endl
         << "\tMy preference order of women are: " << endl;

    // Loop through Preferences
    for(int k = 0; k<peopleToMatch; k++){
        cout << "\t" << k+1 << ")  " << GetName('w', current->women[k]) << endl;
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
  }*/
}



string GetName(char gender, int myName){
  string men[peopleToMatch] = {"Adam", "Bert", "Caleb"};
  string women[peopleToMatch] = {"Amy", "Beth", "Carla"};

  if(gender == 'm')
    return men[myName];
  else
    return women[myName];

}
