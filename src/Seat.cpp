#include "Seat.h"

Seat::Seat()
{
	mana = 1000;
	manaDelta = 0;
	hp = 1000;
	gold = 500;
	numClaimedTiles = 0;
	sem_init(&goalsLockSemaphore, 0, 1);
	sem_init(&completedGoalsLockSemaphore, 0, 1);
	sem_init(&failedGoalsLockSemaphore, 0, 1);

	numCreaturesControlled = 0;
	factionHumans = 0.0;
	factionCorpars = 0.0;
	factionUndead = 0.0;
	factionConstructs = 0.0;
	factionDenizens = 0.0;
	alignmentAltruism = 0.0;
	alignmentOrder = 0.0;
	alignmentPeace = 0.0;
}

/** \brief Adds a goal to the vector of goals which must be completed by this seat before it can be declared a winner.
  *
*/
void Seat::addGoal(Goal *g)
{
	sem_wait(&goalsLockSemaphore);
	goals.push_back(g);
	sem_post(&goalsLockSemaphore);
}

/** \brief A simple accessor function to return the number of goals which must be completed by this seat before it can be declared a winner.
  *
*/
unsigned int Seat::numGoals()
{
	sem_wait(&goalsLockSemaphore);
	unsigned int tempUnsigned = goals.size();
	sem_post(&goalsLockSemaphore);

	return tempUnsigned;
}

/** \brief A simple accessor function to allow for looping over the goals which must be completed by this seat before it can be declared a winner.
  *
*/
Goal* Seat::getGoal(unsigned int index)
{
	sem_wait(&goalsLockSemaphore);
	Goal *tempGoal = goals[index];
	sem_post(&goalsLockSemaphore);

	return tempGoal;
}

/** \brief A simple mutator to clear the vector of unmet goals.
  *
*/
void Seat::clearGoals()
{
	sem_wait(&goalsLockSemaphore);
	goals.clear();
	sem_post(&goalsLockSemaphore);
}

/** \brief A simple mutator to clear the vector of met goals.
  *
*/
void Seat::clearCompletedGoals()
{
	sem_wait(&completedGoalsLockSemaphore);
	completedGoals.clear();
	sem_post(&completedGoalsLockSemaphore);
}

/** \brief A simple accessor function to return the number of goals completed by this seat.
  *
*/
unsigned int Seat::numCompletedGoals()
{
	sem_wait(&completedGoalsLockSemaphore);
	unsigned int tempUnsigned = completedGoals.size();
	sem_post(&completedGoalsLockSemaphore);

	return tempUnsigned;
}

/** \brief A simple accessor function to allow for looping over the goals completed by this seat.
  *
*/
Goal* Seat::getCompletedGoal(unsigned int index)
{
	sem_wait(&completedGoalsLockSemaphore);
	Goal *tempGoal = completedGoals[index];
	sem_post(&completedGoalsLockSemaphore);

	return tempGoal;
}

/** \brief A simple accessor function to return the number of goals failed by this seat.
  *
*/
unsigned int Seat::numFailedGoals()
{
	sem_wait(&failedGoalsLockSemaphore);
	unsigned int tempUnsigned = failedGoals.size();
	sem_post(&failedGoalsLockSemaphore);

	return tempUnsigned;
}

/** \brief A simple accessor function to allow for looping over the goals failed by this seat.
  *
*/
Goal* Seat::getFailedGoal(unsigned int index)
{
	sem_wait(&failedGoalsLockSemaphore);
	Goal *tempGoal = failedGoals[index];
	sem_post(&failedGoalsLockSemaphore);

	return tempGoal;
}

/** \brief Loop over the vector of unmet goals and call the isMet() and isFailed() functions on
  * each one, if it is met move it to the completedGoals vector.
  *
*/
unsigned int Seat::checkAllGoals()
{
	// Loop over the goals vector and move any goals that have been met to the completed goals vector.
	sem_wait(&goalsLockSemaphore);
	vector<Goal*>::iterator currentGoal = goals.begin();
	while(currentGoal != goals.end())
	{
		// Start by checking if the goal has been met by this seat.
		if((*currentGoal)->isMet(this))
		{
			sem_wait(&completedGoalsLockSemaphore);
			completedGoals.push_back(*currentGoal);
			sem_post(&completedGoalsLockSemaphore);

			currentGoal = goals.erase(currentGoal);
		}
		else
		{
			// If the goal has not been met, check to see if it cannot be met in the future.
			if((*currentGoal)->isFailed(this))
			{
				sem_wait(&failedGoalsLockSemaphore);
				failedGoals.push_back(*currentGoal);
				sem_post(&failedGoalsLockSemaphore);

				currentGoal = goals.erase(currentGoal);
			}
			else
			{
				currentGoal++;
			}
		}
	}
	sem_post(&goalsLockSemaphore);

	return numGoals();
}

/** \brief Loop over the vector of met goals and call the isUnmet() function on each one, if any of them are no longer satisfied move them back to the goals vector.
  *
*/
unsigned int Seat::checkAllCompletedGoals()
{
	// Loop over the goals vector and move any goals that have been met to the completed goals vector.
	sem_wait(&completedGoalsLockSemaphore);
	vector<Goal*>::iterator currentGoal = completedGoals.begin();
	while(currentGoal != completedGoals.end())
	{
		// Start by checking if this previously met goal has now been unmet.
		if((*currentGoal)->isUnmet(this))
		{
			sem_wait(&goalsLockSemaphore);
			goals.push_back(*currentGoal);
			sem_post(&goalsLockSemaphore);

			currentGoal = completedGoals.erase(currentGoal);
		}
		else
		{
			// Next check to see if this previously met goal has now been failed.
			if((*currentGoal)->isFailed(this))
			{
				sem_wait(&failedGoalsLockSemaphore);
				failedGoals.push_back(*currentGoal);
				sem_post(&failedGoalsLockSemaphore);

				currentGoal = completedGoals.erase(currentGoal);
			}
			else
			{
				currentGoal++;
			}
		}
	}
	sem_post(&completedGoalsLockSemaphore);

	return numCompletedGoals();
}

string Seat::getFormat()
{
	return "color\tfaction\tstartingX\tstartingY\tcolorR\tcolorG\tcolorB";
}

ostream& operator<<(ostream& os, Seat *s)
{
	os << s->color << "\t" << s->faction << "\t" << s->startingX << "\t" << s->startingY << "\t";
	os << s->colourValue.r << "\t" << s->colourValue.g << "\t" << s->colourValue.b << "\n";

	return os;
}

istream& operator>>(istream& is, Seat *s)
{
	is >> s->color >> s->faction >> s->startingX >> s->startingY;
	is >> s->colourValue.r >> s->colourValue.g >> s->colourValue.b;
	s->colourValue.a = 1.0;

	return is;
}

