## Minified Mode1Score.cpp
```cpp
#include "Mode1Score.h"
Mode1Score::Mode1Score(Player* p1,Player* p2,PinInterface* pi,GameState* gs,History* h):_p1(p1),_p2(p2),_gs(gs),_h(h),_tb(p1,p2,pi,gs,h),_pl(p1,p2,pi),_gl(p1,p2,pi),_sl(p1,p2,pi),_w(p1,p2,pi,gs),_u(p1,p2,pi,gs){}
Mode1Score::~Mode1Score(){}
TieBreaker* Mode1Score::gtb(){return &_tb;}
void Mode1Score::ssb(ScoreBoard* sb){
    _sb=sb;_pl.ssb(sb);_gl.ssb(sb);_w.ssb(sb);_sl.ssb(sb);_tb.ssb(sb);_u.ssb(sb);}
ScoreBoard* Mode1Score::gsb(){return _sb;}
void Mode1Score::_rg(){
    _p1->setPoints(0);_p2->setPoints(0);_gs->setPlayer1Points(0);_gs->setPlayer2Points(0);_gs->setServeSwitch(1);_gs->setServe(0);_pl.updatePoints();}
void Mode1Score::us(Player* cp){
    if(_gs->getTieBreak()==1){_tb.run(cp);}else if(_gs->getSetTieBreak()==1){_tb.setTieBreaker();}else{
        Player* op=cp->getOpponent();
        int cpp=cp->getPoints(),opp=op->getPoints();
        if(cpp>=3){
            if(cpp==opp){cp->setPoints(3);op->setPoints(3);}
            else if(cpp>3 && (cpp-opp)>1){
                cp->setGames(cp->getGames()+1);_u.memory();cp->number()==0?m1P1G():m1P2G();
            }
            if(cp->getPoints()==4){_gs->setPointFlash(1);_gs->setPreviousTime(GameTimer::gameMillis());_gs->setToggle(0);}}
        _pl.updatePoints();}}
void Mode1Score::p1s(){us(_p1);}
void Mode1Score::p2s(){us(_p2);}
void Mode1Score::m1P1G(){
    _gs->setServeSwitch(_gs->getServeSwitch()+1);
    if(_p1->getGames()>=GAMES_TO_WIN_SET){
        if(_p1->getGames()==GAMES_TO_WIN_SET && _p2->getGames()==GAMES_TO_WIN_SET){_gs->setTieBreak(1);_tb.initializeTieBreakMode();}
        if(_gs->getTieBreak()==0){
            if((_p1->getGames()-_p2->getGames())>1){
                _p1->setSets(_gs,_p1->getSets()+1);
                if(_p1->getSets()==_p2->getSets()){_tb.setTieBreakEnable();_mode1WinSequences.p1TBSetWinSequence();_gs->setSetTieBreak(1);}
                else if(_p1->getSets()==SETS_TO_WIN_MATCH){_gs->stopGameRunning();_mode1WinSequences.p1MatchWinSequence();}
                else{_mode1WinSequences.p1SetWinSequence();_gs->setCurrentSet(_gs->getCurrentSet()+1);_resetGame();}
                _p1->setGames(0);_p2->setGames(0);}}}
    else{_mode1WinSequences.p1GameWinSequence();_resetGame();}}
void Mode1Score::m1P2G(){
    _gs->setServeSwitch(_gs->getServeSwitch()+1);
    if(_p2->getGames()>=GAMES_TO_WIN_SET){
        if(_p2->getGames()==GAMES_TO_WIN_SET && _p1->getGames()==GAMES_TO_WIN_SET){_gs->setTieBreak(1);_tb.initializeTieBreakMode();_scoreBoard->update();return;}
        if(_gs->getTieBreak()==0){
            if((_p2->getGames()-_p1->getGames())>1){
                _p2->setSets(_gs,_p2->getSets()+1);
                if(_p2->getSets()==_p1->getSets()){_tb.setTieBreakEnable();_mode1WinSequences.p2TBSetWinSequence();_gs->setSetTieBreak(1);}
                else{_mode1WinSequences.p2SetWinSequence();_gs->setCurrentSet(_gs->getCurrentSet()+1);_resetGame();}
                _p1->setGames(0);_p2->setGames(0);}}}
    else{_mode1WinSequences.p2GameWinSequence();_resetGame();}}
void Mode1Score::m1TBP1G(){
    _gs->setServeSwitch(_gs->getServeSwitch()+1);
    if(_p1->getGames()==15 || (_p1->getGames()>=10 && (_p1->getGames()-_p2->getGames())>1)){
        _p1->setSets(_gs,_p1->getSets()+1);
        if(_p1->getSets()==_p2->getSets()){_tb.setTieBreakEnable();_mode1WinSequences.p1TBSetWinSequence();_gs->setSetTieBreak(1);}
        else{_mode1WinSequences.p1SetWinSequence();_tb.endTieBreak();}}}
void Mode1Score::m1TBP2G(){
    _gs->setServeSwitch(_gs->getServeSwitch()+1);
    if(_p2->getGames()==15 || (_p2->getGames()>=10 && (_p2->getGames()-_p1->getGames())>1)){
        _p2->setSets(_gs,_p2->getSets()+1);
        if(_p2->getSets()==_p1->getSets()){_tb.setTieBreakEnable();_mode1WinSequences.p2TBSetWinSequence();_gs->setSetTieBreak(1);}
        else{_mode1WinSequences.p2SetWinSequence();_tb.endTieBreak();}}}
void Mode1Score::m1STBP1G(){
    if(_p1->getGames()==7){_p1->setSets(_gs,_p1->getSets()+1);_mode1WinSequences.p1SetTBWinSequence();_tieBreaker.tieLEDsOff();_mode1WinSequences.p1MatchWinSequence();_gameState->stopGameRunning();}
    _gs->setServeSwitch(_gs->getServeSwitch()+1);}
void Mode1Score::m1STBP2G(){
    if(_p2->getGames()==7){_p2->setSets(_gs,_p2->getSets()+1);_mode1WinSequences.p2SetTBWinSequence();_tieBreaker.tieLEDsOff();_mode1WinSequences.p2MatchWinSequence();_gameState->stopGameRunning();}
    _gs->setServeSwitch(_gs->getServeSwitch()+1);}
```