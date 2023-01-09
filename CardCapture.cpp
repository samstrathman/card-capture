//This video is my reference for designing the game https://www.youtube.com/watch?v=uj-YpWIxK9Y&list=PLoeKOs9eeocZK3jpASlyMFhoYOtyMDpPj&index=36&ab_channel=LucasGentry
//It's a single player deck building game that uses a standard deck of cards plus jokers.

#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<chrono>
#include<sstream>
#include<algorithm>
using namespace std;

//Initialize enums
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, JOKER }; 
enum Suit { SPADES = 1, HEARTS, DIAMONDS, CLUBS, NONE }; //the NONE suit is for joker

/*/Log for debugging purposes
class Log{
public:
    static const int LogLevelError = 0; //error messages
    static const int LogLevelWarning = 1; //warning messages
    static const int LogLevelInfo = 2; //information messages
private:
    int m_LogLevel = LogLevelInfo; //m indicates class level variable that is private, set to info so that everything gets printed
public:
    void SetLevel(int level){
        m_LogLevel = level;
    }

    void Error(const char* message){
        if (m_LogLevel >= LogLevelError){
            cout << "[ERROR]: " << message << endl;
        }
    }
    
    void Warn(const char* message){
         if (m_LogLevel >= LogLevelWarning){
            cout << "[WARNING]: " << message << endl;
        }
    }

    void Info(const char* message){
        if (m_LogLevel >= LogLevelInfo){
            cout << "[INFO]: " << message << endl;
        }
    }
};
*/

//Create Card datatype with each card having a suit and a rank
struct Card {  
    Suit suit;
    Rank rank;

    //function to display a single card
    void PrintCard(){
        //Code so " of " doesn't print when the card is a Joker (since it has no suit)
        if (rank == JOKER){
            PrintRank();
        }
        else{
            PrintRank();
            cout << " of ";
            PrintSuit();
        }
    }

    //used in the PrintCard function to determine the rank
    void PrintRank(){
        switch (rank){
            case TWO: cout << "two";
            break;
            case THREE: cout << "three";
            break;
            case FOUR: cout << "four";
            break;
            case FIVE: cout << "five";
            break;
            case SIX: cout << "six";
            break;
            case SEVEN: cout << "seven";
            break;
            case EIGHT: cout << "eight";
            break;
            case NINE: cout << "nine";
            break;
            case TEN: cout << "ten";
            break;
            case JACK: cout << "jack";
            break;
            case QUEEN: cout << "queen";
            break;
            case KING: cout << "king";
            break;
            case ACE: cout << "ace";
            break;
            case JOKER: cout << "joker";
            break;
        }
    }

    //used in the PrintCard function to determine the suit
    void PrintSuit() {
        switch (suit) {
            case SPADES: cout << "spades";
            break;
            case HEARTS: cout << "hearts";
            break;
            case DIAMONDS: cout << "diamonds";
            break;
            case CLUBS: cout << "clubs";
            break;
            case NONE: //this is just so the compiler doesn't give me warnings every time
            break;
        }
    }
};

//Create Deck datatype that holds an arry of Card datatypes to form a full deck of cards
class Deck {
    private: 
    vector<Card> deckOfCards;
    public:

    //Initialize a full deck of cards (UNUSED FOR CARD CAPUTRE)
    void SetupCards() {               
        Card jokerCard = {NONE, JOKER}; //create a joker card to add to the end of the deck

        //Add the two jokers to the beginning of the deck (this makes it easier to separate for initialization)
        deckOfCards.push_back(jokerCard);
        deckOfCards.push_back(jokerCard);

        //Iterate through all suits and ranks to cover all cards (except jokers)
        for(int col = SPADES; col <= CLUBS; col++){
            for(int row = TWO; row <= ACE; row++){
                Card c;
                c.suit = (Suit)col; 
                c.rank = (Rank)row;
                
                deckOfCards.push_back(c);
            }
        } 
    }

    //Initialize the player deck
    void SetupPlayerDeck() {
        Card jokerCard = {NONE, JOKER}; //create a joker card to add to the end of the deck

        //Add the two jokers to the beginning of the deck
        deckOfCards.push_back(jokerCard);
        deckOfCards.push_back(jokerCard);

        //Iterate through all suits and ranks to cover all needed cards (2-4 plus jokers for player deck)
        for(int col = SPADES; col <= CLUBS; col++){
            for(int row = TWO; row <= FOUR; row++){
                Card c;
                c.suit = (Suit)col; 
                c.rank = (Rank)row;
                
                deckOfCards.push_back(c);
            }
        } 
    }
    
    //DEBUG CODE USE MAKE CUSTOM DECKS
    // void debugDeck(){
    //    Card a = {SPADES, TWO};
    //    deckOfCards.push_back(a);
    //    Card b = {SPADES, THREE};
    //    deckOfCards.push_back(b);
    //    Card c = {CLUBS, TWO};
    //    deckOfCards.push_back(c);
    //    Card d = {CLUBS, THREE};
    //    deckOfCards.push_back(d);
    // }
     
    //Initialize the enemy deck
    void SetupEnemyDeck(){
        //Iterate through all suits and ranks to cover all needed cards (5-Ace for enemy deck)
        for(int col = SPADES; col <= CLUBS; col++){
            for(int row = FIVE; row <= ACE; row++){
                Card c;
                c.suit = (Suit)col; 
                c.rank = (Rank)row;
                
                deckOfCards.push_back(c);
            }
        } 
    } 

    //Print the deck (FOR TESTING)
    void PrintDeck(){
        for(int i = 0; i < deckOfCards.size(); i++){
            deckOfCards[i].PrintCard();
            cout << endl;
        }
    }

    //Differs from PrintDeck in that it numbers the cards 1-4, for use capturing enemy cards and stuff
    void PrintHand(){
        if(deckOfCards.size() == 0){
            cout << "Empty!" << endl;
        }
        else{
            for(int i = 0; i < deckOfCards.size(); i++){
                cout << i + 1 << " ";
                deckOfCards[i].PrintCard();
                cout << endl;
            }
        }
    }
    
    //Shuffle the deck
    void ShuffleDeck(){
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(deckOfCards.begin(), deckOfCards.end(), default_random_engine(seed));
    }

    //Return the top card from a deck 
    Card TopCard(){
        Card c = deckOfCards.back();
        return c;
    }

    //Remove the top card from the deck (MAYBE GET RID OF THIS FUNCTION)
    void PopCard(){
        deckOfCards.pop_back();
    }

    //Return the enum rank of the card at position "i" in the deck
    int GetRank(int i){
        return deckOfCards[i].rank;
    }

    //Return the enum suit of the card at position "i" in the deck
    int GetSuit(int i){
        return deckOfCards[i].suit;
    }
   
    //Return the number of cards currently in the deck
    int DeckSize(){
        return deckOfCards.size();
    }
    
    //Remove the card at a specific location, used when capturing an enemy card or discarding from the player hand. 
    void RemoveCard(int i){
        deckOfCards.erase(deckOfCards.begin() + i);
    }

    //Insert card from otherDeck into deckOfCards
    //Used for enemy redraw function and in the discard phase to move cards to the bottom of the player's discard pile (maybe make that it's own function)
    void InsertCardAtBottom(Card & c){
        deckOfCards.insert(deckOfCards.begin(), c);
    }

    //Move cards from draw deck to hand until the hand has 4 cards (OR until the draw pile 'otherDeck' is out of cards to draw)
    void DrawHand(Deck& otherDeck){
        while(deckOfCards.size() < 4){
            if(otherDeck.deckOfCards.size() == 0){
                break;      
            }
            else{
                deckOfCards.insert(deckOfCards.begin(), otherDeck.TopCard()); //take the top card from draw pile and add it to the hand
                otherDeck.PopCard(); //remove that card from the draw pile 
            }                                         
        }                  
    }

    //Draw a card from otherDeck and place it in the deckOfCards at i (useful for the enemy redraw function and the player redraw during discard phase)
    //Then remove the card from otherDeck
    void DrawCard(Deck& otherDeck, int i){
          deckOfCards.insert(deckOfCards.begin() + i, otherDeck.TopCard());
          otherDeck.PopCard();
    }

    //Return the card at position i
    Card GetCard(int i){
        Card c = deckOfCards[i];
        return c;
    }
};

//Create Player datatype that has a draw pile, a hand, and a discard pile (capture pile for the enemy)
class Player {
    public: //SET THIS TO PRIVATE AFTER DONE 
    Deck drawPile;
    Deck hand;
    Deck discardPile;

    public:
    //Initializes the player's drawpile
    void SetUpPlayer(){
        drawPile.SetupPlayerDeck();
    }

    //Initializes the enemy's drawpile
    void SetUpEnemy(){
        drawPile.SetupEnemyDeck();
    }

    //Draw cards until there is four cards in the hand
    void DrawPlayerHand(){
        hand.DrawHand(drawPile); //this function will return if the the drawpile runs out of cards
        if(hand.DeckSize() < 4){
            ReshuffleDrawPile();
            cout << "Player drawhand reshuffle triggered" << endl; //DEBUG
            hand.DrawHand(drawPile);
        }
    }

    //Draw cards until there is four cards in the hand
    void DrawEnemyHand(){
        hand.DrawHand(drawPile);
    }

    //Moves the cards from the discard pile to the drawpile and reshuffles them. Used in discard phase when the player's drawpile has run out
    void ReshuffleDrawPile(){
        //Iterate through the whole discard pile, copy each card to the drawpile, then remove the card from the discard pile
        while(discardPile.DeckSize() > 0){
            Card c; 
            c = discardPile.TopCard();
            drawPile.InsertCardAtBottom(c);
            discardPile.PopCard();
        }
        drawPile.ShuffleDeck(); //reshuffle the new draw pile
    }

    void PrintDrawPile(){
        drawPile.PrintDeck();
    }
    void PrintHand(){
        hand.PrintHand();
    }
    void PrintDiscardPile(){
        discardPile.PrintDeck();
    }
    void PrintAllDecks(){
        cout << endl << "For Debug:" << endl << "Discard Pile:" << endl;;
        PrintDiscardPile();
        cout << endl << "Draw Pile:" << endl;
        PrintDrawPile();
        cout << endl << "Player hand:" << endl;
        PrintHand();
    }
    //Returns the size of the deck
    int DeckSize(){
        return hand.DeckSize();
    }
};

//Set up and shuffle the player and enemy decks
void SetUpDecks(Player& player, Player& enemy){
    player.SetUpPlayer();
    player.drawPile.ShuffleDeck();
    enemy.SetUpEnemy();
    enemy.drawPile.ShuffleDeck();
}

//This is Phase 1 according to my mockup
void EnemyPhase(Player& enemy){
    cout << "Enemy Phase: The enemy will draw cards." << endl;
    cin.ignore();
    enemy.DrawEnemyHand();
    cout << "The enemy's hand is currently:" << endl;
    enemy.PrintHand();
}

//Only gets called on the first round, and only one time
//If the enemy draws face cards on the first round, those get sent to the bottom of their draw pile and new cards replace them
void EnemyRedraw(Player& enemy){
    bool redraw = false; //This variable is used to know whether or not to print the redraw message
    //Look through the enemy draw pile, if there's any face cards then swap them out
    for(int i = 0; i < enemy.DeckSize(); i++){
        //Checks the enum value to see if it's a face card
        if(enemy.hand.GetRank(i) == 11 || 
           enemy.hand.GetRank(i) == 12 || 
           enemy.hand.GetRank(i) == 13 || 
           enemy.hand.GetRank(i) == 14){
            
            //if it is a face card, first copy that card to the bottom of the enemy draw pile,
            //then remove the card from the enemy hand,
            //then draw a new card from the drawpile and place it in the same spot that the previous card was
            //then set redraw to true so that it doesn't run again. The enemy can only redraw once, if you get more face cards tough luck!
            Card c = enemy.hand.GetCard(i);
            enemy.drawPile.InsertCardAtBottom(c);
            enemy.hand.RemoveCard(i);
            enemy.hand.DrawCard(enemy.drawPile, i);
            redraw = true;
        }           
    }
    if(redraw){
        cout << "Face cards found and replaced - new enemy hand is:" << endl;
        enemy.PrintHand();
    }     
}

//Prompts the user to select cards using the inputs 1-4, which will corrospond to cards currently in their hand 
//For use with the discard phase, as well as the capture phase
//WHAT HAPPENS IF THE USER DOESN'T ENTER ANYTHING?
vector<int> PlayerCardChoices(){
    //All this code is from some function I found online on how to parse through a csv string. It stores all the values in the vector cardChoices.
    vector<int> cardChoices;
    string cardNums;
    bool inputFailed = true;
    bool isDigit = false, one = false, two = false, three = false, four = false; //prevents duplicates from being entered
    string substr;
    int choice;

    getline(cin, cardNums);

    while(inputFailed){
        inputFailed = false; //set the flag, then reset it if any checks don't pass
      
        stringstream ss(cardNums);
        //parse through the string of numbers and separate them, convert them to integers, and put them into the vector cardChoices
        if(!cardNums.empty()){ //first make sure the user entered something
            while(ss.good()){
                getline(ss, substr, ',');
                for(char const &c : substr){ //first make sure the current substring is actually a digit
                    if(isdigit(c) == 0){
                        isDigit = false;
                        break;
                    }    
                    else{
                        isDigit = true;
                    }
                }
                //if it is a digit convert it to an int and make sure it's 1-4, store it in the array of choices, and flip the boolean flag so no duplicates get entered
                if(isDigit == true){
                    choice = stoi(substr);
                    if(choice == 1 && one == false){
                        cardChoices.push_back(choice);
                        one = true;
                    }
                    else if(choice == 2 && two == false){
                        cardChoices.push_back(choice);
                        two = true;
                    }
                    else if(choice == 3 && three == false){
                        cardChoices.push_back(choice);
                        three = true;
                    }
                    else if(choice == 4 && four == false){
                        cardChoices.push_back(choice);
                        four = true;
                    }
                    else{
                        cout << choice << " is a duplicate or invalid number." << endl;
                        inputFailed = true;
                    }
                    isDigit = false; //reset the flag for the next substring
                }
                else{
                    cout << substr << " is not a valid input and will be ignored." << endl;
                    inputFailed = true;
                }
            }
        }
        else{
            inputFailed = false; //this means the user didn't enter anything, thus the code will return the empty vector
            return cardChoices;
        }
        if(inputFailed == true){ //have the user enter again
            cout << "Input failed, try again:";
            getline(cin, cardNums);
        }
    }
    sort(cardChoices.begin(), cardChoices.end()); //this makes the capture function run more smoothly :)
    return cardChoices;

    //PUT SOMETING HERE WHERE IT RETURNS IF THE VECTOR IS EMPTY TO SKIP ENTRIES
}

//This is Phase 2+3 according to my mockup
//Discard cards from the player hand (whichever one) 
void DiscardPhase(Player& player){
    bool handChanged = false; //flag used for "your hand did not change" message

    //FOR DEBUGGING
    cout << "PLAYER DECK CHECK BEFORE DISCARD PHASE" << endl;
    player.PrintAllDecks();

    //If it's the first turn, the player will not yet have any cards in his hand, in which case skip over the discard section but then draw a hand
    if(player.hand.DeckSize() > 0){
        cout << "Draw Phase: You may discard any number of cards from your hand." << endl;
        cout << "Your hand is currently:" << endl;
        player.PrintHand();

        cout << endl << "Enter the cards you would like to discard with commas separating them and no spaces (i.e. '1,2,4') or nothing if you don't want to discard anything:" << endl;
        vector<int> cardChoices = PlayerCardChoices(); //This function takes care of the user's input and error-handling

        if(cardChoices.size() > 0){ 
            //MAKE THIS A PLAYER FUNCTION SOME DAY??
            //Parse through the choices and remove those cards
            //Since we've verified the choices and not duplicates and are actually numbers, we only need to go through them incrementally here
            for(int i = 0; i < cardChoices.size(); i++){
                if((cardChoices[i] - 1) >= player.hand.DeckSize()){ //this takes care of if the player starts this function with a hand of less than 4
                    cout << "There is no card #" << cardChoices[i] << " silly!" << endl;
                }
                else{ //move the card to the discard pile
                    Card c = player.hand.GetCard(cardChoices[i] - 1); //move the card into the discard pile
                    player.discardPile.InsertCardAtBottom(c);
                    player.hand.RemoveCard(cardChoices[i] - 1); //remove it from the hand
                    if(player.drawPile.DeckSize() <= 0){ //If there's no more cards to draw from the player's deck we need to move the cards from the discard pile and reshuffle them
                        player.ReshuffleDrawPile();
                        cout << "Draw pile empty, reshuffling the player's discard pile..." << endl;
                    }
                    player.hand.DrawCard(player.drawPile, cardChoices[i] - 1); //draw a new card and place it where the other card was removed for readability    
                }            
            }
            player.DrawPlayerHand(); //If the player had less than 4 cards at the beginning of the drawphase, this will complete their hand
            cout << "PLAYER DRAWHAND 1 TRIGGERED" << endl; //DEBUG
            cout << "Your new hand is..." << endl;
            player.PrintHand();
        }
        else if(player.hand.DeckSize() < 4){ //if the user entered the discard phase with less than a full hand and didn't change any cards, they need to draw up to 4
            player.DrawPlayerHand(); //complete the player's hand
            cout << "PLAYER DRAWHAND 2 TRIGGERED" << endl; //DEBUG
            cout << "Your new hand is..." << endl;
            player.PrintHand();
        }
        else{ //the user didn't enter anything 
            cout << "Your hand did not change." << endl;
        }
    }
    else{
        player.DrawPlayerHand();
        cout << "PLAYER DRAWHAND 3 TRIGGERED" << endl; //DEBUG
        cout << endl << "You drew a hand of 4 cards, your hand is currently:" << endl;
        player.PrintHand();
    }
}

//Used in the CapturePhase function, allows the player to attempt to capture an enemy's card
bool PlayerCapture(Player& player, Player& enemy){
    cout << "You may now attempt to capture an enemy's card. Enter the cards you would like to use (i.e. 1,2,4) or nothing to skip: " << endl;
    cout << "Current enemy hand: " << endl;
    enemy.PrintHand();

    vector<int> cardChoices = PlayerCardChoices(); //Record the input from the player and put it in the vector cardChoices

    Card suitChecker, biggestCard = {SPADES, TWO}; //must initializes biggestCard any suit smallest card to avoid getting junk later, this variable will keep track of the biggest card
    vector<int> pointValues;
    int pointsToSpend = 0, numberOfJokers = 0, captureChoice;
    bool sameSuit = true;

    //BUG: WHAT IF THE PLAYER ONLY SELECTED A JOKER
    //ensure that the user has entered at least one choice 
    if(cardChoices.size() > 0){  
        //loop 1 for error-checking, keep track of the suit, the biggets value card, and the number of jokers
        for(int i = 0; i < cardChoices.size(); i++){
            Card c = player.hand.GetCard(cardChoices[i] - 1);
            if(c.rank == JOKER){
                numberOfJokers++;
            }
            else{
                if(c.rank >= biggestCard.rank){ //keep track of the biggest card so we know which card to duplicate if there's a joker(s)
                    biggestCard = c;
                }
                suitChecker = c; //suitChecker will be whatever the last non-joker card is, which is fine. We just need a reference point for a selected suit.
            }
        }

        //loop 2 for actual data processing
        for(int i = 0; i < cardChoices.size(); i++){
            Card c = player.hand.GetCard(cardChoices[i] - 1);
            if(c.rank != JOKER){ //if the card isn't a joker, add to the total
                pointsToSpend += c.rank;
            }
            if(c.suit != suitChecker.suit && c.rank != JOKER){ //if the card isn't a joker and the suit doesn't match the suitChecker, then someone entered cards of the wrong suit
                sameSuit = false;
            }
        }
       
        //calculate the total points to spend with jokers
        for(int i = 0; i < numberOfJokers; i++){
            pointsToSpend += biggestCard.rank;
        }

        //if the cards aren't the same suit forget the rest of this (MAYBE PUT THIS EARLIER IN THE FUNCTION SO IT DOESN'T RUN ALL THE CALCS FIRST?)         
        if(!sameSuit){ 
            cout << "The cards must be of the same suit." << endl;
        }
        else{
            cout << "You have [" << pointsToSpend << "] points of suit [";
            suitChecker.PrintSuit();
            cout << "] to spend." << endl;
            cin.ignore();
            
            cout << "Select the enemy card you would like to capture:" << endl;
            enemy.PrintHand();
            cout << endl << "Enter your choice (1,2,3,4): " << endl;
            
            //This section takes care of error-handling with the captureChoice input, ensuring that it is a digit 1-4
            int captureChoice = 0;
            cin >> captureChoice;
            if(cin.fail() || captureChoice < 1 || captureChoice > 4){
                cout << "That isn't a valid choice, it has to be 1-4!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else{ 
                //if the enemy has less than 4 cards make sure that the player's choice is a valid option
                if(enemy.DeckSize() < captureChoice){
                    cout << "The enemy doesn't have that many cards!" << endl;
                }
                //If the player has enough points and is using the right suit, they will capture the enemy's card
                else{
                    Card c = enemy.hand.GetCard(captureChoice - 1);
                    if(c.suit == suitChecker.suit && pointsToSpend >= c.rank){
                        c.PrintCard();
                        cout << " successfully captured!" << endl;
                        //move the enemy card into the player's discard pile and remove it from their hand
                        player.discardPile.InsertCardAtBottom(c);
                        enemy.hand.RemoveCard(captureChoice - 1);
                    
                        //Iterate backwards so there's no issues with the index after removing a card (the cardChoices vector is sorted)
                        for(int i = cardChoices.size() - 1; i >= 0; i--){
                            Card c = player.hand.GetCard(cardChoices[i] - 1); //move the card into the discard pile
                            player.discardPile.InsertCardAtBottom(c);
                            player.hand.RemoveCard(cardChoices[i] - 1); //remove it from the hand           
                        }
                        return true; //this is the only place this function can return true
                    }
                    else{ //print appropriate error messages
                        if(c.suit != suitChecker.suit){ 
                            cout << "Unable to capture, that card is of a different suit!" << endl; 
                        }
                        else{ 
                            cout << "Unable to capture, your card isn't strong enough to capture the enemy's card!" << endl;
                        }
                    }
                }          
            }
        }
    }
    else{
        cout << "You did not attempt to capture a card." << endl;
    }
    return false; //function will always return false unless it gets all the way into the innermost if statment
}

//Used in the CapturePhase function, allows the player to either sacrifice two cards to send an enemy card away or the enemy to capture a player's card
void EnemyCapture(Player& player, Player& enemy, bool& gameOver){
    string choice;
    vector<int> cardChoices;
    cout << "Do you want to sacrifice two cards?" << endl << endl << "Enter 'y' for yes or 'n' for no: " << endl;

    //Get the user's input and ensure it's valid
    getline(cin, choice);
    while(cin.fail() || (choice != "y" && choice != "n")){
        cout << "That isn't a valid choice, it has to be 'y' or 'n'! Enter your choice again:" << endl;
        getline(cin, choice);
    }

    if(choice == "y"){ //This runs if the player decides to trash two cards to move the enemy's last card to the bottom of the draw pile
        cout << "Select your two cards to trash with commas separating them and no spaces (i.e. 1,3):" << endl;
        cout << "REMEBER if you discard a face card it's game over! Your hand is currently:" << endl;
        player.PrintHand();
        
        cardChoices = PlayerCardChoices(); //This function takes care of the user's input and error-handling
        while(cardChoices.size() != 2){ //using this loop to repurpose 
            cout << "You need to choose exactly 2 cards. Please re-enter your choice: " << endl;
            cardChoices = PlayerCardChoices();
        }

        cout << "You sacrificed:";
        for(int i = 0; i < cardChoices.size(); i++){
            Card c = player.hand.GetCard(cardChoices[i] - 1);
            cout << endl;
            c.PrintCard();
            if(c.rank > 10 && c.rank < 15){ //if a face card is going into the enemy's discard pile the gameOver flag is tripped
                cout << "GAME OVER 1 TRIGGERED" << endl; // DEBUG
                gameOver = true;
                return; //don't bother running anything else if the game's over
            }
        }

        cout << endl;
        cout << "These cards sent the enemy's ";
        Card c = enemy.hand.TopCard(); //this will always be the enemy's last card
        c.PrintCard(); 
        cout << " to the bottom of their draw pile." << endl;
        
        //Move the last enemy card to the bottom of their draw pile
        enemy.drawPile.InsertCardAtBottom(c);
        enemy.hand.PopCard();

        //Move the player's cards to the enemy discard pile 
        for(int i = cardChoices.size() - 1; i >= 0; i--){
            Card c = player.hand.GetCard(cardChoices[i] - 1); //move the card into the discard pile
            //Check for game over
            if(c.rank > 10 && c.rank < 15){ //if a face card made it into the enemy's discard pile the gameOver flag is tripped
                cout << "GAME OVER 2 TRIGGERED" << endl; //DEBUG 
                gameOver = true;
            return; //don't bother running anything else if the game's over
        }
            enemy.discardPile.InsertCardAtBottom(c);
            player.hand.RemoveCard(cardChoices[i] - 1); //remove it from the hand           
        }
    }
    else{ //this happens if the player decides to let the enemy capture of of their cards (takes the player's chosen card and the last enemy card to the enemy's discard pile)
        cout << "Ok then the enemy will use his last card capture one of your cards and take then both to the enemy discard pile!" << endl << endl;
        cout << "Which card of yours should the enemy capture? (Enter 1-4):" << endl;
        cout << "Your hand is currently:" << endl;
        player.PrintHand();
       
        cardChoices = PlayerCardChoices(); //This function takes care of the user's input and error-handling
        //WHAT HAPPENS IF YOU ENTER DUPLICATE NUBMERS?
        while(cardChoices.size() != 1){
            cout << "You need to choose a card. Please re-enter your choice: " << endl;
            cardChoices = PlayerCardChoices();
        }
        cout << "The enemy's ";
        Card c1 = enemy.hand.TopCard(); //get the last card in the enemy's hand 
        c1.PrintCard(); 
        cout << " took itself and your ";
        Card c2 = player.hand.GetCard(cardChoices[0] - 1); //We can hard-code the first index of cardChoices because it's always going to only be one entry long
        c2.PrintCard();
        cout << " to their discard pile!" << endl;

        if((c1.rank > 10 && c1.rank < 15) || (c2.rank > 10 && c2.rank < 15)){ //if a face card made it into the enemy's discard pile the gameOver flag is tripped
            cout << "GAME OVER 3 TRIGGERED" << endl; //DEBUG
            gameOver = true;
            return; //don't bother running any more calculations if the game is over
        }
        //Move both cards to the enemy's discard pile
        enemy.discardPile.InsertCardAtBottom(c1);
        enemy.hand.PopCard();
        enemy.discardPile.InsertCardAtBottom(c2);
        player.hand.RemoveCard(cardChoices[0] - 1);
    }
}

//Things to add:
//Move the input section into a function and use it in both the discard phase and capture phases
void CapturePhase(Player& player, Player& enemy, bool& gameOver){
    if(PlayerCapture(player, enemy)){
        cout << "Since you captured an enemy's card they don't get a chance to capture one of yours this turn!" << endl << endl;
    }
    else{
        cout << "Since you did not capture an enemy's card, it's their turn to capture one of yours!\n" << endl
             << "OR you can sacrifice two of your cards to send the last enemy card to the bottom of their draw deck." << endl;
        EnemyCapture(player, enemy, gameOver);
    }
}

int main(){
    //Initialize Players and bool to see if the game is still in play
    Player player;
    Player enemy;     
    bool stillPlaying = true; 
    bool firstRound = true;
    bool gameOver = false;
    bool won = false;
    
    SetUpDecks(player, enemy); //Set up the decks and draw 4 cards to start the game

    cout << "Welcome to Card Capture! This game is still in development..." << endl;
    cin.ignore();

    //GAMEOVER WILL CHANGE IF A FACE CARD GETS TO THE ENEMY DISCARD PILE OR IF THERE ARE NO MORE CARDS IN THE ENEMY DECK
    while(gameOver == false){   
        EnemyPhase(enemy);
        //If the enemy draws face cards, they are placed at the bottom of the enemy draw deck and new cards are drawn
        //This can only happen once and only on the first round
        if(firstRound){
            cin.ignore();
            EnemyRedraw(enemy);
            firstRound = false;
        }

        //Win condition check
        //Put this here because if the player sends the last enemy card to their drawpile the enemy needs to redraw before we know for sure if their hand is empty
        if(enemy.DeckSize() <= 0){
            gameOver = true;
            won = true;
            cout << "The enemy is out of cards! ";
            break;
        }

        DiscardPhase(player);
        cin.ignore();
        
        CapturePhase(player, enemy, gameOver);
        cin.ignore();
    }
    if(won){
        cout << "Congratulations, you won! :)" << endl;
    }
    else{
        cout << "GAME OVER. Better luck next time!" << endl;  
    }
    
    //FOR DEBUGGING
    //player.PrintAllDecks();
    //enemy.PrintAllDecks();
}