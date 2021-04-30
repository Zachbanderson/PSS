#ifndef AIRPORT_H
#define AIRPORT_H
#include "queue.h"
#include <cstdlib>
class Airport
{
public:
    Airport(int runways);               //Number of runways




    /***************
     ** ACCESSORS **
     ***************/
    int getLanded(){return landed;}
    int getTookOff(){return tookOff;}
    int getCrashed(){return crashed;}
    double getTakeoffWait(){return aveTakeoffWait * tookOff;}
    double getLandingWait(){return aveLandingWait * landed;}
    unsigned getTime(){return TotalTime;}
    void printData();


    /**************
     ** MUTATORS **
     **************/
    void setTime(unsigned time);        //Amount of minutes to simulate
    void setLandingTime(double time);   //Time it takes for a plane to land
    void setTakeoffTime(double time);   //Time it takes for a plane to take off

    void setPlaneArrivalTime(double time);  //Average amount of time it takes
                                            //for a plane to arrive
    void setPlaneTakeoffTime(double time);  //Average amount of time it takes
                                            //for a plane to take off
    void setFlyingTime(double time);        //Amount of time the plane can stay
                                            //in the air
    void run();



private:

    /**************
     ** MUTATORS **
     **************/
    bool planeFliesIn();
    bool planeStartsFlying();
    void oneMinutePasses();
    void reserveRunway(unsigned amount);


    int runways;                //Number of runways the airport has

    //! Note !//
    /// Initialize in constructor
    bool reservedForTakeoff;    //Checks if a plane is using the runway to take
                                //off

    bool reservedForLanding;    //Checks if a plane is using the runway to land
    unsigned TotalTime;         //The total amount of time the simulation runs
    unsigned SimTime;           //Keeps track of how many minutes the simulation
                                //has been running
    unsigned CountToTakeoff;    //Once a plane taking off has reserved the
                                //runway, we keep track of how long the plane
                                //has been using it
    unsigned CountToLand;       //Once a landing plane reserves the runway, we
                                //keep track of how long the plane has been
                                //using it
    //! End Note !//
    unsigned LandingTime;       //Time it takes for a plane to land
    unsigned TakeoffTime;       //Time it takes for a plane to take off
    double PlaneArrivalTime;    //Average time it takes for a plane to arrive in
                                //the landing queue

    double PlaneArrivalChance;  //Chance of a plane arriving
    double PlaneTakeoffTime;    //Average time it takes for a plane to arrive in
                                //the takeoff queue

    double PlaneTakeoffChance;  //Chance of a plane needing to take off
    double FlyingTime;          //Amount of time the plane can stay in the
                                //landing queue without crashing
    int crashed = 0;            //Number of planes that crashed
    int landed = 0;             //Number of planes that landed
    int tookOff = 0;            //Number of planes that took off
    double aveLandingWait = 0;  //Average amount of time the plane stayed in the
                                //landing queue
    double aveTakeoffWait = 0;  //Average amount of time the plane stayed in the
                                //takeoff queue



    Queue<unsigned> Landing;    //Queue of planes that need to land
    Queue<unsigned> Takeoff;    //Queue of planes that need to take off
};

#endif // AIRPORT_H

/******************************
 ******** CONSTRUCTOR *********
 ******************************/

/****************************************************************
 * Airport(int runways);
 *   Constructor; Initialize class attributes
 *   Parameters: runways(int)-number of runways the airport has
 *   Return: none
 ***************************************************************/

/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************
 * int getLanded();
 *
 *   Accessor; This method returns the amount of planes that landed
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: int-Number of planes that landed
 *******************************************************************/

/*******************************************************************
 * int getTookoff();
 *
 *   Accessor; This method returns the amount of planes that took off
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: int-Number of planes that took off
 *******************************************************************/

/*******************************************************************
 * int getCrashed();
 *
 *   Accessor; This method returns the amount of planes that crashed
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: int-Number of planes that crashed
 *******************************************************************/

/*******************************************************************
 * double getTakeoffWait();
 *
 *   Accessor; This method returns the amount of time that the planes
 *             waited in the takeoff queue
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: int-amount of time that the planes waited in the takeoff queue
 *******************************************************************/

/*******************************************************************
 * double getLandingWait();
 *
 *   Accessor; This method returns the amount of time that the planes
 *             waited in the landing queue
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: int-amount of time that the planes waited in the landing queue
 *******************************************************************/

/*******************************************************************
 * unsigned getTotalTime();
 *
 *   Accessor; This method returns the amount of time to simulate
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: unsigned-amount of time to simulate
 *******************************************************************/

/*******************************************************************
 * void printData();
 *
 *   Accessor; This method prints the data
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/**************
 ** MUTATORS **
 **************/

/*******************************************************************
 * void setTime(unsigned time);
 *
 *   Accessor; This method sets the time to simulate
 *------------------------------------------------------------------
 *   Parameter: time(unsigned)-Time to simulate
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void setLandingTime(double time);
 *
 *   Accessor; This method sets the time it takes for a plane to land
 *------------------------------------------------------------------
 *   Parameter: time(double)-Time for the plane to land
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void setTakeoffTime(double time);
 *
 *   Accessor; This method sets the time it takes for a plane to take off
 *------------------------------------------------------------------
 *   Parameter: time(unsigned)-Time for the plane to take off
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void setPlaneArrivalTime(double time);
 *
 *   Accessor; This method sets the time to simulate
 *------------------------------------------------------------------
 *   Parameter: time(unsigned)-Time to simulate
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void setPlaneTakeoff(double time);
 *
 *   Accessor; This method sets the time to simulate
 *------------------------------------------------------------------
 *   Parameter: time(unsigned)-Time to simulate
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void setFlyingTime(double time);
 *
 *   Accessor; This method sets the time that a plane can fly without crashing
 *------------------------------------------------------------------
 *   Parameter: time(double)-Time to set
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void run();
 *
 *   Accessor; This method runs the simulation
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * bool planeFliesIn();
 *
 *   Mutator; This adds a plane to the landing queue
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: true if a plane flies in
 *******************************************************************/

/*******************************************************************
 * bool planeStartsFlying();
 *
 *   Mutator; This adds a plane to the takeoff queue
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: true if a plane is set to take off
 *******************************************************************/

/*******************************************************************
 * void oneMinutePasses();
 *
 *   Mutator; This simulates one minute
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void reserveRunway(unsigned amount);
 *
 *   Mutator; This reserves a runway for use
 *------------------------------------------------------------------
 *   Parameter: amount(unsigned)-time it reserves
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/
