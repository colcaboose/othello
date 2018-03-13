GROUP MEMBER CONTRIBUTIONS

We worked on everything together from one computer at a time. While one person 
typed, the other checked syntax and logic and made suggestions to the person 
typing. This allowed us to progress through debugging much faster and generate 
fewer bugs in the process of typing the code. It also helped to work on the 
same code simultaneously when coming up with the heuristic function and 
minimax tree. We both made sure to comment through our code.

TOURNAMENT IMPROVEMENTS

We first set the value of 'testtingMinimax' to true in player.cpp so that our 
minimax tree would actually be used in the tournament (it was not before). We 
also improved our score function beyond the suggestion in the assignment 
by calculating the increase in number of a single given player's pieces, 
which implicitly also accounts for the number of opponent pieces on the board 
(becuase a player can only increase its pieces by taking the opponent's 
pieces). Our algorithm works by calculating the score of all of our possible moves, then going one level deeper by calculating the opponent's best move in
response to all of our possible moves. We take the difference between these and maximize it, picking the move that gives us this score, essentially maximizing our minimum score.
Our minimax tree also, instead of assuming the opponent minimizes our 
score, will assume that the opponent intends to maximize its score using the 
same heuristic that we are using, which will better predict the intentions of 
the opponent AIs in the tournament.