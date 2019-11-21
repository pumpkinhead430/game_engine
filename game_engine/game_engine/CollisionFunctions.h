#pragma once
//this headr is for all collison related functions
#define PI 3.14159265
#include <iostream>
using namespace std;

VisableObj* Pixel_Colide(Movable *character, int i, int j, vector<VisableObj*>* all_objects, int dst_x, int dst_y)
{ // this function checks if an object is "in" the pixel i, j and returns if there is a object at dst_x, dst_y
	for (int index = 0; index < all_objects->size(); index++)
	{
		if (all_objects->at(index)->GetId() != character->GetId())
		{
			int xplace = (dst_x + j) - all_objects->at(index)->GetInfo()->x;// normalizes the x cord in the object
			int yplace = (dst_y + i) - all_objects->at(index)->GetInfo()->y;// normalizes the y cord in the object
			if (yplace >= 0 && yplace < all_objects->at(index)->GetInfo()->h)
			{
				if (xplace >= 0 && xplace < all_objects->at(index)->GetInfo()->w)
				{
					if (!all_objects->at(index)->GetCurrentImage()->IsTransperent(yplace, xplace))//checking if that pixel of the object is transperent or not 
					{ 
						return all_objects->at(index);
					}
				}
			}
		}
	}
	return nullptr;

}


void who_colided(Movable *character, vector<VisableObj*>* all_objects, vector<VisableObj*>* colided, int dst_x, int dst_y)
{
	/* this function says if a character colided with
	 an object or multiple*/
	//#pragma omp parallel for // that makes the program to split the for into sections and run them in parallel 
	for (int i = 0; i < character->GetCurrentImage()->GetCollisonPixels()->size(); i++)
	{
		VisableObj *temp = Pixel_Colide(character, character->GetCurrentImage()->GetCollisonPixels()->at(i)[0],
			character->GetCurrentImage()->GetCollisonPixels()->at(i)[1], all_objects,dst_x, dst_y);
		if (temp != nullptr) // checks if a real collison happend
		{
			bool is_colided = true;
			for (int i = 0; i < colided->size(); i++)
			{
				if (temp->GetId() == colided->at(i)->GetId())
					is_colided = false;
			}
			if (is_colided)
			{
				//#pragma omp	critical // this makes the program know that we are writing to a variable and locks this part every time a process uses it
				//{

				colided->push_back(temp);
				//}
			}
		}
	}
}



void collision(vector<VisableObj*>*all_objects, vector<Movable*>* movablechars, vector<VisableObj*> *colided)
{
	// this function checks where can the object go and move it according to that
	for (int i = 0; i < movablechars->size(); i++)
	{
		int temp_x = movablechars->at(i)->GetDst()->x;
		int temp_y = movablechars->at(i)->GetDst()->y;
		if (temp_x != movablechars->at(i)->GetInfo()->x || temp_y != movablechars->at(i)->GetInfo()->y)
		{
			who_colided(movablechars->at(i), all_objects, colided, temp_x, temp_y);
			if (colided->size() > 0)
			{
				colided->clear();
				who_colided(movablechars->at(i), all_objects, colided, movablechars->at(i)->GetInfo()->x, temp_y);
				if (colided->size() > 0)
				{
					colided->clear();
					who_colided(movablechars->at(i), all_objects, colided, temp_x, movablechars->at(i)->GetInfo()->y);
					if (colided->size() > 0)
					{
						movablechars->at(i)->SetForce(0, 0);
						movablechars->at(i)->SetSpeed(0, 0);
						movablechars->at(i)->SetDst(movablechars->at(i)->GetInfo()->y, movablechars->at(i)->GetInfo()->x);
					}
					else
					{
						movablechars->at(i)->SetForce(0, movablechars->at(i)->GetForce()->first);
						movablechars->at(i)->SetSpeed(0, movablechars->at(i)->GetSpeed()->second);
						movablechars->at(i)->SetDst(movablechars->at(i)->GetInfo()->y, temp_x);
					}		
				}
				else
				{
					movablechars->at(i)->SetForce(movablechars->at(i)->GetForce()->second, 0);
					movablechars->at(i)->SetSpeed(movablechars->at(i)->GetSpeed()->first, 0);
					movablechars->at(i)->SetDst(temp_y, movablechars->at(i)->GetInfo()->x);
				}

			}
			//problem

		}
	}
}