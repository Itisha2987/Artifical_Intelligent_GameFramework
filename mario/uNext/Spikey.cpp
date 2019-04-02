#include "Spikey.h"
#include "Core.h"
#include "string.h"
#include "CFG.h"
/* ******************************************** */

Spikey::Spikey(int iXPos, int iYPos) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)iYPos + 6;

	this->iHitBoxX = 32;
	this->iHitBoxY = 26;

	this->iBlockID = 52;

	this->startJump(1);

	this->moveSpeed = 0;
}

Spikey::~Spikey(void) {

}

/* ******************************************** */

void Spikey::Update() {
	if (minionState == 0) {
		updateXPos();
	} else if(minionState == -2) {
		Minion::minionDeathAnimation();
	}
}

void Spikey::Draw(SDL_Renderer* rR, CIMG* iIMG) {
	if(minionState != -2) {
		iIMG->Draw(rR, (int)fXPos + (int)CCore::getMap()->getXPos(), (int)fYPos - 4, !moveDirection);
	} else {
		iIMG->DrawVert(rR, (int)fXPos + (int)CCore::getMap()->getXPos(), (int)fYPos + 2);
	}
}

void Spikey::minionPhysics() {
	if (jumpState == 1) {
		physicsState1();
	} else {
		if (!CCore::getMap()->checkCollisionLB((int)fXPos + 2, (int)fYPos + 2, iHitBoxY, true) && !CCore::getMap()->checkCollisionRB((int)fXPos - 2, (int)fYPos + 2, iHitBoxX, iHitBoxY, true) && !onAnotherMinion) {
			physicsState2();
		} else {
			jumpState = 0;
			onAnotherMinion = false;

			if(iBlockID == 52) {
				iBlockID = 51;
				moveDirection = fXPos + iHitBoxX/2 > CCore::getMap()->getPlayer()->getXPos() - CCore::getMap()->getXPos() + CCore::getMap()->getPlayer()->getHitBoxX()/2;
				 switch(CCore::expID){
         case 0: case 1: case 3:
	     this->moveSpeed = std::stoi(CCFG::keyIDSpeed)*0.8;
              break;
         case 2: case 4:
              this->moveSpeed = std::stoi(CCFG::keyIDSpeed)*1.2;
              break;
         case 5:
               this->moveSpeed = std::stoi(CCFG::keyIDSpeed);
               break;
          default:
               this->moveSpeed = std::stoi(CCFG::keyIDSpeed);
}
			}
		}
	}
}

/* ******************************************** */

void Spikey::collisionWithPlayer(bool TOP) {
	if(CCore::getMap()->getPlayer()->getStarEffect()) {
		setMinionState(-2);
	} else {
		CCore::getMap()->playerDeath(true, false);
	}
}
