#include "Room.h"
#include "Game.h"



Room::Room(Game* game)
{
}
Room::Room(Game* game, SDL_Rect rect) :game(game), rect(rect) {
	texture = new Texture();

}
Room::~Room()
{
	delete texture;
}
void Room::loadTexture() {
	rect.x = x * rect.w;
	rect.y = y * rect.h;
	if (upDoor && downDoor && leftDoor && rightDoor)//UDLR
	{
		filename = "..\\images\\roomUDLR.png";
	}
	else if (upDoor && downDoor && leftDoor)//UDL
	{
		filename = "..\\images\\roomUDL.png";
	}
	else if (upDoor && downDoor && rightDoor)//UDR
	{
		filename = "..\\images\\roomUDR.png";
	}
	else if (upDoor && leftDoor && rightDoor)//ULR
	{
		filename = "..\\images\\roomULR.png";
	}
	else if (upDoor && downDoor)//UD
	{
		filename = "..\\images\\roomUD.png";
	}
	else if (upDoor && leftDoor)//UL
	{
		filename = "..\\images\\roomUL.png";

	}
	else if (upDoor && rightDoor)//UR
	{
		filename = "..\\images\\roomUR.png";
	}

	else if (downDoor && leftDoor && rightDoor)//DLR
	{
		filename = "..\\images\\roomDLR.png";
	}
	else if (downDoor && leftDoor)//DL
	{
		filename = "..\\images\\roomDL.png";
	}
	else if (downDoor && rightDoor)//DR
	{
		filename = "..\\images\\roomDR.png";
	}
	else if (leftDoor && rightDoor)//LR
	{
		filename = "..\\images\\roomLR.png";
	}
	else if (upDoor)//U
	{
		if (special == "Boss") {
			filename = "..\\images\\roomBossU.png";
		}
		else if (special == "Chest") {
			filename = "..\\images\\roomChestU.png";
		}
		else if (special == "Shop") {
			filename = "..\\images\\roomShopU.png";
		}
		else {
			filename = "..\\images\\roomU.png";
		}
	}
	else if (downDoor)//D
	{
		if (special == "Boss") {
			filename = "..\\images\\roomBossD.png";
		}
		else if (special == "Chest") {
			filename = "..\\images\\roomChestD.png";
		}
		else if (special == "Shop") {
			filename = "..\\images\\roomShopD.png";
		}
		else if (special == "FirstRoom") {
			filename = "..\\images\\firstRoom.png";
		}
		else {
			filename = "..\\images\\roomD.png";
		}
	}
	else if (leftDoor)//L
	{
		if (special == "Boss") {
			filename = "..\\images\\roomL.png";
		}
		else if (special == "Chest") {
			filename = "..\\images\\roomChestL.png";
		}
		else if (special == "Shop") {
			filename = "..\\images\\roomShopL.png";
		}
		else {
			filename = "..\\images\\roomL.png";
		}

	}
	else if (rightDoor)//R
	{
		if (special == "Boss") {
			filename = "..\\images\\roomBossR.png";
		}
		else if (special == "Chest") {
			filename = "..\\images\\roomChestR.png";
		}
		else if (special == "Shop") {
			filename = "..\\images\\roomShopR.png";
		}
		else {
			filename = "..\\images\\roomR.png";
		}

	}
	texture->loadFromImg(game->getRenderer(), filename);
}
void Room::render() {

	/*
	for (Recorre los tiles de la sala) {//Pinta la sala
		if (...) {//Si est� dentro de la sala
			tile->render();
		}
	}
	*/
	for (GameObject* o : characters) {
		if (game->getCamera()->isInsideCamera(o->getTransform())) {
			o->render();
		}
	}
}
//-----------------------------------------------------------------------------------------------
int Room::getX()
{
	return x;
}
int Room::getY()
{
	return y;
}
bool Room::getUpDoor()
{
	return upDoor;
}
bool Room::getRightDoor()
{
	return rightDoor;
}
bool Room::getLeftDoor()
{
	return leftDoor;
}
bool Room::getDownDoor()
{
	return downDoor;
}
bool Room::getVisited()
{
	return visited;
}
string Room::getSpecial() {
	return special;
}
void Room::setX(int X) {
	x = X;
}
void Room::setY(int Y) {
	y = Y;
}
void Room::setUpDoor(bool UpDoor) {
	upDoor = UpDoor;
}
void Room::setRightDoor(bool RightDoor) {
	rightDoor = RightDoor;
}
void Room::setLeftDoor(bool LeftDoor) {
	leftDoor = LeftDoor;
}
void Room::setDownDoor(bool DownDoor) {
	downDoor = DownDoor;
}
void Room::setVisited(bool Visited) {
	visited = Visited;
}
void Room::setSpecial(string Special) {
	special = Special;
}

void Room::addCharacter(GameObject * o)
{
	characters.push_back(o);
}

//-------------------------------------------------------------------------------------