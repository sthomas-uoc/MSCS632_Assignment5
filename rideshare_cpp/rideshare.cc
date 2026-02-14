#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ride {

  protected:
    string ride_id;
    
    string pickup_location;
    
    string dropoff_location;

    float distance;

    float fare;

  public:

    Ride(string id, string pickup, string dropoff, float dist)
      : ride_id(id), pickup_location(pickup), dropoff_location(dropoff), distance(dist) {
        
    }

    virtual ~Ride() {}

    virtual string getTypeName() {
      return "Ride";
    }
    
    virtual string getRideDetails() {
      return this->getTypeName() + " - " + this->ride_id + " to " + this->dropoff_location;;
    }

    virtual float calculateFare() {
      this->fare = this->distance * 2.5;
      return this->fare;
    }
};

class StandardRide : public Ride {

  public:

    StandardRide(string id, string pickup, string dropoff, float dist)
       : Ride(id, pickup, dropoff, dist) {
      
    }

    string getTypeName() override {
      return "Standard Ride";
    }
    
    float calculateFare() override {
      this->fare = this->distance * 2.5;
      return this->fare;
    }

};

class PremiumRide : public Ride {
  public:

    PremiumRide(string id, string pickup, string dropoff, float dist)
      : Ride(id, pickup, dropoff, dist) {
        
    }
    
    string getTypeName() override {
      return "Premium Ride";
    }
    
    float calculateFare() override {
      this->fare = this->distance * 3.5;
      return this->fare;
    }

    string getRideDetails() override {
      return "Premium Ride - " + this->ride_id + " to " + this->dropoff_location;
    }
};

class Driver {
  private:
    string driver_id;

    string name;

    float rating;

    vector<Ride*> assigned_rides;

  public:
    Driver(string id, string d_name, float d_rating)
      : driver_id(id), name(d_name), rating(d_rating) {
        
    }
    
    void addRide(Ride* ride) {
      this->assigned_rides.push_back(ride);
    }

    string getDriverInfo() {
      return this->driver_id + " - " + this->name + " - with rating " + to_string(this->rating);
    }

    auto assignedRides() {
      return this->assigned_rides;
    }
    
};

class Rider {
  private:
    string rider_id;

    string name;

    vector<Ride*> requested_rides;

  public:
    Rider(string id, string r_name)
      : rider_id(id), name(r_name) {
        
    }
    
    void requestRide(Ride* ride) {
      this->requested_rides.push_back(ride);
    }

    auto viewRides() {
      return this->requested_rides;
    }
};

int main(int argc, char** argv) {

  cout << "Rideshare" << endl;

  // Ride* ride = new Ride();

  // Setup drivers and rides
  StandardRide* standard_ride = new StandardRide("1", "Brooklyn", "Manhattan", 3.0);

  PremiumRide* premium_ride = new PremiumRide("2", "Corbin", "Williamsburg", 20.0);

  // Refer to the base class
  Ride* standard_ride2 = new StandardRide("3", "Bethesda", "Lincoln Memorial", 20.0);

  // PremiumRide* premium_ride2 = new PremiumRide();

  Rider rider("5001", "Philip");

  Driver driver("1001", "Matthew", 4.8);

  // Perform rideshare actions
  rider.requestRide(standard_ride);
  rider.requestRide(premium_ride);

  driver.addRide(standard_ride);
  driver.addRide(standard_ride2);
  // driver.addRide(premium_ride2);

  // Call overridden methods
  vector<Ride*> rides;
  rides.push_back(standard_ride);
  rides.push_back(premium_ride);

  for(auto ride: rides) {
    cout << ride->getRideDetails() << " - Calculated Fare: $"
      << ride->calculateFare() << endl;
  }

  cout << endl;

  // Driver getDriverInfo
  cout << "getDriverInfo - " << driver.getDriverInfo() << endl;

  cout << endl;

  // Driver assignedRides
  for(auto ride: driver.assignedRides()) {
    cout << ride->getRideDetails() << " - Calculated Fare: $"
      << ride->calculateFare() << endl;
  }

  cout << endl;

  // Rider viewRides
  for(auto ride: rider.viewRides()) {
    cout << ride->getRideDetails() << " - Calculated Fare: $"
      << ride->calculateFare() << endl;
  }

  cout << endl;

  // Cleanup
  // delete premium_ride2;
  delete standard_ride2;
  delete premium_ride;
  delete standard_ride;
  // delete ride;
}
