#include "airport.h"
#include "time.h"
#include <cmath>
const bool DEBUG = false;

/**********************************************************
 *
 * Constructor Airport: Class Airport
 *_________________________________________________________
 * This method constructs the Airport class
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will construct an Airport class
 ***********************************************************/
Airport::Airport(int runways)
{
    this->runways = runways;
    reservedForTakeoff = reservedForLanding = false;
    SimTime = CountToLand = CountToTakeoff = 0;
    landed = tookOff = crashed = 0;
    srand(time(NULL));
}

/**********************************************************
 *
 * Method setTime(unsigned time): Class Airport
 *_________________________________________________________
 * This method sets the time to simulate
 *_________________________________________________________
 * PRE-CONDITIONS
 *     time: time to simulate
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::setTime(unsigned int time)    //Time to simulate
{
    TotalTime = time;
}

/**********************************************************
 *
 * Method setLandingTime(double time): Class Airport
 *_________________________________________________________
 * This method sets the time it takes for a plane to land
 *_________________________________________________________
 * PRE-CONDITIONS
 *     time: time to set
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::setLandingTime(double time)   //Time it takes for a plane to land
{
    LandingTime = time;
}

/**********************************************************
 *
 * Method setTakeoffTime(double time): Class Airport
 *_________________________________________________________
 * This method sets the time it takes for a plane to take off
 *_________________________________________________________
 * PRE-CONDITIONS
 *     time: time to set
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::setTakeoffTime(double time)   //Time it takes for a plane to take
                                            //off
{
    TakeoffTime = time;
}

/**********************************************************
 *
 * Method setPlaneArrivalTime(double time): Class Airport
 *_________________________________________________________
 * This method sets the average time it takes for a plane to
 * get into the landing queue
 *_________________________________________________________
 * PRE-CONDITIONS
 *     time: time to set
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::setPlaneArrivalTime(double time)  //Average time it takes for a
                                                //plane to arrive in landing q
{
    PlaneArrivalTime = time;

    //Calculating the chance of a plane arriving every minute
//    double temp = 60/time;
//    temp *= (100/60);
//    temp /= 100;
//    PlaneArrivalChance = temp;
    PlaneArrivalChance = 1/time;

}

/**********************************************************
 *
 * Method setPlaneTakeoffTime(double time): Class Airport
 *_________________________________________________________
 * This method sets the average time it takes for a plane to
 * get into the takeoff queue
 *_________________________________________________________
 * PRE-CONDITIONS
 *     time: time to set
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::setPlaneTakeoffTime(double time)  //Average time it takes for a
                                                //plane to arrive in takeoff q
{
    PlaneTakeoffTime = time;

    //Calculating the chance of a plane arriving every minute
//    double temp = 60/time;
//    temp *= (100/60);
//    temp /= 100;
//    PlaneTakeoffChance = temp;
    PlaneTakeoffChance = 1/time;
}

/**********************************************************
 *
 * Method setFlyingTime(double time): Class Airport
 *_________________________________________________________
 * This method sets the amount of time a plane can stay in the air
 *_________________________________________________________
 * PRE-CONDITIONS
 *     time: time to set
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::setFlyingTime(double time)    //Amount of time that a plane can
                                            //stay in the air
{
    FlyingTime = time;
}

/**********************************************************
 *
 * Method run(): Class Airport
 *_________________________________________________________
 * This method runs the simulation
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::run()
{
    reservedForTakeoff = reservedForLanding = false;
    SimTime = CountToLand = CountToTakeoff = 0;
    aveTakeoffWait = 0;
    aveLandingWait = 0;
    landed = tookOff = crashed = 0;
    while(SimTime <= TotalTime)
        oneMinutePasses();
    aveTakeoffWait /= tookOff;
    aveLandingWait /= landed;
    Landing.clear();
    Takeoff.clear();
    //cout << "SimTime: " << SimTime << endl;
    //printData();
}

/**********************************************************
 *
 * Method printData(): Class Airport
 *_________________________________________________________
 * This method prints the data that the simulation creates
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::printData()
{
    cout << "Amount of planes that took off: " << tookOff << endl;
    cout << "Amount of planes that landed: " << landed << endl;
    cout << "Number of planes that crashed: " << crashed << endl;
    cout << "Average amount of time that a plane spent in the takeoff queue: "
         << aveTakeoffWait << " minutes" << endl;
    cout << "Average amount of time that a plane spent in the landing queue: "
         << aveLandingWait << " minutes" << endl;
}

/**********************************************************
 *
 * Method oneMinutePasses(): Class Airport
 *_________________________________________________________
 * This method simulates on minute
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns nothing
 ***********************************************************/
void Airport::oneMinutePasses()
{
    SimTime++;

    if(DEBUG)
    {
        cout << "SimTime: " << SimTime << endl;
        cout << "Size of takeoff queue: " << Takeoff.size() << endl;
        cout << "Number landed: " << landed << endl;
        cout << "Number taken off: " << tookOff << endl;
        cout << "Size of landing queue: " << Landing.size() << endl;
        cout << endl;
    }
    if(reservedForLanding)
    {
        CountToLand++;
        if(DEBUG)
        {
            cout << "CountToLand: " << CountToLand << endl;
            cout << "Landing.top(): " << Landing.top() << endl;

        }
        if((CountToLand) == LandingTime)
        {
            //Plane has landed
            reservedForLanding = false;
            //If the time that it was waiting is greater than the amount of time
            //that the plane could stay in the air, it crashes
            if(SimTime - Landing.top() > FlyingTime)
            {
                if(DEBUG)
                {
                    cout << "!!FLAG!!" << endl;
                    cout << "Plane crashed" << endl;
                }
                crashed++;
                Landing.pop();
                CountToLand = 0;
                reservedForLanding = false;
            }
            else
            {
                if(DEBUG)
                {
                    cout << "!!FLAG!!" << endl;
                }
                aveLandingWait += SimTime - LandingTime - Landing.top();
                Landing.pop();
                landed++;
                CountToLand = 0;
                reservedForLanding = false;
            }



        }
    }
    else if(reservedForTakeoff)
    {
        CountToTakeoff++;
        if(DEBUG)
        {
            cout << "CountToTakeoff: " << CountToTakeoff << endl;
        }
        if((CountToTakeoff) == TakeoffTime)
        {
            if(DEBUG)
            {
                cout << "!!FLAG!!" << endl;
            }
            //Plane has taken off
            aveTakeoffWait += SimTime - TakeoffTime - Takeoff.top();
            reservedForTakeoff = false;
            Takeoff.pop();
            tookOff++;
            CountToTakeoff = 0;
        }
    }

    if(!(reservedForTakeoff || reservedForLanding))
    {
        if(!Landing.isEmpty())
        {
            reservedForLanding = true;
            reservedForTakeoff = false;
        }
        //If the landing queue is empty and the runway has not been reserved,
        //only then do we reserve the runway for takeoff
        if(Landing.isEmpty() && !Takeoff.isEmpty())
        {
            reservedForTakeoff = true;
            reservedForLanding = false;
        }
    }


    //Potentially adding a plan to queues
    if(planeFliesIn())
    {
        if(DEBUG)
        {
            cout << "Right before adding new plane" << endl;
            cout << "Landing.size() is: " << Landing.size() << endl;
        }
        Landing.push(SimTime);
        if(DEBUG)
        {
            cout << "Updated the landing queue" << endl;
            cout << "Landing.size() is: " << Landing.size() << endl;
        }
    }
    if(planeStartsFlying())
    {
        Takeoff.push(SimTime);
    }


}

/**********************************************************
 *
 * Method planeFlyiesIn(): Class Airport
 *_________________________________________________________
 * This method adds a plane to the landing queue
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns true if the plane is added
 ***********************************************************/
bool Airport::planeFliesIn()
{
    int r = rand() % 101;
    if(r < PlaneArrivalChance * 100)
    {
        if(DEBUG)
        {
            cout << "Plane flies in" << endl;
        }
        return true;
    }
    return false;
}

/**********************************************************
 *
 * Method planeStartsFlying(): Class Airport
 *_________________________________________________________
 * This method adds a plane to the takeoff queue
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function returns true if the plane is added
 ***********************************************************/
bool Airport::planeStartsFlying()
{
    int r = rand() % 101;
    if(r < PlaneTakeoffChance * 100)
    {
        if(DEBUG)
        {
            cout << "Plane gets into takeoff queue" << endl;
        }
        return true;
    }
    return false;
}
