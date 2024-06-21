#include <iostream>
#include <cassert>
#include <vector>
#include <map>
using namespace std;
class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip);

private:
    std::string name;
    BinaryTreeNode* BSThead;
};

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripnodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripnodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    const std::vector<Trip*>& getTrips() const {
        return trips;
    }
private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {
        int i,count=0;
        for(i = 0;i<serviceptrs.size();i++){
            if(droplocation == serviceptrs[i]->getName()){
                return serviceptrs[i];
                break;
            }
            else{
                count++;
            }
        }
        if(count==serviceptrs.size()){
            return nullptr;
        }
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    // TransportService* setServicePtr(std::string droplocation) {
        
    //     return nullptr;
    // }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    void addservice(TransportService* service){
        int check=0,i;
        for(i=0;i<serviceptrs.size();i++){
            if(service->getName()==serviceptrs[i]->getName()){
                check=1;
                break;
            }
        }
        if(check==0){
            serviceptrs.push_back(service);
        }
    }
    vector<TransportService*> showservices (){
        return serviceptrs;
    }
private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
        // Implement this function to return the height of the tree
        return 0; // Placeholder
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        return 0; // Placeholder
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
        // Implement this function to return the element with the minimum key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        // Implement this function to return the element with the maximum key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        // Implement this function to search for a node with the given key or the next larger key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the successor node of the given node
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
        return nullptr; // Placeholder
    }
};

void inserto(BinaryTreeNode*& root, BinaryTreeNode* node){
    BinaryTreeNode* w = nullptr;
    BinaryTreeNode* v = root;
    while(v!=nullptr){
        w = v;
        if(node->getDepartureTime()<=v->getDepartureTime()){
            v = v->getLeftPtr();
        }
        else if(node->getDepartureTime()>=v->getDepartureTime()){
            v = v->getRightPtr();
        }
    }
    node->setParentPtr(w);
    //cout<<"elo"<<endl;
    if(w == nullptr){
        root = node;
        //cout<<"elo"<<endl;
    }
    else if(node->getDepartureTime()<=w->getDepartureTime()){
        w->setLeftPtr(node);
    }
    else if(node->getDepartureTime()>=w->getDepartureTime()){
        w->setRightPtr(node);
    }
}

void preorderTraversal(BinaryTreeNode* root, int aftertime, int beforetime, vector<Trip*>& trippo) {
    if (root != nullptr) {
        // Visit the current node
        int k = root->getDepartureTime();
        if(k>=aftertime&&k<beforetime){
            trippo.push_back(root->getTripNodePtr());
            //cout<<trippo.size()<<endl;
        }
        // Traverse the left subtree
        if(root->getLeftPtr()!=nullptr){
            preorderTraversal(root->getLeftPtr(),aftertime, beforetime, trippo);
        }
        if(root->getRightPtr()!=nullptr){
        // Traverse the right subtree
            preorderTraversal(root->getRightPtr(),aftertime, beforetime, trippo);
        }
    }
}
BinaryTreeNode* treemin(BinaryTreeNode* v){
    while(v->getLeftPtr()!=nullptr){
        v = v->getLeftPtr();
    }
    return v;
}
BinaryTreeNode* treesucc(BinaryTreeNode* v){
    if(v->getRightPtr()!=nullptr){
        return treemin(v->getRightPtr());
    }
    BinaryTreeNode* w = v->getParentPtr();
    while(w!=nullptr&&v==w->getRightPtr()){
        v = w;
        w = w->getParentPtr();
    }
    return w;
}
void deleteNode(BinaryTreeNode* root, BinaryTreeNode* node) {
    BinaryTreeNode* w = nullptr;
    BinaryTreeNode* v = nullptr;
    if(node->getLeftPtr()==nullptr||node->getRightPtr()==nullptr){
        w = node; //first and second case
    }
    else{
        w = treesucc(node); // case 3
    }
    if(w->getLeftPtr()!=nullptr){
        v = w->getLeftPtr();
    }
    else{
        v = w->getRightPtr();
    }
    if(v!=nullptr){
        v->setParentPtr(w->getParentPtr());
    }
    if(w->getParentPtr()==nullptr){
        root = v;
    }
    else if(w = w->getParentPtr()->getLeftPtr()){
        w->getParentPtr()->setLeftPtr(v);
    }
    else{
        w->getParentPtr()->setRightPtr(v);
    }
    if(w!=node){
        node->setDepartureTime(w->getDepartureTime());
    }
}

// Trip* bookboy(BinaryTreeNode* root, string vehicle_number, int departure_time,BinaryTreeNode* rootorg){
//     int k;
//     if(root==nullptr){
//         return nullptr;
//     }
//     while(root!=nullptr){
//         if(root->getDepartureTime()==departure_time){
//             cout<<"yes"<<endl;
//             if(root->getTripNodePtr()->getVehicle()->getVehicleNumber()==vehicle_number){
//                 cout<<root->getTripNodePtr()->getBookedSeats()<<endl;
//                 k=root->getTripNodePtr()->getBookedSeats()+1;
//                 cout<<"yes3"<<endl;
//                 root->getTripNodePtr()->setBookedSeats(k);
//                 cout<<root->getTripNodePtr()->getBookedSeats()<<endl;
//                 //checking if seat capacity full
//                 if(root->getTripNodePtr()->getBookedSeats()==root->getTripNodePtr()->getVehicle()->getSeatingCapacity()){
//                     cout<<"yes6"<<endl;
//                     deleteNode(rootorg,root);
//                     cout<<"yes7"<<endl;
//                 }
//                 cout<<root->getTripNodePtr()<<endl;
//                 return root->getTripNodePtr();
//             }
//         }
//         else if(departure_time>root->getDepartureTime()){
//             root = root->getRightPtr();
//         }
//         else if(departure_time<root->getDepartureTime()){
//             root = root->getLeftPtr();
//         }
//     }
// }

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        int i;
        Vehicle* vehicle = nullptr;
        Location* location = nullptr;
        TransportService* tservice = nullptr;
        int vcount=0;
        int plcount=0;
        // Check if the vehicle already exists, if not, create a new one with the seating capacity
        for(i=0;i<vehicles.size();i++){
            if(vehicles[i]->getVehicleNumber()==vehicle_number){
                vcount=1;
                break;
            }
        }
        if(vcount!=1){
            vehicle = new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(vehicle);
        }
        else{
            vehicle = vehicles[i];
        }
        //cout<<vehicles[0]->getVehicleNumber()<<endl;
        vcount=0;
        // Create a new trip and add it to the appropriate objects
        Trip* t1 = new Trip(vehicle,pick_up_location,drop_location,departure_time);
        vehicle->addTrip(t1);
        //cout<<vehicles[0]->getTrips()[0]->getPickUpLocation()<<endl;
        // Create or retrieve the Location object and associated pick up location
        for(i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                plcount=1;
                break;
            }
        }
        if(plcount!=1){
            location = new Location(pick_up_location);
            locations.push_back(location);
            tservice = new TransportService(drop_location);
            location->addservice(tservice);
        }
        else{
            location = locations[i];
            if(locations[i]->getServicePtr(drop_location)==nullptr){
                tservice = new TransportService(drop_location);
                location->addservice(tservice);
            }
            else{
                tservice = locations[i]->getServicePtr(drop_location);
            }
        }
        plcount=0;
        //cout<<locations[0]->getName()<<endl;
        //Add the trip to the TransportService's BST
        BinaryTreeNode* btn = new BinaryTreeNode(departure_time);
        //cout<<btn<<endl;
        btn->setTripNodePtr(t1);
        BinaryTreeNode* root = tservice->getBSTHead(); // Get a reference to the root
        inserto(root, btn);
        tservice->setBSTHead(root);
        //cout<<tservice->getBSTHead()->getDepartureTime()<<endl;
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        vector<Trip*> trippo;
        int i,j;
        for(i = 0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                break;
            }
        }
        //cout<<locations[i]->getName()<<endl;
        //cout<<locations[i]->showservices().size()<<endl;
        for(j=0;j<locations[i]->showservices().size();j++){
            preorderTraversal(locations[i]->showservices()[j]->getBSTHead(),after_time,before_time,trippo);
            // cout<<locations[i]->showservices()[j]->getName()<<endl;
        }
        //cout<<trippo.size();
        return trippo; // Placeholder
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        vector<Trip*> trippo1;
        int i,j;
        for(i = 0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                break;
            }
        }
        for(j=0;j<locations[i]->showservices().size();j++){
            if(locations[i]->showservices()[j]->getName()==destination){
                break;
            }
        }
        preorderTraversal(locations[i]->showservices()[j]->getBSTHead(),after_time,before_time,trippo1);
        return trippo1; // Placeholder
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        int i,j;
        for(i = 0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                break;
            }
        }
        //cout<<locations[i]->getName()<<endl;
        for(j=0;j<locations[i]->showservices().size();j++){
            if(locations[i]->showservices()[j]->getName()==drop_location){
                break;
            }
        }
        //cout<<locations[i]->showservices()[j]->getName()<<endl;
        BinaryTreeNode* axe = locations[i]->showservices()[j]->getBSTHead();
        BinaryTreeNode* nox = axe;
        while(nox!= nullptr){
            if(nox->getDepartureTime()==departure_time){
                if(nox->getTripNodePtr()->getVehicle()->getVehicleNumber()==vehicle_number){
                    int k = nox->getTripNodePtr()->getBookedSeats()+1;
                    nox->getTripNodePtr()->setBookedSeats(k);
                    if(k == nox->getTripNodePtr()->getVehicle()->getSeatingCapacity()){
                        deleteNode(axe,nox);
                    }
                    return nox->getTripNodePtr();
                }
            }
            else if(nox->getDepartureTime()>departure_time){
                nox = nox->getLeftPtr();
            }
            else{
                nox = nox->getRightPtr();
            }
        }
        return nullptr;
    }
    Location* getLocation(std::string location){
        int i;
        for(i=0;i<locations.size();i++){
            if(locations[i]->getName()==location){
                break;
            }
        }
        return locations[i];
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};
// bool isBSTUtil(BinaryTreeNode* node, int minValue, int maxValue);

//Function to check if a tree is a proper BST
// bool isBST(BinaryTreeNode* node){
//     return isBSTUtil(node, INT_MIN, INT_MAX);
// }

// // Utility function to check BST property recursively
// bool isBSTUtil(BinaryTreeNode* node, int minValue, int maxValue) {
//     if (node == nullptr)
//         return true;

//     int nodeValue = node->getDepartureTime();
//     if (nodeValue < minValue || nodeValue > maxValue)
//         return false;

//     return isBSTUtil(node->getLeftPtr(), minValue, nodeValue - 1) &&
//         isBSTUtil(node->getRightPtr(), nodeValue + 1, maxValue);
// }
// int main(){
//     int testCasesPassed = 0;
//     TravelDesk travelDesk;

//     // Add trips
//     for (int i = 0; i < 10; i++) {
//         std::string vehicleNumber = "A" + std::to_string(i);
//         travelDesk.add_trip(vehicleNumber, 4, "LocationA", "LocationB", 1000 + i * 100);
//     }
//     // vector<Trip*> inio = travelDesk.show_trips("LocationA",900, 1400);
//     // cout<<inio[2]->getDepartureTime()<<endl;
//     // Add trips for LocationX
//     for (int i = 0; i < 10; ++i) {
//         std::string vehicleNumber = "X" + std::to_string(i);
//         travelDesk.add_trip(vehicleNumber, 3, "LocationX", "LocationY", 1500 + i * 100);
//     }
//     // vector<Trip*> inio = travelDesk.show_trips("LocationX",1400, 2000);
//     // cout<<inio[2]->getDepartureTime()<<endl;
//     // Verify that the tree is a proper BST
//     BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead(); // Add a function to get root by location
//     // assert(isBST(rootLocationA));
//     // cout<<travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead()<<endl;

//     BinaryTreeNode* rootLocationX = travelDesk.getLocation("LocationX")->getServicePtr("LocationY")->getBSTHead(); // Add a function to get root by location
//     //assert(isBST(rootLocationX));

//     std::vector<Trip*> tripsFromLocationA = travelDesk.show_trips("LocationA", 0, 2000);
//     std::vector<Trip*> tripsFromLocationX = travelDesk.show_trips("LocationX", 0, 2000);

//     // Assert the number of trips from LocationA and LocationX
//     assert(tripsFromLocationA.size() == 10);
//     assert(tripsFromLocationX.size() == 6);

//     testCasesPassed++;
//     cout<<testCasesPassed;
//     // TravelDesk travelDesk;
//     // travelDesk.add_trip("ABC123", 4, "LocationA", "LocationB", 1000);
//     // travelDesk.add_trip("XYZ789", 3, "LocationX", "LocationY", 1500);

//     // std::vector<Trip*> trips = travelDesk.show_trips("LocationA", 800, 1200);
//     // //cout<<trips.size();
//     // TravelDesk travelDesk;
//     // travelDesk.add_trip("LMN456", 2, "LocationP", "LocationQ", 1200);
//     // cout<<travelDesk.show_trips("LocationP",1000,1300)[0]<<endl;
//     // Trip* bookedTrip = travelDesk.book_trip("LocationP", "LocationQ", "LMN456", 1200);
//     // assert(bookedTrip != nullptr);
//     // cout<<bookedTrip<<endl;
//     // assert(bookedTrip->getBookedSeats() == 1);
//     // Trip* secondBooking = travelDesk.book_trip("LocationP", "LocationQ", "LMN456", 1200);
//     // assert(secondBooking != nullptr);
//     // assert(secondBooking->getBookedSeats() == 2);
//     // testCasesPassed++;
// }