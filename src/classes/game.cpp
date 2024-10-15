#include "game.h"

Game::Game(int playerCount) { 
    for (int i = 0; i < PLAYERCOUNT; i++) {
        currentPlayers.emplace_back(Players(i, PLAYERMONEY, PLAYERBET));
    }
    for (int i = 0; i < 5; i++) {
        communityCards[i][0] = -1;
        communityCards[i][1] = -1;
    }
}

void Game::gameLoop() {
        std::cout << "There are " << PLAYERCOUNT - bustedPlayerCount << " players." << std::endl;
        std::cout << "Player initialization complete.\n";
        while (wantToPlay)
        {
            initGlobals();
            dealFirstCards();
            updatePlayerHands();
            std::cout << std::endl;
            for (int i = 0; i < 3; i++) {
                takeActions();
                switch (i){
                case 0:
                    dealCommunityCards(3);
                    break;

                default:
                    dealCommunityCards(1);
                    break;
                }

                updatePlayerHands();
                takeActions();
            }
            std::cout << std::endl;
            for (auto&  player : currentPlayers) {
                player.getHeldCards(3, true);
            }
            displayCommunityCards();
            scoreHands();
            std::cout << "Game over.\n";
            std::cout << "There are " << PLAYERCOUNT - bustedPlayerCount << " players left.\n";
            do{
                std::cout << "Do you want to play again? (1 = yes, 0 = no)\n";
                std::cin >> wantToPlay;

                if (std::cin.fail() || (wantToPlay != 1 && wantToPlay != 0)) {//invalid input, loop again
                    std::cin.clear(); // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                    std::cout << "Invalid input. Please enter 1 for yes or 0 for no.\n";
                }   
                else {// Valid input, reset the game and break the loop
                    for (auto& player : currentPlayers) { //soft reset player data
                        player.resetPlayer();
                    }
                    for (int i = 0; i < 5; i++) {
                        communityCards[i][0] = -1;
                        communityCards[i][1] = -1;
                    }
                    dealtCommunityCards = 0;
                    break; 
                }
            } while (true);
            
            
        }


            
        //TODO: game loop should actually be a loop, not just a sequence of events

    }

void Game::debugMode() {
    dealFirstCards();
    updatePlayerHands();
    setCommunityCards(0, 9, 2, 3, 0, 10, 0, 11, 0, 12); 

    for (auto&  player : currentPlayers) {
        player.getHeldCards(3, true);
    }
    
    displayCommunityCards();
    scoreHands();
}

void Game::setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5){
    communityCards[0][0] = s1;
    communityCards[0][1] = r1;
    updatePlayerHands();
    communityCards[1][0] = s2;
    communityCards[1][1] = r2;
    updatePlayerHands();
    communityCards[2][0] = s3;
    communityCards[2][1] = r3;
    updatePlayerHands();
    communityCards[3][0] = s4;
    communityCards[3][1] = r4;
    updatePlayerHands();
    communityCards[4][0] = s5;
    communityCards[4][1] = r5;
    updatePlayerHands();
    }

void Game::displayCommunityCards() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Community card " << i + 1 << " is: ";
        displayCard(communityCards[i][0], communityCards[i][1]);
        std::cout << std::endl;
    }
}

void Game::dealCommunityCards(int amount) {
    for (int i = 0; i < amount; i++)
    {    
        if (communityCards[dealtCommunityCards][0] == -1 && communityCards[dealtCommunityCards][1] == -1) {
            dealCard(1);
            communityCards[dealtCommunityCards][0] = dealtSuit;
            communityCards[dealtCommunityCards][1] = dealtRank;
            std::cout << "Community card " << dealtCommunityCards + 1 << " is: ";
            displayCard(communityCards[dealtCommunityCards][0], communityCards[dealtCommunityCards][1]);
            dealtCommunityCards++;
        }
        else {
            std::cout << "Community card " << dealtCommunityCards + 1 << " has already been dealt.\n";
        }
    }
}

int Game::getCommunityCard(int selectedSlot) {
    if (selectedSlot >= 0 && selectedSlot <= 4) {
        return communityCards[selectedSlot][0], communityCards[selectedSlot][1];
    }
    else {
        std::cout << "Invalid community card slot selected at Game::getCommunityCard.\n";
        return 0;
    }
}

void Game::takeActions() {
    //TODO: implement betting
}

void Game::updatePlayerHands() { 
    // Copy held cards to pWideHand for each player
    for (auto& player : currentPlayers) {
        for (int i = 0; i < 2; i++) {
            player.pWideHand[i][0] = player.heldCards[i][0];
            player.pWideHand[i][1] = player.heldCards[i][1];
        }
    }

    // Copy community cards to pWideHand for each player
    for (int i = 0; i < 5; i++) {
        for (auto& player : currentPlayers) {
            player.pWideHand[i + 2][0] = communityCards[i][0];
            player.pWideHand[i + 2][1] = communityCards[i][1];
        }
    }
}

void Game::scoreHands() {
    std::vector <std::vector <int>> playerScores;
    for (Players& player : currentPlayers) {
        std::cout << "\n\n\n";
        std::cout << ">---Player " << player.getPlayerID() + 1 << "---<\n";
        std::cout << "Calling flush\n";
        player.testNewScore(flush(player.getPlayerID()));
        std::cout << "Calling straight\n";
        player.testNewScore(straight(player.getPlayerID()));
        std::cout << "Calling dupes\n";
        player.testNewScore(duplicate(player.getPlayerID()));
        playerScores.push_back(player.getPlayerScore());
    }

    std::vector<int> highestScore;
    highestScore.push_back(-1);
    int winningPlayerID = -1;
    
    for (int i = 0; i < currentPlayers.size(); i++) {
        int playerScore = playerScores[i][0]; // First element is the main score.
        if (playerScore > highestScore[0]) {
            highestScore = playerScores[i];
            winningPlayerID = currentPlayers[i].getPlayerID();
        }
        else if (playerScore == highestScore[0]){
            for (int j = 1; j < playerScores[i].size(); j++){
                if (zeroFirstDesc(playerScores[i][j], highestScore[j])){
                    highestScore = playerScores[i];
                    winningPlayerID = currentPlayers[i].getPlayerID();
                }
                else if (playerScores[i][j] < highestScore[j]){
                    break;
                }
            }
        }
    }

    std::cout << "The winner is Player " << winningPlayerID + 1 << " with a score of " << highestScore[0] << "!\n";
    
}

std::vector<int> Game::flush(int id) {
    std::vector <int> flushedCards;
    Players* analyzedPlayer = findPlayerByID(id);
    if (analyzedPlayer == nullptr) {
        throw std::runtime_error("findPlayerByID() returned nullptr.");
    }
    std::vector <int> score;
    std::string flushSuit = "None";
    //i think flushCounter may not be needed
    int flushCounter = 0;
    //flush counters for each suit //this can also be done by checking the size of the vectors. idk which is better performance wise.
    int Fspades = 0;
    int Fclubs = 0;
    int Fdiamonds = 0;
    int Fhearts = 0;

    //all the vectors are used to store the ranks of the cards of the same suit.
    std::vector <int> spades;
    std::vector <int> clubs;
    std::vector <int> diamonds;
    std::vector <int> hearts;
    for (int i = 0; i < 7; i++) {                                   //checks for a cards suit and adds the RANK to the corresponding vector.
        
        switch (analyzedPlayer->pWideHand[i][0])                        //this vector is later passed to straight() to check for a straight (or royal) flush by checking the ranks.
        {
        case 0:
            Fspades++;
            spades.push_back(analyzedPlayer->pWideHand[i][1]);
            break;
        case 1:
            Fclubs++;
            clubs.push_back(analyzedPlayer->pWideHand[i][1]);
            break;
        case 2:
            Fdiamonds++;
            diamonds.push_back(analyzedPlayer->pWideHand[i][1]);
            break;
        case 3:
            Fhearts++;
            hearts.push_back(analyzedPlayer->pWideHand[i][1]);
            break;
        }
    }
    
    if (Fspades >= 5){                                              //checks for a flush and sets the flushSuit and flushCounter accordingly.
        flushCounter = Fspades;
        flushSuit = "Spades";
        flushedCards = spades;                                      //this is a workaround for the straight() function. we pass the vector of ranks of the flushed suit to check for a straight flush.
    }
    else if (Fclubs >= 5){
        flushCounter = Fclubs;
        flushSuit = "Clubs";
        flushedCards = clubs;
    }
    else if (Fdiamonds >= 5){
        flushCounter = Fdiamonds;
        flushSuit = "Diamonds";
        flushedCards = diamonds;
    }
    else if (Fhearts >= 5){
        flushCounter = Fhearts;
        flushSuit = "Hearts";
        flushedCards = hearts;
    }
    
    if (flushCounter >= 5) {                                        //if the flushCounter is 5 or more, the player has a flush.
        std::cout << "Player " << id + 1 << " has a flush of " << flushSuit << "!\n";
        score = straight(id, true, flushedCards);                   //we call straight() with the flushedCards vector to check for a straight flush.
        return score;
    }
    else {
        score.push_back(HIGHCARDSCORE);
        return score;
    }
}

std::vector<int> Game::straight(int id, bool shortHand, std::vector <int> flushedCards) {
    //do NOT read further if you value your sanity
    Players* analyzedPlayer = findPlayerByID(id);
    if (analyzedPlayer == nullptr){
        throw std::runtime_error("findPlayerByID() returned nullptr.");
    }
    std::vector <int> score;
    int sCounter = 1;                                                       //counter for the straight is initialized to 1 because the first card will already be in the array.
    bool straight = false;                                                  //straight is set to false by default.
    int currentStraight[5];                                                 //currentStraight[] is used to check for a straight and also store it after the straight is completed.
    setArrayToValue(currentStraight, 5, -1);
    if (shortHand == false){                                                //this block is called only to check for a straight. flush+straight combinations are checked in the else block.  
        int ranks[7];                                                       //ranks[] is used to store the ranks of the player's hand.
        for (int i = 0; i < 7; i++) {
            ranks[i] = analyzedPlayer->pWideHand[i][1];
        }
        int n = sizeof(ranks) / sizeof(ranks[0]);
        std::sort(ranks, ranks + n, std::greater<int>());                   //ranks is sorted in descending order.
        currentStraight[0] = ranks[0];
        for (int i = 0; i < 7; i++) {
            if ((currentStraight[0] == 12) && (currentStraight[1] == 11) && (currentStraight[2] == 10) && (currentStraight[3] == 9)){ //checks if the current hand has a chance to be a broadway.
                for (int j = i; j < 7; j++ ){
                    if (ranks[j] == 0){
                        currentStraight[4] = 0;                                //if the player has an ace, we add it to the end of the array. [12, 11, .., 0]
                        std::cout << "Player " << id + 1 << " has a Broadway Straight!" << std::endl;
                        straight = true;
                        break;
                    }
                }
            }
            if(straight){                                                   //if the player has a broadway, we break the loop. not sure if this is needed tho.
                break;
            }
                
            else if (ranks[i] - ranks[i + 1] == 1) {                        //typical straight check.     
                currentStraight[sCounter] = ranks[i+1];
                sCounter++;                                                     
                if (sCounter >= 5){                                             
                    straight = true;                                            
                    break;
                }
            }
            else if (ranks[i] - ranks[i + 1] == 0) {                        //the straight hasn't broken yet but didn't continue either. so we don't touch it.
                    //wtf is this shit
                    //maybe should've used a switch
                    //anyways do nothing so maybe the straight will continue
                    //TODO: commit suicide
            }
            else {                                                          //the straight is broken :(
                //reset the counter and currentStraight
                for (int j = 0; j < 5; j++){
                    currentStraight[j] = -1;
                }
            sCounter = 1;
            }
        }
        if (straight){
            std::cout << "Player " << id + 1 << " has a straight!\n";
            score.push_back(STRAIGHTSCORE);
            for (int i = 0; i < 5; i++){
                score.push_back(currentStraight[i]);
            }
        }
        else{
            std::cout << "Player " << id + 1 << " does not have a straight.\n";
            score.push_back(HIGHCARDSCORE);
        }
    }   
    else {//this block is called when a player already has flush and we want to check for straight or royal flush //most of this is documented in the if statement above
        bool royal = false;
        sort(flushedCards.begin(), flushedCards.end(), std::greater<int>());
        currentStraight[0] = flushedCards[0];
        for (int i = 0; i < flushedCards.size(); ++i){
            std::cout << flushedCards[i] << " ";
        }
        for (int i = 0; i < flushedCards.size(); i++) {
            if ((currentStraight[0] == 12) && (currentStraight[1] == 11) && (currentStraight[2] == 10) && (currentStraight[3] == 9)){
                for (int j = i-1; j < flushedCards.size(); j++ ){
                    if (flushedCards[j] == 0){
                        currentStraight[4] = 0; //this is a workaround for the ace being the last card in the hand. so we just add it to the end of the array. [9, 10, 11, 12, 0] // isn't it [12, 11, 10, 9, 0]?
                        royal = true;
                        straight = true;
                        sCounter++;
                        break;
                    }
                }
            }
            if(straight){
                break;
            }
                
            else if (flushedCards[i] - flushedCards[i + 1] == 1) {                             
                currentStraight[sCounter] = flushedCards[i+1];
                sCounter++;                                                     
                if (sCounter >= 5){                                             
                    straight = true;                                            
                    break;
                }
            }
            else if (flushedCards[i] - flushedCards[i + 1] == 0) {                            

            }
            else {
                //reset the counter and currentStraight
                for (int j = 0; j < 5; j++){
                    currentStraight[j] = -1;
                }
                sCounter = 1;
            }
            }
        if (straight && royal){
            std::cout << "Player " << id + 1 << " has a Royal Flush!" << std::endl;
            score.push_back(ROYALFLUSHSCORE);
        }
        else if (straight && !royal){
            std::cout << "Player " << id + 1 << " has a straight flush!\n";
            score.push_back(STRAIGHTFLUSHSCORE);
            int n = sizeof(currentStraight) / sizeof(currentStraight[0]);
            std::sort(currentStraight, currentStraight + n, zeroFirstDesc);
            for (int i = 0; i < 5; i++){
                score.push_back(currentStraight[i]); //should be taking the Ace into account now.
            }
        }
        else if (!straight){
            std::cout << "Player " << id + 1 << " does not have a straight flush.\n";
            score.push_back(FLUSHSCORE);
            std::sort(flushedCards.begin(), flushedCards.end(), zeroFirstDesc);
            for (int i = 0; i < 5; i++){
                score.push_back(flushedCards[i]);
            }
        }

    }
    return score;
}

std::vector<int>Game::duplicate(int id) {
    /**
     * @brief This vector will be returned when evaluation finishes.
     */
    std::vector<int> score;
    /**
     * @brief Currently analyzed player for duplicates.
     */
    Players* analyzedPlayer = findPlayerByID(id);

    //yeet if no pointer
    if (analyzedPlayer == nullptr){
        throw std::runtime_error("findPlayerByID() returned nullptr.");
    }


    int duplicateCards[13];
    int ranks[7];

    int pairs[3];
    int pairCounter = 0;

    int trios[2];
    int trioCounter = 0;

    int quad = -1;
    int quadCounter = 0;
    
    setArrayToValue(duplicateCards, 13, 0);
    setArrayToValue(ranks, 7, -1);
    setArrayToValue(pairs, 3, -1);
    setArrayToValue(trios, 2, -1);


    for (int i = 0; i < 7; i++) { //get ranks to the ranks array.
        ranks[i] = analyzedPlayer->pWideHand[i][1];
    }

    //Sort ranks

    int n = sizeof(ranks) / sizeof(ranks[0]);
    std::sort(ranks, ranks + n, zeroFirstDesc);

    //Loop through cards.
    std::cout << "Player " << id+1 << " has the following cards: ";
    for (int i = 0; i < 7; i++) {
        displayCard(-1, ranks[i]);
        switch (i){
        case 6:
            std::cout << " ";
            break;
        
        default:
            std::cout << ", ";
            break;
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < 7; i++) { //add cards to duplicateCards
        duplicateCards[ranks[i]]++;
    }

    //Tally for cards

    for (int i = 0; i < 13; i++) {
        switch (duplicateCards[i]){
            case 2:
                pairs[pairCounter] = i;
                pairCounter++;
                break;
            case 3:
                trios[trioCounter] = i;
                trioCounter++;
                break;
            case 4:
                quad = i;
                quadCounter++;
                break;
            default:
                break;
        }
    }
    //This is where evaluation finalizes and returns the best (dupe related) score.
    //For this if chain, H = High Card(s), P = Paired Card(s), T = Trio Card, Q = Quad Card. S = Score of the hand. S values can be found in globals.cpp/.h. 

    //Four of a kind
    if (quadCounter == 1){
        for (int i = 0; i < 7; i++){
            if (ranks[i] == quad){
                ranks[i] = -1;
            }
        }

        //sort

        n = sizeof(ranks) / sizeof(ranks[0]);
        std::sort(ranks, ranks + n, zeroFirstDesc);

        //store

        score.push_back(FOUROFAKINDSCORE);
        score.push_back(quad);
        score.push_back(ranks[0]);

        //output

        std::cout << "Player " << analyzedPlayer->getPlayerID() + 1 << " has four of ";
        displayCard(-1, quad);
        std::cout <<"s!\n";

        //score should have score first, then quad, then the remaining high card. Like so -> <S, Q, H>
        return score;
    }
    //Full house
    else if (trioCounter > 0 && pairCounter > 0){
        //no need to remove dupes since there is no high cards.

        //sort

        n = sizeof(trios) / sizeof(trios[0]);
        std::sort(trios, trios + n, zeroFirstDesc);
        std::sort(pairs, pairs + n, zeroFirstDesc);
        n = sizeof(pairs) / sizeof(pairs[0]);
        
        //store

        score.push_back(FULLHOUSESCORE);
        score.push_back(trios[0]);
        score.push_back(pairs[0]);

        //output
        
        std::cout << "Player " << analyzedPlayer->getPlayerID() + 1 << " has a full house of three ";
        displayCard(-1, trios[0]);
        std::cout << "s and two ";
        displayCard(-1, pairs[0]);
        std::cout << "s!\n";

        //this vector contains all the cards in the hand. so no high card is needed. <S, T, P>
        return score;
    }
    //Three of a kind
    else if (trioCounter > 0){

        //remove dupes

        for (int i = 0; i < 7; i++){
            if (ranks[i] == trios[0]){
                ranks[i] = -1;
            }
        }

        //sort

        n = sizeof(ranks) / sizeof(ranks[0]);
        std::sort(ranks, ranks + n, zeroFirstDesc);

        //store

        score.push_back(THREEOFAKINDSCORE);
        score.push_back(trios[0]);
        for (int i = 0; i < 2; i++){
            score.push_back(ranks[i]);
        }

        //output

        std::cout << "Player " << analyzedPlayer->getPlayerID() + 1 << " has three of ";
        displayCard(-1, trios[0]);
        std::cout << "s!\n";

        //score should be <S, T, H1, H2>
        return score;
    }
    //Two Pair
    else if (pairCounter > 1){

        //remove dupes

        for (int i = 0; i < 7; i++){
            if (ranks[i] == pairs[0] || ranks[i] == pairs[1]){
                ranks[i] = -1;
            }
        }

        //sort

        n = sizeof(ranks) / sizeof(ranks[0]);
        std::sort(ranks, ranks + n, zeroFirstDesc);
        score.push_back(TWOPAIRSCORE);
        n = sizeof(pairs) / sizeof(pairs[0]);
        std::sort(pairs, pairs + n, zeroFirstDesc);

        //store

        score.push_back(pairs[0]);
        score.push_back(pairs[1]);
        score.push_back(ranks[0]);

        //output

        std::cout << "Player " << analyzedPlayer->getPlayerID() + 1 << " has two pairs! A pair of ";
        displayCard(-1, pairs[0]);
        std::cout << "s and a pair of ";
        displayCard(-1, pairs[1]);
        std::cout << "s.\n";

        //score should be <S, P1, P2, H>
        return score;
    }
    //Pair
    else if (pairCounter > 0){

        //remove dupes

        for (int i = 0; i < 7; i++){
            if (ranks[i] == pairs[0]){
                ranks[i] = -1;
            }
        }

        //sort

        n = sizeof(ranks) / sizeof(ranks[0]);
        std::sort(ranks, ranks + n, zeroFirstDesc);
        n = sizeof(pairs) / sizeof(pairs[0]);
        std::sort(pairs, pairs + n, zeroFirstDesc);

        //store

        score.push_back(PAIRSCORE);
        score.push_back(pairs[0]);
        for (int i = 0; i < 3; i++){
            score.push_back(ranks[i]);
        }

        //output

        std::cout << "Player " << analyzedPlayer->getPlayerID() + 1 << " has a pair of ";
        displayCard(-1, pairs[0]);
        std::cout << "s!\n";
        
        //score should be <S, P, H1, H2, H3>
        return score;
    }
    //High card
    else {
        score.push_back(HIGHCARDSCORE);
        for (int i = 0; i < 5; i++){
            score.push_back(ranks[i]);
        }

        //score should be <S, H1, H2, H3, H4, H5>
        return score;
    }
}

void Game::displayHand(int id) {
    Players* analyzedPlayer = findPlayerByID(id);
    if (analyzedPlayer == nullptr){
        throw std::runtime_error("findPlayerByID() returned nullptr.");
    }
    int s;
    int r;
    for (int i = 0; i < 7; i++) {    
        s = analyzedPlayer->pWideHand[i][0];
        r = analyzedPlayer->pWideHand[i][1];
        displayCard(s, r);
    }
    std::cout << std::endl;
    }

void Game::dealFirstCards() { 
        std::cout << "\nDealing one card to each player.\n";
        for (auto&  player : currentPlayers) {
            player.dealToPlayer(1);
        }
        std::cout << std::endl;
        for (auto&  player : currentPlayers) {
            player.getHeldCards(1, true);
        }
        for (auto&  player : currentPlayers) {
            player.dealToPlayer(1);
        }
        std::cout << std::endl;
        for (auto&  player : currentPlayers) {
            player.getHeldCards(2, true);
        }
    }
    
void Game::displayPlayerData(int playerID) {
        for (const auto& player : currentPlayers) {
            if (player.getPlayerID() == playerID){
                std::cout  << "Player ID:" << player.getPlayerID() << std::endl;
                std::cout  << "Player has $" << player.getMoney() << " money, " << player.getBet() << " bet, and has no cards dealt yet.\n";
                return;
            }
        }
    std::cout << "Player ID not found.\n";
    }

Players* Game::findPlayerByID(int id) {
    for (auto& player : currentPlayers) {
        if (player.getPlayerID() == id) {
            return &player;
        }
    }
    return nullptr;
}












